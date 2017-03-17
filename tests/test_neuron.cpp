#include <neural_network.hpp>

#include <iostream>


int main () {
    
    std::mt19937 gen;
    std::normal_distribution<> distribution(0, 0.1);
    
    
    cvt::neuron<double> neuron;
    neuron.resize(2, [&](){ return distribution(gen); });
    
    auto line = [](const double &x){ return x + 1; };
    auto func = [&](const double &x, const double &y)->double{ return y > line(x) ? 1 : 0; };
    
    double x, y;

    auto loss = [&](const cvt::math::auto_diff<double>& output){
        return 1/2.0* cvt::math::pow(output - cvt::math::auto_diff<double>( func(x, y) ), 2.0); 
    };
    
    while (true) {
        // train
    
        int n, N = 1000;

        while (++n <= N) {

            x = distribution(gen);
            y = distribution(gen);

            auto output = neuron.process( {x, y} );
            output.derivative = 1;
            
            neuron.train( {x, y}, loss( output ) );

        }

        int u, U = 100;

        double sum;

        while (++u <= U) {

            x = distribution(gen);
            y = distribution(gen);

            sum += loss( neuron.process({x, y}) ).value;
        }

        std::cout << "Mean: " << sum/U << std::endl;
    
    }
    
    
    return 0;
}