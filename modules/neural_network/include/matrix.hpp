#ifndef CLAIRVOYANT_CVT_NEURAL_NETWORK_MATRIX_HPP
#define CLAIRVOYANT_CVT_NEURAL_NETWORK_MATRIX_HPP

#include "auto_double.hpp"

#include <Eigen/Core>

namespace Eigen {
    
    template<> struct NumTraits<cvt::neural_network::auto_double> : NumTraits<double> {
        
        using Real = cvt::neural_network::auto_double;
        using NonInteger = cvt::neural_network::auto_double;
        using Nested = cvt::neural_network::auto_double;
        
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
    
    namespace neural_network {
    
        inline const auto_double& conj(const auto_double& x)  { return x; }
        inline const auto_double& real(const auto_double& x)  { return x; }
        inline auto_double imag(const auto_double&)    { return 0.; }
        //inline auto_double abs(const auto_double&  x)  { return abs(x); }
        inline auto_double abs2(const auto_double& x)  { return x*x; }
        
        
        using auto_matrix = Eigen::Matrix<auto_double, Eigen::Dynamic, Eigen::Dynamic>;
        using auto_vector = Eigen::Matrix<auto_double, Eigen::Dynamic, 1>;
    }
}

#endif // CLAIRVOYANT_CVT_NEURAL_NETWORK_MATRIX_HPP