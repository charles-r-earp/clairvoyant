#include <neural_network/neural_network.hpp>

#include <iostream>

int main() {

    using namespace cvt;
    
    neural_network network;
    auto activation = [](const auto_double& z){ return log(1 + exp(z)); };
    auto loss = [](const eigen::auto_vector& a, const eigen::auto_vector& y){ 
        
        return 1/2.0 * (a - y).dot(a - y);
    };
    
    network.reshape({2, 1}, activation);
    network.input_range = {0, 1};
    network.output_range = {0, 1};
    network.activation_range = {0, 1};
    network.loss = loss;
    
    for (auto& layer : network.layers) {
    
        std::cout << layer.weights << std::endl;
    }
    
    std::random_device rd;
    std::uniform_real_distribution<double> uniform(0, 1);
    
    // train 
    
    auto line = [](double x){ return x; };
    auto func = [&](double x, double y) -> double { return y > line(x) ? 1 : 0; };
                                                   
    
    double x, y, target, output1, output2;
    
    eigen::vector inputs(2, 1), targets(1, 1);
    
    // evaluate 
    
    int e, E = 10;
    
    auto evaluate = [&](bool print = false){ 
        
        double sum = 0;
        
        e = 0;
        
        while (e < E) {
            
            x = uniform(rd);
            y = uniform(rd);

            inputs << x, y;
            
            target = func(x, y);

            output1 = network.process(inputs)(0, 0);

            sum += std::abs(output1 - target);
            
            if (print) {
        
                std::cout << "target: " << target << " output: " << output1 << std::endl;
            }
        
            ++e;
        }
        
        
        
        
        return sum/E;
        
    };
    
    // train
    
    int t = 0;
    
    double error = 1;
    
    while (error > 0.1) {
    
        x = uniform(rd);
        y = uniform(rd);
        
        target = func(x, y);
        
        inputs << x, y;
        
        targets << target;
        
        network.train(inputs, targets);
        
        if (t % 100 == 0) {
        
            error = evaluate();
            
            std::cout << "epoch " << t << ": error = " << error << std::endl;
        }
        
        ++t;
    }
    
    // validate
    
    std::cout << "mean: " << evaluate(true) << std::endl;

    return 0;
}