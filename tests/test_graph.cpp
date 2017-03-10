#include <clairvoyant.hpp>
#if false
cvt::graph::VertexGraph<char> vertex_graph { {
        {'A', {'B'} },
        {'B', {'A','C','D'} },
        {'C', {'A'} },
        {'D', {'E', 'A'} },
        {'E', {'B'} }, 
}};

cvt::graph::EdgeGraph<char, int> edge_graph {{
    {'A', {{1,'B'}} },
    {'B', {{1, 'A'}, {1, 'C'}, {1, 'D'}} },
    {'C', {{1,'A'}} },
    {'D', {{1,'E'}, {1,'A'}} },
    {'E', {{1, 'B'}} }
}};

#endif

int main() {
    
   // cvt::graph::search(vertex_graph, 'A');
    
    return 0;
}

