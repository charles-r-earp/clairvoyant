#include <array>
#include <functional>



namespace cvt {
    
    namespace model {
        
        template<typename T, typename I, typename O> struct AbstractModel {
            
            using Type = T;
            using Inputs = I;
            using Outputs = O;
            
            const std::function<std::array<Type, Outputs>(const std::array<Type, Inputs> inputs)> function;
            
            inline const std::array<Type, Outputs> operator(const std::array<Type, Inputs> inputs) {
                this->function(inputs);
            }
        }
    }
}