#include "matrix.hpp"

#include <lambda.hpp>
#include <vector>


namespace cvt {
    
    namespace neural_network {
        
        struct neuron {
        
            auto_vector weights;
            auto_double bias;
            
            lambda::lambda<auto_double(const auto_double&)> activation;
            lambda::lambda<bool(void)> func;
            
            void reshape(const int num_inputs, lambda::lambda<double()> get_weight) {
            
                this->weights.resize(num_inputs);
                
                for (int i = 0; i < this->weights.size(); ++i) {
                    
                    *(this->weights.data()+i) = get_weight();
                }
            }
            
            auto_double process(const auto_vector& inputs) {
                
                std::cout << "neuron process inputs: " << inputs << std::endl;
                
                auto_double result = this->activation(this->weights.dot(inputs) + this->bias);
                
                std::cout << "neuron process result: " << result << std::endl;
                
                return result;
            }
            
            auto_vector train(const auto_vector& inputs, const auto_double& loss) {
                
                std::cout << "neuron.train wts " << this->weights << std::endl;
                
                std::cout << "loss: " << loss << std::endl;
            
                auto_vector gradient(inputs.size());
                
                std::cout << "gradient: " << gradient << std::endl;
                
                auto func = [&](){ return this->process(inputs); };
                
                for (int i = 0; i < this->weights.size(); ++i) {
                
                    gradient(i, 0).derivative = inputs(i, 0).value * this->weights(i, 0).partial(func).derivative * loss.derivative;
                    
                    std::cout << " gradient: " << gradient(i, 0) << " loss: " << loss << std::endl;
                    
                    this->weights(i, 0).value -= gradient(i, 0).derivative;
                }
                
                //this->bias.value -= this->bias.partial(func).derivative * loss.derivative;
                
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
                
                std::cout << "layer process inputs: " << inputs << std::endl;
                
                std::cout << "size: " << this->neurons.size() << std::endl;
                
                assert(inputs.size() == this->num_inputs);
                
                if (save) {
                    
                    this->saved_inputs = inputs;
                }
                
                auto_vector result(this->neurons.size(), 1);
                
                std::cout << "result created: " << result << std::endl;
                
                int i = 0;
                
                for (auto& n : this->neurons) {
                    
                    std::cout << "loop i: " << i << std::endl;
                    auto_double val = n.process(inputs);
                    
                    std::cout << "val: " << val << std::endl;
                    
                    result(i, 0) = val;
                    
                    ++i;
                }
                
                std::cout << "layer process result: " << result << std::endl;
                
                return result;
            }
            
            auto_vector train(const auto_vector& losses) {
                
                std::cout << "num_inputs " << this->num_inputs << std::endl;
                
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
                
                auto_vector outputs = inputs;
                
                for (auto& layer : this->layers) {
                    
                    outputs = layer.process(outputs, save);
                }
                
                //std::cout << "network return outputs: " << outputs << std::endl;
                
                return outputs;
            }
            
            void train(const auto_vector& inputs, const auto_vector& target) {
                
                std::cout << "network train inputs: " << inputs << std::endl;
                
                auto_vector outputs = this->process(inputs, true);
                
                std::cout << "network train outputs: " << outputs << std::endl;
                
                auto_vector losses(target.size(), 1);
                
                for (int i = 0; i < outputs.size(); ++i) {
                
                    losses(i, 0) = outputs(i, 0).partial([&]{ return this->loss(outputs, target); } );
                }
                
                std::cout << "network train losses: " << losses << std::endl;
                
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