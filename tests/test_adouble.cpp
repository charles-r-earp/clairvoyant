#include <math/adouble.hpp> 

#include <iostream>

int main() {
    
    cvt::adouble x = 2;
    
    x.partial([&]{ return 1/(1 + exp(-x)); });
    
    return 0;
}