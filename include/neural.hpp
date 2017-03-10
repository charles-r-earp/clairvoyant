#include <array>
#include <functional>



namespace cvt {
    
    namespace neural {
        
        
        
        template<typename T, int I, int O> Network {
            
            // Conforms to Model
            
            using InputType = T;
            using OutputType = T;
            using Inputs = I;
            using Outputs = O;

            using Input = std::array<T, I>;
            using Output = std::array<T, O>;
            
            inline const Output operator()(const Input&) {
                // query the network
                return Output();
            }
            
            // Implementation
            
           // NeuralNetwork nn; 
        };
        
        template<typename Network> Model<Network::Input, Network::Output {
            
            using Input = using Network::Input;
            using Output = using Network::Output;
            
            Network network;
            
            inline const Output operator()(const Input&) {
                return this->network(Input);
            }
        }
        
    }
}