#include "matrix.hpp"

#include <lambda.hpp>
#include <vector>


namespace cvt {
    
    namespace neural_network {
        
        double clamp(double val, double min, double max) {
        
            return std::min(std::max(val, min), max);
        }
        
        struct neuron {
        
            auto_vector weights;
            auto_double bias;
            mutable double learning_rate = 0.05;
            
            lambda::lambda<auto_double(const auto_double&)> activation;
            lambda::lambda<bool(void)> func;
            
            void reshape(const int num_inputs, lambda::lambda<double()> get_weight) {
            
                this->weights.resize(num_inputs);
                
                for (int i = 0; i < this->weights.size(); ++i) {
                    
                    this->weights(i, 0) = get_weight();
                }
            }
            
            auto_double process(const auto_vector& inputs) {
                
                for (int i = 0; i < inputs.size(); ++i) {
                
                    assert(!isnan(inputs(i, 0).value));
                    assert(!isnan(this->weights(i, 0).value));
                    assert(!isnan(this->weights(i, 0).derivative));
                }
                
                assert(!isnan(this->bias.value));
                
                //std::cout << "neuron process inputs: " << inputs << std::endl;
                
                //std::cout << "neuron.process wts " << this->weights << std::endl;
                
                auto_double result = this->activation(this->weights.dot(inputs) + this->bias);
                
               // std::cout << "neuron process result: " << result << std::endl;
                
                return result;
            }
            
            auto_vector train(const auto_vector& inputs, const auto_double& loss) {
                
                assert(!isnan(loss.derivative));
                
                //std::cout << "neuron.train wts " << this->weights << std::endl;
                
                //std::cout << "loss: " << loss << std::endl;
            
                auto_vector gradient(inputs.size());
                
                //std::cout << "gradient: " << gradient << std::endl;
                
                auto func = [&](){ return this->process(inputs); };
                
                for (int i = 0; i < this->weights.size(); ++i) {
                    
                    //std::cout << "partial of weights: " << this->weights(i, 0).partial(func) << std::endl;
                    
                    //std::cout << "wt: " << this->weights(i, 0) << std::endl;
                    
                    auto_double par = this->weights(i, 0).partial(func);
                    
                    //assert(!isnan(par.derivative));
                
                    gradient(i, 0).derivative = inputs(i, 0).value * this->weights(i, 0).partial(func).derivative * loss.derivative;
                    
                    //std::cout << "par: " << par << " gradient: " << gradient(i, 0) << " loss: " << loss << std::endl;
                    
                    this->weights(i, 0).value = clamp(this->weights(i, 0).value - gradient(i, 0).derivative, -100, 100);
                    //this->weights(i, 0).value -= clamp(gradient(i, 0).derivative, -10, 10);
                    
                    assert(!isnan(this->weights(i, 0).value));
                }
                
                //this->bias.value -= this->learning_rate * this->bias.partial(func).derivative * loss.derivative;
                //this->bias.value -= clamp(this->bias.partial(func).derivative * loss.derivative, -10, 10);
                
                return gradient;
            }
        };
        
        template<typename N> struct layer {
        
            std::vector<N> neurons;
            int num_inputs;
            
            auto_vector saved_inputs;
            
            void reshape(const int num_inputs, const int num_neurons, lambda::lambda<double()> get_weight) {
                
                this->neurons.resize(num_neurons);
                this->num_inputs = num_inputs;
            
                for (auto& n : this->neurons) {
                    
                    n.reshape(num_inputs, get_weight);
                }
            }
            
            auto_vector process(const auto_vector& inputs, bool save = false) {
                
                //std::cout << "layer process inputs: " << inputs << std::endl;
                
                //std::cout << "size: " << this->neurons.size() << std::endl;
                
                assert(inputs.size() == this->num_inputs);
                
                if (save) {
                    
                    this->saved_inputs = inputs;
                }
                
                auto_vector result(this->neurons.size(), 1);
                
                //std::cout << "result created: " << result << std::endl;
                
                int i = 0;
                
                for (auto& n : this->neurons) {
                    
                    //std::cout << "loop i: " << i << std::endl;
                    auto_double val = n.process(inputs);
                    
                    //std::cout << "val: " << val << std::endl;
                    
                    result(i, 0) = val;
                    
                    ++i;
                }
                
                //std::cout << "layer process result: " << result << std::endl;
                
                return result;
            }
            
            auto_vector train(const auto_vector& losses) {
                
                //std::cout << "num_inputs " << this->num_inputs << std::endl;
                
                assert(losses.rows() == this->neurons.size());
                
                auto_vector result(this->num_inputs, 1);
                
                int i = 0;
                
                auto_vector gradient;
            
                for (auto& n : this->neurons) {
                
                    gradient = n.train(this->saved_inputs, losses(i, 0));
                    
                    for (int u = 0; u < this->num_inputs; ++u) {
                    
                        result(u, 0) += gradient(u);
                    }
                    
                    i++;
                }
                
                //std::cout << "layer train result: " << result << std::endl;
                
                return result;
            }
        };
        
        
        template <typename L> struct network { 
        
            std::vector<L> layers; // hiddden and output layers
            lambda::lambda<auto_double(const auto_vector&, const auto_vector&)> loss;
            
            void reshape(const Eigen::VectorXi& shape, lambda::lambda<double()> get_weight) {
                
                assert(shape.cols() == 1);
                assert(shape.rows() > 1);
                
                this->layers.resize(shape.size()-1);
                
                int i = 0;
                
                int num_inputs, num_neurons;
                
                for (auto& layer : this->layers) {
                    
                    num_inputs = shape(i, 0);
                    num_neurons =  shape(i+1, 0);
                    
                    layer.reshape(num_inputs, num_neurons, get_weight);
                    
                    ++i;
                }
                
            }
            
            auto_vector process(const auto_vector& inputs, bool save = false) {
                
                // standardize inputs
                //auto_double mean = inputs.mean();
                //auto_double std_dev = sqrt(variance(inputs));
                
                //std::cout << "mean : " << mean << " std_dev: " << std_dev << std::endl;
                
                auto_vector outputs(inputs.size(), 1);
                
                for (int i = 0; i < outputs.size(); ++i) {
                
                    outputs(i, 0) = inputs(i, 0);
                }
                
                for (auto& layer : this->layers) {
                    
                    outputs = layer.process(outputs, save);
                }
                
                //std::cout << "network return outputs: " << outputs << std::endl;
                
                // rescale outputs
                
                for (int i = 0; i < outputs.size(); ++i) {
                
                    outputs(i, 0) = outputs(i, 0);
                }
                
                return outputs;
            }
            
            void train(const auto_vector& inputs, const auto_vector& target) {
                
                //std::cout << "network train inputs: " << inputs << " target: " << target << std::endl;
                
                auto_vector outputs = this->process(inputs, true);
                
                //std::cout << "network train outputs: " << outputs << std::endl;
                
                auto_vector losses(target.size(), 1);
                
                for (int i = 0; i < outputs.size(); ++i) {
                
                    losses(i, 0) = outputs(i, 0).partial([&]{ return this->loss(outputs, target); } );
                }
                
                //std::cout << "network train losses: " << losses << std::endl;
                
                std::reverse(this->layers.begin(), this->layers.end());
                
                for (auto& layer : this->layers) {
                
                    losses = layer.train(losses);
                    
                    //std::cout << "network train loop layers losses: " << losses << std::endl;
                    
                    //std::cout << "network train loop layers losses transpose: " << losses << std::endl;
                }
                
                //std::cout << "network train end loop " << std::endl;
                
                std::reverse(this->layers.begin(), this->layers.end());
                
                //std::cout << "network train return " << std::endl;
            }
        };
        
        
    }
}