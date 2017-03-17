#include <math.hpp>


#include <iostream>



int main() {

    cvt::math::auto_diff<double> x(2, 1);
    
    std::cout << "1/(1+e^-" << x << ") = " << 1.0/(1.0 + cvt::math::exp(-x)) << std::endl;
    
    return 0;
}