#ifndef CLAIRVOYANT_NEURAL_NETWORK_NEURAL_NETWORK_HPP
#define CLAIRVOYANT_NEURAL_NETWORK_NEURAL_NETWORK_HPP

#include "math/math.hpp"
#include <lambda.hpp>
#include <vector>
#include <cstdlib>
#include <random>
#include <iostream>

namespace cvt {


    struct neural_network {
        
        template<typename T> using lambda = lambda::lambda<T>;
        
        using Activation = lambda<auto_double(const auto_double&)>;
        using Loss = lambda<auto_double(const eigen::auto_vector&, const eigen::auto_vector&)>;
    
        struct layer {
        
            Activation activation;
            eigen::auto_matrix weights;
            eigen::auto_vector saved_inputs;
            
            eigen::auto_vector process(const eigen::auto_vector& inputs, bool save = false) {
                
                assert(inputs.size() == this->weights.cols()-1);
            
                eigen::auto_vector inputs_and_bias(this->weights.cols(), 1);
                
                inputs_and_bias(0, 0) = 1; // bias
                
                inputs_and_bias.block(1, 0, this->weights.cols()-1, 1) = inputs;
                
                if (save) {
                
                    this->saved_inputs = inputs_and_bias;
                }
                
                return this->process_with_bias(inputs_and_bias);
                
            }
            
            eigen::auto_vector process_with_bias(const eigen::auto_vector& inputs) {
            
                assert(inputs.size() == this->weights.cols());
                
                return this->weights * inputs;
            }
            
            eigen::vector train(const eigen::vector& back_prop) {
            
                eigen::vector next_back_prop(this->weights.cols(), 1);
                
                double gradient;
                
                for (int row = 0; row < this->weights.rows(); ++row) {
                
                    for (int col = 0; col < this->weights.cols(); ++col) {
                        
                        
                        auto func = [&](){
                            return this->process_with_bias(this->saved_inputs)(row, 0);
                        };
                        
                        gradient = this->saved_inputs(col, 0).value * this->weights(row, col).partial(func) * back_prop(row, 0);
                        
                        gradient = clamp(gradient, {-4, 4});
                        
                        std::cout << this->saved_inputs(col, 0).value << " " << this->weights(row, col).partial(func) 
                            << " " << back_prop(row, 0) << std::endl;
                        
                        this->weights(row, col).value -= gradient;
                        
                        //next_back_prop(col, 0) += gradient;
                        
                    }
                    
                    
                }
                
                return next_back_prop;
            }
            
            void reshape(const int num_inputs, const int num_neurons, lambda<double()> random_weight) {
            
                this->weights = eigen::auto_matrix(num_neurons, num_inputs+1);
                
                for (int row = 0; row < this->weights.rows(); ++row) {
                
                    for (int col = 0; col < this->weights.cols(); ++col) {
                    
                        if (col == 0) {
                        
                            this->weights(row, col) = 0; // bias
                        }
                        else {
                        
                            this->weights(row, col) = random_weight() / std::sqrt(this->weights.rows());
                        }
                    }
                }
            }
            
        };
        
        std::vector<layer> layers; 
        
        range<double> input_range, output_range, activation_range;
        
        Loss loss;
        
        eigen::auto_vector scale_inputs(const eigen::vector& inputs) const {
        
            eigen::auto_vector x(inputs.size(), 1);
            
            for (int i = 0; i < inputs.size(); ++i) {
            
                x(i, 0) = map_min_max(inputs(i, 0), this->input_range, this->activation_range);
            }
            
            return x;
        }
        
        eigen::auto_vector scale_targets(const eigen::vector& targets) const {
        
            eigen::auto_vector y(targets.size(), 1);
            
            for (int i = 0; i < targets.size(); ++i) {
            
                y(i, 0) = map_min_max(targets(i, 0), this->output_range, this->activation_range);
            }
            
            return y;
        }
        
        eigen::vector scale_outputs(const eigen::auto_vector& a) const {
            
            eigen::vector outputs(a.size(), 1);
            
            for (int i = 0; i < a.size(); ++i) {
            
                outputs(i, 0) = map_min_max(a(i, 0).value, this->activation_range, this->output_range);
            }
            
            return outputs;
        }
        
        eigen::vector process(const eigen::vector& inputs) {
        
            eigen::auto_vector x = this->scale_inputs(inputs);
            
            eigen::auto_vector a = this->process(x);
            
            return this->scale_outputs(a);
        }
        
        eigen::auto_vector process(eigen::auto_vector x, bool save = false) {
            
            //std::cout << "process(x,save)" << std::endl;
            
            for (auto& layer : this->layers) {
            
                //std::cout << "Here1\n";
                
                x = layer.process(x, save);
                
            }
            
            return x;
        }
        
        void train(const eigen::vector& inputs, const eigen::vector& targets) {
            
           // std::cout << "train" << std::endl;
        
            eigen::auto_vector x = this->scale_inputs(inputs);
            
            eigen::auto_vector a = this->process(x, true); // save the inputs
            
            eigen::auto_vector y = this->scale_targets(targets);
            
            eigen::vector back_prop(a.size(), 1);
            
            for (int i = 0; i < a.size(); ++i) {
                
               // std::cout << "back_prop " << std::endl;
            
                back_prop(i, 0) = a(i, 0).partial([&](){ return this->loss(a, y); });
            }
            
            //std::cout << "end calc back_prop:\n" << back_prop << std::endl;
            
            std::reverse(this->layers.begin(), this->layers.end());
            
            for (auto& layer : layers) {
            
                //std::cout << "back_prop through layers:\n" << back_prop << std::endl;
                back_prop = layer.train(back_prop);
            }
            
            //std::cout << "end back_prop layers" << std::endl;
            
            std::reverse(this->layers.begin(), this->layers.end());
            
        }
        
        void reshape(const std::vector<int> shape, Activation activation, bool linear_out = false) {
        
            std::random_device rd;
            std::normal_distribution<double> gaussian(0, 0.1);
            
            this->layers.resize(shape.size()-1);
            
            int i = 0;
            
            for (auto& layer : this->layers) {
            
                layer.reshape(shape[i], shape[i+1], [&](){ return gaussian(rd); });
                
                if (i < this->layers.size()-1 || !linear_out)
                    layer.activation = activation;
                else {
                
                    layer.activation = [](const auto_double& z){ return z; };
                }
                
                ++i;
            }
        }
        
        
    };




}

#endif // CLAIRVOYANT_NEURAL_NETWORK_NEURAL_NETWORK_HPP

