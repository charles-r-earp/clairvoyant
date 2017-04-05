#ifndef CLAIRVOYANT_MATH_MATH_HPP
#define CLAIRVOYANT_MATH_MATH_HPP

#include "adouble.hpp"
#include "eigen.hpp"

#include <cmath>

namespace cvt {

    template<typename T> struct range {
        
        T start;
        T end;
        
        T dist() const { 
        
            return this->end - this->start;
        }
    };
    
    template <typename TX, typename TY> TY map_min_max(const TX& x, const range<TX>& x_range, const range<TY>& y_range) {

        return y_range.dist() * (x - x_range.start)/x_range.dist() + y_range.start;
    }
    
    template <typename T> T clamp(const T& x, const range<T>& x_range) {
    
        return std::min(std::max(x, x_range.start), x_range.end);
    }
}

#endif // #define CLAIRVOYANT_MATH_MATH_HPP