#include "math.hpp"
#include "utility.hpp"

//#include <lambda>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

#include <iostream>

namespace cvt {
    
    template<typename T = double> struct neuron {
        
        std::vector<math::auto_diff<T> > weights;
        math::auto_diff<T> bias;
        
        using ActivationFunction = lambda::lambda<math::auto_diff<T>(const math::auto_diff<T>&)>;
        
        mutable ActivationFunction activation = [](const math::auto_diff<T>& z){
            return T(1)/(T(1) + math::exp(-1.0*z)); 
        };
        
        
        inline math::auto_diff<T> process(const std::vector<math::auto_diff<T> >& inputs) const {
            
            assert(inputs.size() == this->weights.size());
            
            return this->activation(math::dot(this->weights, inputs) + this->bias);
        }
        
        inline void resize(const std::size_t &size, lambda::lambda<T()> get_weight) {
            
            this->weights.resize(size);
            
            for (auto &wt : this->weights) {
                
                wt.value = get_weight();
            }
        }
        
        inline std::vector<math::auto_diff<T> > train(const std::vector<math::auto_diff<T> > &inputs, const math::auto_diff<T> &output_diff) {
            
            std::vector<math::auto_diff<T> > losses(this->weights.size());
            
            auto loss_it = losses.begin();
            
            for (auto& wt : this->weights) {
                
                // compute partial derivative
                wt.derivative = 1;
                
                wt.value -= (*(loss_it++) = this->process(inputs) * output_diff).derivative;
                
                wt.derivative = 0;
            }
            
            // repeat for bias
            
            bias.derivative = 1;
            
            bias.value -= (this->process(inputs) * output_diff).derivative;
            
            bias.derivative = 0;
            
            return losses;
        }
        
        /*inline T train(const std::vector<T>& inputs, LossFunction loss) {
            
            return this->train(map(inputs, [](const T& in){ return math::auto_diff<T>(in); }), loss).first().value;
        }*/
    
    };

    template<typename T> struct neuron_layer {
        
        using LossFunction = lambda::lambda<math::auto_diff<T>(const std::vector<math::auto_diff<T> >&)>;
        
        std::vector<neuron<T> > neurons;
        
        std::vector<math::auto_diff<T> > saved_inputs;
        
        inline std::vector<math::auto_diff<T> > process(const std::vector<math::auto_diff<T> >& inputs, bool save = false) {
            
            if (save) {
                
                this->saved_inputs = inputs;
            }
            
            return {}; // map(this->neurons, [&](const neuron<T>& n){ return n.process(inputs); });
        }
        
        inline void resize(const std::size_t &inputs_size, const std::size_t &size, lambda::lambda<T()> get_weight) {
            
            this->neurons.resize(size);
            
            for (auto& n : this->neurons) {
                n.resize(inputs_size, get_weight);
            }
        }
        
        inline std::vector< std::vector<math::auto_diff<T> > > train(std::vector<math::auto_diff<T> > &output_diff) {
            
            assert(output_diff.size() == this->neurons.size());
            
            auto out_it = output_diff.begin();
            
            return map(this->neurons, [&](const neuron<T>& n){ return n.train(saved_inputs, *(out_it++)); });
        }
        
        inline std::vector< std::vector<math::auto_diff<T> > > train(LossFunction loss) {
            
            auto outputs = this->process(this->saved_inputs);
            
            return this->train(map(outputs, [&](const math::auto_diff<T>& out){ 
                
                out.derivative = 1;
                math::auto_diff<T> output_diff = loss(outputs);
                out.derivative = 0;
                
                return output_diff;
            }));
        }
    };
    
    
    template<typename T> struct neural_network {
        
        using LossFunction = typename neuron_layer<T>::LossFunction;
        
        std::vector<neuron_layer<T> > layers;
        
        std::mt19937 gen;
        mutable std::normal_distribution<T> distribution = std::normal_distribution<T>(0, 0.1);
        
        inline std::vector<math::auto_diff<T> > process(const std::vector<math::auto_diff<T> >& inputs, bool save = false) {
            
            auto outputs = inputs;
            
            for (auto& layer : this->layers) {
                
                outputs = layer.process(outputs, save);
            }
            
            return outputs;
        }
        
        inline std::vector< std::vector<math::auto_diff<T> > > 
            train(const std::vector<math::auto_diff<T> >& inputs, LossFunction loss) {
            
            // forward pass
            
            auto outputs = this->process(inputs, true); // saves the inputs in each layer
            
            // backward pass
            
            std::vector< std::vector<math::auto_diff<T> > > auto_diff_mat;
            
            /*
            for (auto& layer : backwards(this->layers)) {
                
                if (!auto_diff_mat.size()) {
                    auto_diff_mat = layer.train(loss);
                }
                else {
                    auto_diff_mat = layer.train(auto_diff_mat);
                }
            }*/
            
            return auto_diff_mat;
        }
        
        inline void reshape(const std::vector<std::size_t> &shape) {
            
            // shape is number of inputs, then the number of neurons for each layer
            
            // resize layers vector to match shape
            this->layers.resize(shape.size());
            
            auto shape_it = shape.begin();
            
            for (auto &layer : this->layers) {
                
                layer.resize(*shape_it, *(++shape_it), [&](){ return distribution(gen); }); 
                
            }
        }
        
    };
    
   
    
    
    
    
}