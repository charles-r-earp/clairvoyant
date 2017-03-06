#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_map>


namespace cvt {
    
    // adapted from http://www.redblobgames.com/pathfinding/a-star/implementation.html
    
    template <typename Vertex> struct Graph {
        
        using iterator = typename std::vector<Vertex>::iterator;
        
        std::unordered_map<Vertex, std::vector<Vertex> > edges;
        
        inline const std::vector<Vertex> neighbors(Vertex v) {
            return this->edges[v];
        }
    };
    
    
};

#endif // GRAPH_HPP