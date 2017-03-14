#include "math.hpp"

#include <lambda>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

#include <iostream>

namespace cvt {
    
    // utility function
    template<typename T, typename F> void _resize(std::vector<T> &v, std::size_t size, F fill) {
        
        std::size_t current = v.size();

        if (current > size) {

            v.resize(size);
        }
        else if (current < size) {
            
            v.resize(size);
            for_each(v.end() + current - size, v.end(), [&](const T&){ return fill(); });
        }
    }
    
    template<typename T> void _resize(std::vector<T> &v, std::size_t size) {
        
        _resize(v, size, [](void){ return T(); });
    }
    
    template<typename T> struct neuron {
        
        std::vector<T> weights;
        T bias;
        
        std::vector<T> last_inputs;
        
        mutable T learning_rate = 1;
        mutable lambda::lambda<T(T)> activation = [](const T &z){ return 1/(1 + std::exp(-z)); };
        
        mutable std::default_random_engine generator;
        mutable std::normal_distribution<T> distribution = std::normal_distribution<T>(0, 0.1);
    
        inline T operator()(const std::vector<T> &inputs){
            
            // store inputs for later
            //this->last_inputs = inputs;
            
            
            // run operation
            return this->activation(math::dot(this->weights, inputs) + this->bias);
        }
        
        inline void resize(const std::size_t &size) {
            _resize(this->weights, size, [&](void)->T{ return distribution(generator); });
        }
    };

    template<typename T> struct neuron_layer {
        
        std::vector<neuron<T> > neurons;
        
        std::vector<T> last_inputs;
        
        inline std::vector<T> operator()(const std::vector<T> &inputs) {
            
            // store inputs for later
            this->last_inputs = inputs;
            
            std::vector<T> outputs;
            outputs.reserve(this->neurons.size());
            
            for (auto n : this->neurons) {
                outputs.push_back(n(inputs));
            }
            
            return outputs;
        }
        
        inline void resize(const std::size_t &input_size, const std::size_t &size) {
            
            _resize(this->neurons, size);
            
            for (auto n : this->neurons) {
                n.resize(input_size);
            }
        }
        
    };
    
    template<typename T> struct neural_network {
        
        std::vector<neuron_layer<T> > layers;
        
        // shape starts with input layer, and ends with the output layer
        // it corresponds to the number of neurons in that layer. 
        std::vector<std::size_t> shape;
        
        std::vector<T> last_inputs;
        
        inline std::vector<T> operator()(std::vector<T> inputs) {
        
            // store for later
            //this->last_inputs = inputs;
            
            for (auto &layer : layers) {
                inputs = layer(inputs);
            }
            
            return inputs;
        }
        
        inline void reshape(const std::vector<std::size_t> &shape) {
            
            // resize layers vector to match shape
            _resize(this->layers, this->shape.size());
            
            // shape iterator
            auto shape_it = this->shape.begin();
            
            for (auto &layer : this->layers) {
                
                layer.resize(*shape_it, *(shape_it+1)); 
                
                ++shape_it;
            }
        }
        
    };
    
   
    
    
    
    
}