#include <clairvoyant.hpp>

using Vertex = char;
using Cost = int;
using Edge = std::pair<Cost, Vertex>;
        
using iterator = typename std::vector<Edge>::iterator;

std::unordered_map<Vertex, std::vector<Edge> > edges {
    {'A',  {{1, 'B'}} }
};


cvt::StaticGraph<char, int> test_graph1 {{
    {'A', {{1, 'B'}} }
}};

cvt::StaticGraph<char, int> test_graph {{
    {'A', {{1,'B'}} },
    {'B', {{1, 'A'}, {1, 'C'}, {1, 'D'}} },
    {'C', {{1,'A'}} },
    {'D', {{1,'E'}, {1,'A'}} },
    {'E', {{1, 'B'}} }
}};

int main() {
    cvt::breadth_first_search(test_graph, 'A', 'C');
}