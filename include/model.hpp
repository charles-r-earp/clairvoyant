#include <array>
#include <functional>
#include <utility>



namespace cvt {
    
    namespace model {
        
        /*template<typename IT, typename OT> struct Model {

            using Input = IT;
            using Output = OT;
            using Function = std::function<OT(IT)>;
            
            inline const Output operator()(Input input) {
                return this->function(input);
            }
            
            // Implementation
            
            Function function;
            
        }; */
        
        template<typename IT, typename OT> using Model = std::function<OT(IT)>;
        
        template<typename S, typename A> using StateModel = Model<S, std::pair<S, A> >;
    }
}