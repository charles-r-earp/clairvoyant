cmake_minimum_required (VERSION 3.1)
project(clairvoyant)

set (CMAKE_CXX_STANDARD 11)

add_library(clairvoyant INTERFACE)

target_sources(clairvoyant INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/clairvoyant.hpp)

find_package(lambda REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${lambda_INCLUDE_DIRS})

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
target_link_libraries(clairvoyant INTERFACE Eigen3::Eigen)

# Tests

add_subdirectory(tests)

#add_executable(test_neural_network tests/test_neural_network.cpp)
#target_link_libraries(test_neural_network clairvoyant)