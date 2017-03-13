#include <lambda>

#include <iostream>

int main() {
    
    lambda::lambda<void(std::string)> lambda { [](std::string s){ std::cout << s << std::endl; } };
    
    lambda("Hello World!");
    
    return 0;
}
