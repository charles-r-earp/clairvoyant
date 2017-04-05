#include <neural_network/mnist.hpp>
#include <neural_network/neural_network.hpp>

const cvt::range<unsigned char> pixel_value_range = {0, 255};
//const int num_pixels = 28 * 28;
//const int num_training_images = 60000;
//const int num_testing_images = 10000;

const std::string training_images_path = "train-images.idx3-ubyte";
const std::string training_labels_path = "train-labels.idx1-ubyte";

const std::string testing_images_path = "train-images.idx3-ubyte";
const std::string testing_labels_path = "train-labels.idx1-ubyte";

int main() {
    
    // load data
    int num_training_images, num_pixels;
    std::cout << "Reading training images..." << std::endl;
    unsigned char** training_images = cvt::read_mnist_images(training_images_path, num_training_images, num_pixels);
    std::cout << "Reading training labels..." << std::endl;
    unsigned char* training_labels = cvt::read_mnist_labels(training_labels_path, num_training_images);
    
    int num_testing_images;
    std::cout << "Reading testing images..." << std::endl;
    unsigned char** testing_images = cvt::read_mnist_images(testing_images_path, num_testing_images, num_pixels);
    std::cout << "Reading testing labels..." << std::endl;
    unsigned char* testing_labels = cvt::read_mnist_labels(testing_labels_path, num_testing_images);
    
    // make nn
    cvt::neural_network network({num_pixels, num_pixels, 10});
    
    for (auto& layer : network.layers) {
        layer.activation = [](const cvt::adouble& z) { return 1.0/(1.0 + exp(-z)); };
    }
    
    network.layers.back().activation = [](const cvt::adouble& z) { return clamp(z, {0.0, 1.0}); };
    
    network.loss = [](const cvt::eigen::avector& outputs, const cvt::eigen::avector& targets) {
        
        return (outputs - targets).squaredNorm();
        
        /*/
        cvt::adouble sum = 0;
        
        for (int row = 0; row < outputs.size(); ++row) {
            sum += pow(outputs(row, 0) - targets(row, 0), 2.0);
        }
        
        return sum;*/
    };
    
    cvt::eigen::avector inputs(num_pixels, 1), targets(10, 1);
    
    // train 
    std::cout << "Starting training..." << std::endl;
    
    for (int i = 0; i < 1/*num_training_images*/; ++i) {
        
        for (int row = 0; row < num_pixels; ++row) {
            
            inputs(row, 0) = map_min_max(training_images[i][row], pixel_value_range, cvt::range<double>{0.0, 1.0});
        }
        
        targets = cvt::eigen::avector::Zero(10, 1);
        int digit = training_labels[i];
        targets(digit, 0) = 1;
        
        network.train(inputs, targets);
        
        if (i % 600 == 0) std::cout << "Training... " << i/600 << "%" << std::endl;
    }
    
    
    // test
    
    std::cout << "Starting testing..." << std::endl;
    
    cvt::eigen::avector results;
    int num_correct = 0;
    
    for (int i = 0; i < 1/*num_testing_images*/; ++i) {
        
        for (int row = 0; row < num_pixels; ++row) {
            
            inputs(row, 0) = map_min_max(training_images[i][row], pixel_value_range, cvt::range<double>{0.0, 1.0});
        }
        
        int digit = training_labels[i];
        
        //results = network.process(inputs);
        
        int row, col;
        
        cvt::adouble val = 0;//results.maxCoeff(&row, &col);
        
        if (row == digit) ++num_correct;
        
        
        if (i % 600 == 0) std::cout << "Testing... " << i/600 << "%" << std::endl;
    }
    
    std::cout << "Correct: " << 100.0 * num_correct/double(num_testing_images);
    
    return 0;
}