#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_map>
#include <map>
#include <utility>
#include <functional>


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
    
    template <typename V, typename C, typename A> struct ActionGraph {
    
        using Vertex = V;
        using Cost = C;
        using Action = A;
        
        using Edge = std::tuple<Cost, Vertex, Action>;
        
        using iterator = typename std::vector<Edge>::iterator;
        
        std::map<Vertex, std::vector<Edge> > edges;
        
        using NeighborsCallBack = std::function<std::vector<Edge>(Vertex v)>;
        
        NeighborsCallBack neighbors_cb; 
        
        inline const sd::vector<Edge> neighbors(Vertex v) {
            
            if (!this->edges.count(v)) {
                this->edges[v] = this->neighbors_cb(v);
            }
           
            return this->edges[v];
        }
    }
    
    
};

#endif // GRAPH_HPP
