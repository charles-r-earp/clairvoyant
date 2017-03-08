#include <clairvoyant.hpp>

cvt::StaticGraph<char, int> static_graph {{
    {'A', {{1,'B'}} },
    {'B', {{1, 'A'}, {1, 'C'}, {1, 'D'}} },
    {'C', {{1,'A'}} },
    {'D', {{1,'E'}, {1,'A'}} },
    {'E', {{1, 'B'}} }
}};


int main() {
    cvt::breadth_first_search(static_graph, 'A', 'C');
}