#include <array>
#include <functional>
#include <utility>



namespace cvt {
    
    namespace model {
        
        template<typename IT, typename OT> struct Model {

            using Input = IT;
            using Output = OT;
            
            inline const Output operator()(const Input&) {
                return this->function(Input);
            }
            
            // Implementation
            
            std::function<Output(const Input&)> function;
            
        }; 
        
    }
}