#ifndef CLAIRVOYANT_CVT_UTILITY_HPP
#define CLAIRVOYANT_CVT_UTILITY_HPP

#include <lambda>
#include <vector>

namespace cvt {

    template<typename T1, typename T2> std::vector<T2> map(const std::vector<T1>& items, lambda::lambda<T2(T1&)> func) {
        
        std::vector<T2> mapped(items.size);
        
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
            typename T::reverse_iterator begin() { return t.rbegin(); }
            typename T::reverse_iterator end() { return t.rend(); }
        private:
            const T &t;
    };
        
    template <typename T> iterate_backwards<T> backwards(T &t) {
        return iterate_backwards<T>(t);
    }
}


#endif // CLAIRVOYANT_CVT_UTILITY_HPP