#include <lambda>
#include <array>
#include <map>
#include <vector>



namespace cvt {

    template<typename V> graph {
        
        using Vertex = V;
        using iterator = std::map<Vertex, std::vector<Vertex> >::iterator;
        
        std::map<Vertex, std::vector<Vertex> > edges;
        
    }
    
    template<typename T, int I> struct neuron {
        
        lambda::lambda<T(T)> activation;
        lambda::lambda<T(T)> inverse_activation;
        
        std::array<T, I> weights;
        T bias;
        
        inline T operator()(std::array<T, I> input) {
            T sum;
            
            int index = 0;
            for (auto in : input) {
                sum += this->weights[index++] * in;
            }
            
            return this->activation((sum + bias)/(I+1));
        }
        
        inline void train(T truth) {
            
            // stuff
        }
    };
    
    template<typename T, int I> neuron<T, I> make_neuron(lambda::lambda<T(T)> activation, lambda::lambda<T(T)> inverse_activation) {
        
        return  neuron<T, I> { activation, inverse_activation };
    }
    
    template<typename T, int I, int O, int HL = 1> struct neural_network {
        
        std::array<neuron<T, I+2>, I> in_layer;
        std::array<std::array<neuron<T, I+2>, I+2>, HL> hidden_layers;
        std::array<neuron<T, 1>, O> out_layer;
        
        
    };
    
    template<typename Sequence, typename T> mul(Sequence<T> sa, const Sequence<T> &sb) {
        
        std::size_t i;
        
        for (auto b : sb) {
            sa[i++] = sb; 
        }
        
        return sa;
    }
    
    template<typename Sequence, typename T> dot(Sequence<T> sa, Sequence<T> sb) {
        
        sa = mul(sa, sb);
        
        T sum;
        
        for (auto a : sa) {
            sum += a;
        }
        
        return sum;
    }
    
    
    
    template<typename T> struct neural_network {
        
        struct meuron {
        
            std::vector<T> weights;
        
            inline T operator()(std::vector<T> inputs) {
                inputs.push_back(1);
                return dot(inputs, weights)/(weights.size());
            }
        }
        
        using Layer = std::vector<neuron>;
        
        std::vector< std::vector<Layer> layers;
        
        lambda::lambda<T(T)> activation, inverse, scale_in, scale_out;
        
        inline std::vector<T> outputs operator()(std::vector<T> inputs) {
            
            std::vector<T> tmp1(inputs.size());
            for (auto in : inputs) {
                tmp1.push_back(scale_down(in));
            }
            
            for (auto layer : this->layers) {
                
                tmp1.resize(sizes[i++]);
                
                for (auto n : layer) {
                    for (auto val : tmp1) {
                        tmp2.push_back(this->activation(n(inputs)));
                    }
                    tmp1 = tmp2;
                    tmp2.clear;
                }
                
                inputs = tmp1;
                tmp1.clear();
            }
            
            return inputs;
        }
        
    }
    
   
    
    
    
    
}