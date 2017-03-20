#include <neural_network.hpp>
#include <lambda.hpp>
#include <iostream>

#include <random>


int main() {
    
    // setup
    
    std::random_device rd;
    std::normal_distribution<double> gaussian(0, 0.1);
    
    cvt::neural_network::network<cvt::neural_network::layer<cvt::neural_network::neuron> > network;
    
    Eigen::Vector2i shape(2, 1);
    
    std::cout << shape << std::endl;
    
    network.reshape(shape, [&](){ return gaussian(rd); });
    
    for (auto& layer : network.layers) {
        
        for (auto& neuron : layer.neurons) {
            
            neuron.activation = [](const cvt::neural_network::auto_double& z) {
                
                using cvt::neural_network::log;
                using cvt::neural_network::exp;

                return log(1 + exp(z));
                //return 1/(1 + exp(-z));
            };
        }
    }
    
    using cvt::neural_network::auto_vector;
    
    network.loss = [](const auto_vector& outputs, const auto_vector& targets) {
        
        return (outputs - targets).dot(outputs - targets);
    };
    
    
    
    // target
    
    auto line = [](double x) { return 2*x + 0.1; };
    
    auto above_line = [&](double x, double y)->double{ 
    
        return y > line(x) ? 1.0 : 0;
    };
    
    // train
    
    std::cout << "training..." << std::endl;
    
    std::uniform_real_distribution<double> uniform(0, 1);
    
    int t, T = 1000;
    
    while (++t <= T) {
        
        //std::cout << "loop" << std::endl;
        
        double x = uniform(rd), y = uniform(rd);
        auto_vector pt(2, 1);
        pt << x, y;
        
        auto_vector a(1, 1);
        a << above_line(x, y);
        
        std::cout << "pt: " << pt << std::endl << "a: " << a << std::endl;
    
        network.train(pt, a);
    }
    
    
    // evaluate
    std::cout << "evaluating... " << std::endl;
    
    int e, E = 10;
    
    double sum;
    
    while (e++ <= E) {
        
        double x = uniform(rd), y = uniform(rd);
        auto_vector pt(2, 1);
        pt << x, y;
        
        auto_vector result = network.process(pt);
        
        double output = result(0, 0).value;
        double target = above_line(x, y);
        
    
        sum += std::pow(output - target, 2.0);
        
        std::cout << "target: " << target << " output: " << output << std::endl;
    }
    
    std::cout << "mean: " << sum/E  << std::endl;
    
    return 0;
}