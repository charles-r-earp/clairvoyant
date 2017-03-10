#include <clairvoyant.hpp>


//cvt::model::Model<int, int> test_model{{ [](int x){ return x*x; } }};


int main () {
    
    auto test_model = [](int x){ return x*x; };
    
    for (auto x : {0, 1, 2, 3}) {
        std::cout << x << "^2 = " << test_model(x) << std::endl; 
    }
    
    return 0;
}