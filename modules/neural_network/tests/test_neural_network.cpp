#include <neural_network.hpp>
#include <lambda.hpp>
#include <iostream>

#include <random>


int main() {
    
    // setup
    
    std::random_device rd;
    std::normal_distribution<double> gaussian(0, 0.1);
    
    cvt::neural_network::network<cvt::neural_network::layer<cvt::neural_network::neuron> > network;
    
    Eigen::VectorXi shape(3, 1);
    shape << 1, 100, 1;
    
    std::cout << shape << std::endl;
    
    network.reshape(shape, [&](){ return gaussian(rd); });
    
    int i = 1;
    
    using cvt::neural_network::auto_vector;
    using cvt::neural_network::auto_double;
    
    for (auto& layer : network.layers) {
        
        for (auto& neuron : layer.neurons) {
            
            if (i < network.layers.size()) {
            
                // hidden layers
                neuron.activation = [](const cvt::neural_network::auto_double& z) {
                    
                    assert(!isnan(z.value));
                    assert(!isnan(z.derivative));
                
                    using cvt::neural_network::log;
                    using cvt::neural_network::exp;
                    
                    
                    
                    auto_double result = 1/(1 + exp(-z));//log(1 + exp(z));
                    
                    //std::cout << "z = " << z << " result = " << result << std::endl;
                    
                    return result;
                };
            }
            else {
                
                // output layer
                neuron.activation = [](const cvt::neural_network::auto_double& z) {
                
                    return z;
                };
            }
            
            ++i;
        }
    }
    
    
    
    // target
    
    double x_min = 0, x_max = 1;
    
    std::uniform_real_distribution<double> uniform(x_min, x_max);
    
    auto func = [&](double x)->double{ 
    
        //return 0.2 + 0.4 * x*x + 0.3*x* std::sin(15*x) + 0.05 * std::cos(50*x);
        
        return std::sin(x) * std::sin(x);
    };
    
    double y_min = 0, y_max = 1;
    
    auto scale_up = [&](const auto_double& x)->auto_double{
    
        return x;
    };
    
    auto scale_down = [&](const auto_double& x)->auto_double{
    
        return x / x_max;
    };
    
    
    network.loss = [&](const auto_vector& outputs, const auto_vector& targets) {
        
        auto_double loss;
        
        for (int i = 0; i < outputs.size(); ++i) {
        
            loss += pow(outputs(i, 0) - targets(i, 0), 2.0);
        }
        
        using cvt::neural_network::clamp;
        
        loss.value = clamp(loss.value/outputs.size(), -100, 100);
        loss.derivative = clamp(loss.derivative/outputs.size(), -100, 100);
        
        return loss;
    };
    
    
    // train
    
    std::cout << "training..." << std::endl;
    
    
    
    auto evaluate = [&](){
        int e = 0, E = 10;
    
        double sum;

        while (e++ <= E) {

            double x = uniform(rd);
            auto_vector pt(1, 1);
            pt << scale_down(x);

            auto_vector result = network.process(pt);

            double output = result(0, 0).value;
            double target = func(x);


            sum += std::abs(output - target);

            std::cout << "target: " << target << " output: " << output << std::endl;
            
        }
        
        return sum/E;
    };
    
    int t = 0, T = 1000;
    
    while (t <= T) {
        
        double x = uniform(rd);
        auto_vector pt(1, 1);
        pt << scale_down(x);
        
        auto_vector targets(1, 1);
        targets << func(x);
        
        //std::cout << "pt: " << pt << std::endl << "a: " << a << std::endl;
    
        network.train(pt, targets);
        
        if (int(t) % 100 == 0)
            std::cout << "Epoch: " << t << " mean: " << evaluate() << std::endl;
        
        ++t;
    }
    
    
    // validate
    //std::cout << "validating... " << std::endl;
    
    int e, E = 10;
    
    double sum;

    while (e++ <= E) {

        double x = uniform(rd);
        auto_vector pt(1, 1);
        pt << x;

        auto_vector result = network.process(pt);

        double output = result(0, 0).value;
        double target = func(x);


        sum += std::abs(output - target);

        std::cout << "target: " << target << " output: " << output << std::endl;

    }
    
    std::cout << "mean: " << sum/E  << std::endl;
    
    return 0;
}