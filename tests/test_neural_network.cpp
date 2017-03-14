#include <neural_network.hpp>

#include <iostream>

#include <chrono>
#include <ratio>


int main () {
    
    
    std::vector<double> inputs;
    
    int I = 1080*1920;
    for (int i = 0; i < I; ++i) {
        inputs.push_back(i/I);
    }
    
    cvt::neural_network<double> network;
    int L = 10;
    int N = I;
    std::vector<std::size_t> shape(L, N);
    
    network.reshape(shape);
    
    std::cout << "Processing...";
    auto t1 = std::chrono::high_resolution_clock::now();
    auto outputs = network(inputs);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << " done.\n";
    
    // fractional duration: no duration_cast needed
    std::chrono::duration<double> dt = t2 - t1;
    
    std::cout << "Time is " << dt.count() << " seconds.\n";
    std::cout << "Output length: " << outputs.size() << std::endl;
    
    return 0;
}