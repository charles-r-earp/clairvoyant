#include <math/math.hpp>


int main() {
    
    cvt::eigen::auto_matrix m(1, 3);
    m << 1, 2, 3;
    
    cvt::eigen::auto_vector u(3, 1);
    u << 1,
         2,
         3;
    std::cout 
        << "m = " << std::endl
        << m << std::endl
        << "u = " << std::endl
        << u << std::endl
        << "m * u = " << std::endl
        << m * u << std::endl;

    return 0;
}