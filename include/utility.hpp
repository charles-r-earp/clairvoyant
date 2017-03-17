#ifndef CLAIRVOYANT_CVT_UTILITY_HPP
#define CLAIRVOYANT_CVT_UTILITY_HPP

#include <lambda>
#include <vector>

namespace cvt {

    template<typename T> std::vector<T> map(const std::vector<T>& items, lambda::lambda<T(const T&)> func) {
        
        std::vector<T> mapped(items.size);
        
        auto mapped_it = mapped.begin();
        
        for (auto& item : items) {
            
            *(mapped_it++) = item;
        }
        
        return mapped;
    }
    
    //http://goodliffe.blogspot.com/2013/05/c11-iterating-range-based-for-backwards.html
    template <typename T> class iterate_backwards {
        
        public:
            explicit iterate_backwards(T &t) : t(t) {}
            typename T::reverse_iterator begin() const { return t.rbegin(); }
            typename T::reverse_iterator end()   const { return t.rend(); }
        private:
            const T &t;
    };
        
    template <typename T> iterate_backwards<T> backwards(T &t) {
        return iterate_backwards<T>(t);
    }
}


#endif // CLAIRVOYANT_CVT_UTILITY_HPP