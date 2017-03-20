#ifndef CLAIRVOYANT_CVT_NEURAL_NETWORK_AUTO_DOUBLE_HPP
#define CLAIRVOYANT_CVT_NEURAL_NETWORK_AUTO_DOUBLE_HPP

#include <cmath>
#include <iostream>
#include <lambda.hpp>

namespace cvt {

    namespace neural_network {
        
        //class auto_double;
        //const auto_double e = 2.7182818284590452353602875, pi = 3.1415926535897932384626, one = 1.0, two = 2.0;
        
        
        struct auto_double {
            
            double value, derivative;
            
            auto_double(double value = 0, double derivative = 0) {
            
                this->value = value;
                this->derivative = derivative;
            }
            
            auto_double partial(lambda::lambda<auto_double()> func) {
        
                this->derivative = 1;
                auto result = func();
                this->derivative = 0;
                
                std::cout << " partial(" << *this << ")= " << result << std::endl;
            
                return result;
            }
            
            friend inline std::ostream& operator<<(std::ostream& os, const auto_double& ad) {
                
                return (os << ad.value << "|" << ad.derivative);
            }
        
        };
        
        inline auto_double operator+(const auto_double& lhs, const auto_double& rhs) {
            
            auto_double result;
            
            result.value = lhs.value + rhs.value;
            result.derivative = lhs.derivative + rhs.derivative;
            
            return result;
        }
        
        inline auto_double operator+=(auto_double& lhs, const auto_double& rhs) {
            
            return lhs = lhs + rhs;
        }
        
        inline auto_double operator-(const auto_double& lhs, const auto_double& rhs) {
            
            auto_double result;
            
            result.value = lhs.value - rhs.value;
            result.derivative = lhs.derivative - rhs.derivative;
            
            return result;
        }
        
        inline auto_double operator-=(auto_double& lhs, const auto_double& rhs) {
            
            return lhs = lhs - rhs;
        }
        
        inline auto_double operator-(const auto_double& rhs) {
        
            auto_double result;
            
            result.value = -rhs.value;
            result.derivative = -rhs.derivative;
            
            return result;
        }
        
        inline auto_double operator*(const auto_double& lhs, const auto_double& rhs) {
            
            auto_double result;
            
            result.value = lhs.value * rhs.value;
            result.derivative = lhs.derivative * rhs.value  + lhs.value * rhs.derivative;
            
            return result;
        }
        
        inline auto_double operator/(const auto_double& lhs, const auto_double& rhs) {
            
            auto_double result;
            
            result.value = lhs.value / rhs.value;
            result.derivative = (lhs.derivative * rhs.value - lhs.value * rhs.derivative)/(rhs.value * rhs.value);
            
            return result;
        }
        
        inline auto_double pow(const auto_double& base, const auto_double& exp) {
            
            auto_double result;
            
            result.value = std::pow(base.value, exp.value);
            result.derivative = base.derivative * exp.value * std::pow(base.value, exp.value - 1);
            
            if (exp.derivative != 0) {
            
                assert(base.value > 0);
                result.derivative += exp.derivative * std::pow(base.value, exp.value) * std::log(base.value);
            }
                             
            
            return result;
        }
        
        inline auto_double exp(const auto_double& exp) {
            
            auto_double result;
            
            result.value = std::exp(exp.value);
            result.derivative = exp.derivative * std::exp(exp.value);
            
            return result;
        }
        
        inline auto_double log(const auto_double& x) {
        
            auto_double result;
            
            result.value = std::log(x.value);
            result.derivative = x.derivative/x.value;
            
            return result;
        }
        
        inline auto_double abs(const auto_double& val) {
        
            auto_double result;
            
            result.value = std::abs(val.value);
            result.derivative = std::abs(val.derivative);
            
            return result;
        }
        
        inline auto_double max(const auto_double& a, const auto_double& b) {
        
            auto_double result;
            
            result.value = std::max(a.value, b.value);
            result.derivative = a.derivative * (a.value >= b.value ? 1 : 0) + b.derivative * (b.value >= a.value ? 1 : 0);
            
            return result;
        }
        
    }
}

#endif // CLAIRVOYANT_CVT_NEURAL_NETWORK_AUTO_DOUBLE_HPP