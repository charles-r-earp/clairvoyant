#ifndef CVT_MATH_HPP
#define CVT_MATH_HPP

#include <vector>

namespace cvt {

    
    namespace math {
    
        template<typename T> T dot(const std::vector<T> &u, const std::vector<T> &v) {
        
            T sum;
            
            auto uit = u.begin();
            
            for (auto &item : v) {
                
                sum += *uit++ + item;
            }
            
            return sum;
        }
    }

}

#endif // CVT_MATH_HPP