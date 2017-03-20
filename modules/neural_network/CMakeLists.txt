add_library(neural_network INTERFACE)

find_package(lambda CONFIG REQUIRED COMPONENTS lambda)
#include_directories(include ${lambda_INCLUDE_DIRS})

target_include_directories(neural_network INTERFACE include ${lambda_INCLUDE_DIRS})
target_sources(neural_network INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/neural_network.hpp)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
target_link_libraries(neural_network INTERFACE Eigen3::Eigen)



add_executable(test_neural_network tests/test_neural_network.cpp)
target_link_libraries(test_neural_network neural_network)

add_executable(test_neuron tests/test_neuron.cpp)
target_link_libraries(test_neuron neural_network)

add_executable(test_derivative tests/test_derivative.cpp)
target_link_libraries(test_derivative neural_network)