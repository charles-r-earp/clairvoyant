#ifndef CLAIRVOYANT_MATH_ADOUBLE_HPP
#define CLAIRVOYANT_MATH_ADOUBLE_HPP

#include <lambda.hpp>
#include <cmath>
#include <iostream>

namespace cvt {

    struct adouble {
            
        double value, derivative;
            
        adouble(double value = 0, double derivative = 0) {

            this->value = value;
            this->derivative = derivative;
        }

        adouble partial(lambda::lambda<adouble()> func) {

            this->derivative = 1;
            auto result = func();
            this->derivative = 0;
            
            //std::cout << "partial: " << result << std::endl;

            return result;
        }

        friend inline std::ostream& operator<<(std::ostream& os, const adouble& ad) {

            return (os << ad.value << "|" << ad.derivative);
        }

    };
    
    inline bool operator==(const adouble& lhs, const adouble& rhs) {
    
        return lhs.value == rhs.value;
    }
    
    inline bool operator<(const adouble& lhs, const adouble& rhs) {
        
        return lhs.value < rhs.value;
    }
    
    inline bool operator>(const adouble& lhs, const adouble& rhs) {
        
        return lhs.value > rhs.value;
    }

    inline adouble operator+(const adouble& lhs, const adouble& rhs) {

        adouble result;

        result.value = lhs.value + rhs.value;
        result.derivative = lhs.derivative + rhs.derivative;

        return result;
    }

    inline adouble operator+=(adouble& lhs, const adouble& rhs) {

        return lhs = lhs + rhs;
    }

    inline adouble operator-(const adouble& lhs, const adouble& rhs) {

        adouble result;

        result.value = lhs.value - rhs.value;
        result.derivative = lhs.derivative - rhs.derivative;

        return result;
    }

    inline adouble operator-=(adouble& lhs, const adouble& rhs) {

        return lhs = lhs - rhs;
    }

    inline adouble operator-(const adouble& rhs) {

        adouble result;

        result.value = -rhs.value;
        result.derivative = -rhs.derivative;

        return result;
    }

    inline adouble operator*(const adouble& lhs, const adouble& rhs) {

        adouble result;

        result.value = lhs.value * rhs.value;
        result.derivative = lhs.derivative * rhs.value  + lhs.value * rhs.derivative;

        return result;
    }

    inline adouble operator/(const adouble& lhs, const adouble& rhs) {

        //std::cout << lhs << " / " << rhs << std::endl;

        adouble result;

        result.value = lhs.value / rhs.value;
        result.derivative = (lhs.derivative * rhs.value - lhs.value * rhs.derivative)/(rhs.value * rhs.value);

        //assert(!isnan(result.value));
        //assert(!isnan(result.derivative));

        if (isnan(result.value)) {

            result.value = std::nexttoward(0, lhs.value > 0 ? 1 : -1);
        }

        if (isnan(result.derivative)) {

            result.derivative = std::nexttoward(0, lhs.value > 0 ? 1 : -1);
        }


        return result;
    }

    inline adouble pow(const adouble& base, const adouble& exp) {

        adouble result;

        result.value = std::pow(base.value, exp.value);
        result.derivative = base.derivative * exp.value * std::pow(base.value, exp.value - 1);

        if (exp.derivative != 0) {

            assert(base.value > 0);
            result.derivative += exp.derivative * std::pow(base.value, exp.value) * std::log(base.value);
        }


        return result;
    }

    inline adouble sqrt(const adouble& x) {

        return pow(x, 0.5);
    }

    inline adouble exp(const adouble& exp) {

        adouble result;

        result.value = std::exp(exp.value);
        result.derivative = exp.derivative * std::exp(exp.value);

        return result;
    }

    inline adouble log(const adouble& x) {

        adouble result;

        result.value = std::log(x.value);
        result.derivative = x.derivative/x.value;

        return result;
    }

    inline adouble abs(const adouble& val) {

        adouble result;

        result.value = std::abs(val.value);
        result.derivative = std::abs(val.derivative);

        return result;
    }

    inline adouble max(const adouble& a, const adouble& b) {

        adouble result;

        result.value = std::max(a.value, b.value);
        result.derivative = a.derivative * (a.value >= b.value ? 1 : 0) + b.derivative * (b.value >= a.value ? 1 : 0);

        return result;
    }

    inline adouble tan(const adouble& x) {

        adouble result;

        result.value = std::tan(x.value);

        return result;
    }

    inline adouble atan(const adouble& x) {

        adouble result;

        result.value = std::atan(x.value);
        result.derivative = x.derivative /(x.value*x.value + 1);

        return result;
    }

    inline adouble tanh(const adouble& x) {

        adouble result;

        result.value = std::tanh(x.value);
        result.derivative = x.derivative * std::pow(std::cosh(x.value), -2);

        return result;
    }
 
}

#endif // CLAIRVOYANT_MATH_ADOUBLE_HPP