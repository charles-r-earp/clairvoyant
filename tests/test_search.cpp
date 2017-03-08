#include <clairvoyant.hpp>

cvt::StaticGraph<char, int> static_graph {{
    {'A', {{1,'B'}} },
    {'B', {{1, 'A'}, {1, 'C'}, {1, 'D'}} },
    {'C', {{1,'A'}} },
    {'D', {{1,'E'}, {1,'A'}} },
    {'E', {{1, 'B'}} }
}};


cvt::SimpleGraph<char> simple_graph {{
    {'A', {'B'} },
    {'B', {'A','C','D'} },
    {'C', {'A'} },
    {'D', {'E', 'A'} },
    {'E', {'B'} }
}};

int main() {
    
    cvt::Search<cvt::SimpleGraph<char>> simple_search(simple_graph, 'A');
    
    for (auto costed_edge : simple_search.search('E')) {
        std::cout << "Visited: " << costed_edge.second << std::endl;
    }
}