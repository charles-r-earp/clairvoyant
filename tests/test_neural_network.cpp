#include <neural_network/neural_network.hpp>

#include <iostream>
#include <random>

int main() {


    cvt::neural_network network({2, 1});
    
    for (auto& layer : network.layers) {
        layer.activation = [](const cvt::adouble& z) { return 1.0/(1.0 + exp(-z)); };
    }
    
    network.layers.back().activation = [](const cvt::adouble& z) { return clamp(z, {0.0, 1.0}); };
    
    network.loss = [](const cvt::eigen::avector& outputs, const cvt::eigen::avector& targets) {
        
        
        return (outputs - targets).squaredNorm();
        
        /*
        cvt::adouble sum = 0;
        
        
        
        for (int row = 0; row < outputs.size(); ++row) {
            sum += pow(outputs(row, 0) - targets(row, 0), 2.0);
        }*/
        
        //std::cout << "loss() " << outputs(0, 0) << " " << targets(0, 0) << " >> " << sum << std::endl;
        
        //return sum;
    };
    
    auto func = [](double x, double y) {
        return x > y ? 1 : 0;
    };
    
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0, 1);
    
    // train
    for (int i = 0; i < 100000; ++i) {
        
        double x = distribution(generator), y = distribution(generator);
        
        cvt::eigen::avector inputs(2, 1);
        inputs << x, y;
        
        cvt::eigen::avector targets(1, 1);
        targets << func(x, y);
        
        cvt::eigen::avector gradients = network.train(inputs, targets);
        
        //std::cout << x << " " << y << " >> " << targets(0, 0) << " "
         //   << "gradients: " << gradients(0, 0) << " " << gradients(1, 0) << std::endl; 
    }
    
    int N = 10;
    double sum = 0;
    
    for (int i = 0; i < N; ++i) {
        
        double x = distribution(generator), y = distribution(generator);
        
        cvt::eigen::avector inputs(2, 1);
        inputs << x, y;
        
        cvt::eigen::avector outputs = network.process(inputs);
        
        cvt::eigen::avector targets(1, 1);
        targets << func(x, y);
        
        double error = abs(outputs(0, 0) - targets(0, 0)).value;
        
        std::cout << "target: " << targets(0, 0) << " output: " << outputs(0, 0) << std::endl;
        
        sum += error;
    }
    
    std::cout << "mean: " << sum / N << std::endl;
}