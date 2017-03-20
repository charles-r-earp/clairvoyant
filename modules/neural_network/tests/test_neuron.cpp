#include <neural_network.hpp>
#include <lambda.hpp>
#include <iostream>

#include <random>


int main() {
    
    using cvt::neural_network::auto_vector;
    using cvt::neural_network::auto_double;
    
    // setup
    
    std::random_device rd;
    std::normal_distribution<double> gaussian(0, 0.1);
    
    cvt::neural_network::neuron neuron;
    neuron.activation = [](const auto_double& z) {
        using cvt::neural_network::log;
        using cvt::neural_network::exp;
        
        return log(1 + exp(z));
        //return 1/(1 + exp(-z));
    };
    
    //auto_double u(2, 1);
    
    //std::cout << "partial of activation at u = 2: " << u.partial([&](){ return neuron.activation(u); }) << std::endl;
    
    neuron.reshape(2, [&](){ return gaussian(rd); });
    
    auto loss = [](const auto_double& output, const auto_double& target) {
        
        using cvt::neural_network::pow;
        
        
        auto_double result = pow(output - target, 2);
        
        std::cout << "loss_func(" << output << ", " << target << ") = " << result << std::endl;
        
        return result;
    };
    
    
    // target
    
    auto line = [](double x) { return 2*x - 0.1; };
    
    auto above_line = [&](double x, double y)->double{ 
    
        return y > line(x) ? 1.0 : 0;
    };
    
    // train
    
    std::cout << "training..." << std::endl;
    
    std::uniform_real_distribution<double> uniform(0, 1);
    
    int t, T = 10000; 
    
    while (++t <= T) {
        
        //std::cout << "loop" << std::endl;
        
        double x = uniform(rd), y = uniform(rd);
        auto_vector pt(2, 1);
        pt << x, y;
        
        auto_double target = above_line(x, y);
        
        std::cout << "pt: " << pt << std::endl << "target: " << target << std::endl;
        
        auto_double output = neuron.process(pt);
        
        auto_double loss_gradient = output.partial( [&](){ return loss(output, target); });
        
        std::cout << "before: wts= " << neuron.weights(0, 0) << " " << neuron.weights(1, 0) << " output= " << output
            << " loss gradient= " << loss_gradient << std::endl;
        
        
    
        neuron.train(pt, loss_gradient);
        
        output = neuron.process(pt);
        
        std::cout << "after: wts= " << neuron.weights(0, 0) << " " << neuron.weights(1, 0) << " output= " << output << std::endl;
    }
    
    
    // evaluate
    std::cout << "evaluating... " << std::endl;
    
    int e, E = 10;
    
    double sum;
    
    while (e++ <= E) {
        
        double x = uniform(rd), y = uniform(rd);
        auto_vector pt(2, 1);
        pt << x, y;
        
        auto_double output = neuron.process(pt);
        auto_double target = above_line(x, y);
        
    
        sum += loss(output, target).value;
        
        std::cout << "target: " << target << " output: " << output << std::endl;
    }
    
    std::cout << "mean: " << sum/E  << std::endl;
    return 0;
}