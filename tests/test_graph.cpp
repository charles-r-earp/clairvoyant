#include <graph.hpp>

cvt::graph<char> graph { {
        {'A', {'B'} },
        {'B', {'A','C','D'} },
        {'C', {'A'} },
        {'D', {'E', 'A'} },
        {'E', {'B'} }, 
}};

int main() {
    
    
    
    return 0;
}

