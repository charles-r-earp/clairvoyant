#ifndef CLAIRVOYANT_CVT_MATH_AUTO_DIFF_HPP
#define CLAIRVOYANT_CVT_MATH_AUTO_DIFF_HPP

#include <cmath>

namespace cvt {
    
    namespace neural_network {
                              
        // Automatic Differentiation
        
        template<typename T> struct auto_diff {
            
            T value;
            T derivative;
            
            auto_diff(T value = 0, T derivative = 0) {
                
                this->value = value;
                this->derivative = derivative;
            }
            
            auto_diff<T> operator-() const { 
                return T(-1) * (*this);
            }
            
            template<typename T2> auto_diff<T> operator-(const T2& other) const {
                
                auto_diff<T> other_diff(other);
                
                return auto_diff(this->value + other_diff.value, this->derivative + other_diff.derivative);
            }
            
            
            friend inline std::ostream& operator<<(std::ostream& os, const auto_diff<T>& a_diff) {
                
                return (os << a_diff.value << "|" << a_diff.derivative);
            }
        
        };
        
        // + 
        
        template<typename T> auto_diff<T> operator+(const auto_diff<T>& lhs, const auto_diff<T>& rhs) {
        
            auto_diff<T> result;
                
            result.value = lhs.value + rhs.value;
            result.derivative = lhs.derivative + rhs.derivative;
                
            return result;
        }
        
        template<typename T> auto_diff<T> operator+(const T& lhs, const auto_diff<T>& rhs) {
        
            return auto_diff<T>(lhs) + rhs;
        }
        
        // *
        
        template<typename T> auto_diff<T> operator*(const auto_diff<T>& lhs, const auto_diff<T>& rhs) {
        
            auto_diff<T> result;
                
            result.value = lhs.value * rhs.value;
            result.derivative = lhs.derivative * rhs.value + lhs.value * rhs.derivative;
                
            return result;
        }
        
        template<typename T> auto_diff<T> operator*(const T& lhs, const auto_diff<T>& rhs) {
        
            return auto_diff<T>(lhs) * rhs;
        }
        
        // pow
        
        template<typename T> auto_diff<T> pow(const auto_diff<T>& base, const auto_diff<T>& exp) {
            
            auto_diff<T> result;
            
            result.value = std::pow(base.value, exp.value);
            result.derivative = base.derivative * exp.value * std::pow(base.value, exp.value - 1);
            
            return result;
        }
        
        template<typename T> auto_diff<T> pow(const T& base, const auto_diff<T>& exp) {
            
            return pow(auto_diff<T>(base), exp);
        }
        
        template<typename T> auto_diff<T> pow(const auto_diff<T>& base, const T& exp) {
            
            return pow(base, auto_diff<T>(exp));
        }
        
        // exp
        
        template<typename T> auto_diff<T> exp(const auto_diff<T>& x) {
            
            auto_diff<T> result;
            
            result.value = std::exp(x.value);
            result.derivative = x.derivative * std::exp(x.value);
            
            return result;
        }
        
        // /
        
        template<typename T> auto_diff<T> operator/(const auto_diff<T>& lhs, const auto_diff<T>& rhs) {
        
            return lhs * pow(rhs, T(-1));
        }
        
        template<typename T> auto_diff<T> operator/(const T& lhs, const auto_diff<T>& rhs) {
        
            return auto_diff<T>(lhs) / rhs;
        }
        
        template<typename T> auto_diff<T> operator/(const auto_diff<T>& lhs, const T& rhs) {
        
            return lhs / auto_diff<T>(rhs);
        }
    }

}

#endif // CLAIRVOYANT_CVT_MATH_AUTO_DIFF_HPP