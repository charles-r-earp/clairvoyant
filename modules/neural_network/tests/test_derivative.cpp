#include <neural_network.hpp>



int main() {
    
    using cvt::neural_network::auto_double;
    
    auto_double x = -881.203;
    
    auto func = [&](){ 
        
        using cvt::neural_network::log;
        using cvt::neural_network::exp;
    
        return 1/(1 + exp(-x));
    };
    
    
    
    std::cout << " sigmoid at x = " << x << " => " << x.partial(func) << std::endl;
    
    return 0;
}