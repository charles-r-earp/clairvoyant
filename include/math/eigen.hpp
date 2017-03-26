#ifndef CLAIRVOYANT_MATH_EIGEN_HPP
#define CLAIRVOYANT_MATH_EIGEN_HPP

#include "auto_double.hpp"

#include <Eigen/Core>

namespace Eigen {
    
    template<> struct NumTraits<cvt::auto_double> : NumTraits<double> {
        
        using Real = cvt::auto_double;
        using NonInteger = cvt::auto_double;
        using Nested = cvt::auto_double;
        
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
        
        inline const auto_double& conj(const auto_double& x)  { return x; }
        inline const auto_double& real(const auto_double& x)  { return x; }
        inline auto_double imag(const auto_double&)    { return 0.; }
        inline auto_double abs2(const auto_double& x)  { return x*x; };


        using auto_matrix = Eigen::Matrix<auto_double, Eigen::Dynamic, Eigen::Dynamic>;
        using matrix = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>;
        using auto_vector = Eigen::Matrix<auto_double, Eigen::Dynamic, 1>;
        using vector = Eigen::Matrix<double, Eigen::Dynamic, 1>;
        
    }
    
}

#endif // CLAIRVOYANT_MATH_EIGEN_HPP
