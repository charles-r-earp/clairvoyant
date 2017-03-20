#include <neural_network.hpp>



int main() {
    
    using cvt::neural_network::auto_double;
    
    auto_double x = 1;
    
    auto func = [&](){ 
        
        using cvt::neural_network::log;
        using cvt::neural_network::exp;
    
        return log(1 + exp(x));
    };
    
    
    
    std::cout << " softplus(x) at x = " << x << " => " << x.partial(func) << std::endl;
    
    return 0;
}