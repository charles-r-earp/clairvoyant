#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_map>
#include <utility>


namespace cvt {
    
    // adapted from http://www.redblobgames.com/pathfinding/a-star/implementation.html
    
    template <typename V, typename C> struct StaticGraph {
        
        using Vertex = V;
        using Cost = C;
        using Edge = std::pair<Cost, Vertex>;
        
        using iterator = typename std::vector<Edge>::iterator;
        
        std::unordered_map<Vertex, std::vector<Edge> > edges;
        
        inline const std::vector<Edge> neighbors(Vertex v) {
            return this->edges[v];
        }
    };
    
    
};

#endif // GRAPH_HPP
