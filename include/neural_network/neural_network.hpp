#ifndef CLAIRVOYANT_NEURAL_NETWORK_NEURAL_NETWORK_HPP
#define CLAIRVOYANT_NEURAL_NETWORK_NEURAL_NETWORK_HPP

#include "math/math.hpp"
#include <lambda.hpp>
#include <vector>
//#include <cstdlib>
//#include <random>
#include <iostream>

namespace cvt {


    struct neural_network {
        
        struct layer {
            
            eigen::amatrix weights;
            eigen::avector biases;
            
            eigen::avector saved_inputs;
            
            lambda::lambda<adouble(const adouble&)> activation;
            
            mutable double learning_rate = 0.25;
            
            layer(int inputs = 0, int outputs = 0, lambda::lambda<double()> get_weight = []{ return rand()/double(RAND_MAX); }) {
                
                this->weights = eigen::amatrix(outputs, inputs);
                this->biases = eigen::avector(outputs, 1);
                
                for (int row = 0; row < this->weights.rows(); ++row) {
                    
                    for (int col = 0; col < this->weights.cols(); ++col) {
                        
                        this->weights(row, col) = get_weight();
                    }
                    
                    this->biases(row, 0) = 0;
                }
            }
            
            inline eigen::avector process(const eigen::avector& inputs) {
                
                eigen::avector outputs = this->weights * inputs ;//+ this->biases;
                for (int row = 0; row < outputs.size(); ++row) {
                    outputs(row, 0) = this->activation(outputs(row, 0));
                }
                
                return outputs;
            }
            
            inline eigen::avector forward(const eigen::avector& inputs) {
                
                this->saved_inputs = inputs;
                
                return this->process(inputs);
            }
            
            inline eigen::avector backward(const eigen::avector& gradients) {
                
                eigen::avector next_gradients(this->weights.cols(), 1);
                
                for (int row = 0; row < this->weights.rows(); ++row) {
                    
                    for (int col = 0; col < this->weights.cols(); ++col) {
                        
                        if (row == 0) {
                            next_gradients(col, 0) = 0; 
                        }
                        
                        next_gradients(col, 0) += this->weights(row, col).partial([&]{ 
                            return this->process(this->saved_inputs)(row, 0); 
                        }).derivative * gradients(row).derivative;
                        
                        this->weights(row, col) -= this->learning_rate * next_gradients(col, 0);
                    }
                    
                    this->biases(row, 0).value -= this->learning_rate * this->biases(row, 0).partial([&]{ 
                        return this->process(this->saved_inputs)(row, 0); 
                    }).derivative;
                }
                
                return next_gradients;
            }
        };
        
        std::vector<layer> layers;
        
        lambda::lambda<adouble(const eigen::avector& output, const eigen::avector& target)> loss;
        
        neural_network(std::vector<int> shape = {}, lambda::lambda<double()> get_weight = []{ return rand()/double(RAND_MAX); }) {
            
            this->layers.reserve(shape.size()-1);
            
            for (int i = 1; i < shape.size(); ++i) {
                
                this->layers.push_back(layer(shape[i-1], shape[i], get_weight));
            }
        }
        
        inline eigen::avector process(eigen::avector inputs) {
            
            for (auto& layer : this->layers) {
                
                inputs = layer.process(inputs);
            }
            
            return inputs;
        }
        
        inline eigen::avector forward(eigen::avector inputs) {
            
            for (auto& layer : this->layers) {
                
                inputs = layer.forward(inputs);
            }
            
            return inputs;
        }
        
                                       
        inline eigen::avector backward(eigen::avector gradients) {
            
            std::reverse(this->layers.begin(), this->layers.end());
            
            for (auto& layer : this->layers) {
                
                gradients = layer.backward(gradients);
            }
            
            std::reverse(this->layers.begin(), this->layers.end());
            
            return gradients;
        }
        
        inline eigen::avector train(const eigen::avector& inputs, const eigen::avector& targets) {
            
            eigen::avector outputs = this->forward(inputs);
            
            eigen::avector gradients(targets.size(), 1);
            
            for (int row = 0; row < targets.size(); ++row) {
                adouble val = outputs(row, 0).partial([&]{ return this->loss(outputs, targets); });
                gradients(row, 0) = val;
                
                //std::cout << "val: " << val << " gradients(row, 0): " << gradients(row, 0) << std::endl;
            }
            
            //std::cout << "loss: " << gradients(0, 0) << std::endl; 
            
            return this->backward(gradients);
        }
        
    };




}

#endif // CLAIRVOYANT_NEURAL_NETWORK_NEURAL_NETWORK_HPP

