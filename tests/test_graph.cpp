#include <graph.hpp>

cvt::vertex_graph<char> graph1 { {
        {'A', {'B'} },
        {'B', {'A','C','D'} },
        {'C', {'A'} },
        {'D', {'E', 'A'} },
        {'E', {'B'} }, 
}};

cvt::graph<char, int> graph2 {{
    {'A', {{1,'B'}} },
    {'B', {{1, 'A'}, {1, 'C'}, {1, 'D'}} },
    {'C', {{1,'A'}} },
    {'D', {{1,'E'}, {1,'A'}} },
    {'E', {{1, 'B'}} }
}};

int main() {
    
    cvt::graph_search<char> search;
    search.set_goal('A');
    
    for (auto connection : search.min_cost_path(graph1, 'E')) {
        std::cout << connection.first.first << " -> " << connection.first.second << std::endl;
        //std::cout << " -[ " << connection.first << " ]-> " << connection.second;
    }
    
    std::cout << std::endl;
    
    
    
    return 0;
}

