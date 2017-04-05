#ifndef CLAIRVOYANT_MATH_EIGEN_HPP
#define CLAIRVOYANT_MATH_EIGEN_HPP

#include "adouble.hpp"

#include <Eigen/Core>

namespace Eigen {
    
    template<> struct NumTraits<cvt::adouble> : NumTraits<double> {
        
        using Real = cvt::adouble;
        using NonInteger = cvt::adouble;
        using Nested = cvt::adouble;
        
        enum {
            IsComplex = 0,
            IsInteger = 0,
            IsSigned = 1,
            RequireInitialization = 1,
            ReadCost = 1,
            AddCost = 3,
            MulCost = 3
        };
        
    };
}

namespace cvt {
    
    namespace eigen { 
        
        inline const adouble& conj(const adouble& x)  { return x; }
        inline const adouble& real(const adouble& x)  { return x; }
        inline adouble imag(const adouble&)    { return 0.; }
        inline adouble abs2(const adouble& x)  { return x*x; };


        using amatrix = Eigen::Matrix<adouble, Eigen::Dynamic, Eigen::Dynamic>;
        using matrix = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
        using avector = Eigen::Matrix<adouble, Eigen::Dynamic, 1>;
        using vector = Eigen::Matrix<double, Eigen::Dynamic, 1>;
        
    }
    
}

#endif // CLAIRVOYANT_MATH_EIGEN_HPP
