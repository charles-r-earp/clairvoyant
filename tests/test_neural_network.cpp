#include <neural_network.hpp>

#include <iostream>


int main () {
    
    std::mt19937 gen;
    std::normal_distribution<double> distribution(0, 0.5);
    
    cvt::neural_network<double> network;
    network.reshape({2, 1});
    
    auto line = [](const double &x){ return x + 1; };
    auto func = [&](const double &x, const double &y)->double{ return y > line(x) ? 1 : 0; };
    
    double x, y;

    auto loss = [&](const std::vector<cvt::math::auto_diff<double> >& outputs){
        return  cvt::math::sum_of_squares(subtract(outputs, {func(x, y)}) );
    };
    
    while (true) {
        // train
    
        int n, N = 1000;

        while (++n <= N) {

            x = distribution(gen);
            y = distribution(gen);
            
            network.train({x, y}, loss);

        }

        int u, U = 100;

        double sum;

        while (++u <= U) {

            x = distribution(gen);
            y = distribution(gen);

            sum += loss( network.process({x, y}) ).value;
        }

        std::cout << "Mean: " << sum/U << std::endl;
    
    }
    
    
    return 0;
}