#include <clairvoyant.hpp>

cvt::Graph<char> test_graph {{
    {'A', {'B'}},
    {'B', {'A', 'C', 'D'}},
    {'C', {'A'}},
    {'D', {'E', 'A'}},
    {'E', {'B'}}
}};

int main() {
    cvt::breadth_first_search(test_graph, 'A', 'C');
}