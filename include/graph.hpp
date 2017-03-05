#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <stddef>
#include <memory>
#include <vector>


namespace cvt {
    
    template <std::size_t D, typname T, typename P> class Graph {
    
        class Edge;
        
        public: class Node {
            
            public: Vector<D, T> coord; // coordinates
            
            public: P pay; // payload 
            
            public: std::vector<Edge> edges;
        };
        
        public: class Edge {
            public: std::shared_ptr<Node> start, end;
            
            T cost;
        }
        
        
        using Path = std::vector<Edge>;
    };
    
    
};

#endif // GRAPH_HPP