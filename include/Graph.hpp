#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <map>
#include <utility>
#include <memory>
#include <functional>


namespace cvt {
    
    // Vertices, edges, and costs constructed before searching
    
    template <typename V, typename C> struct StaticGraph {
        // adapted from http://www.redblobgames.com/pathfinding/a-star/implementation.html
        using Vertex = V;
        using Cost = C;
        using Edge = std::pair<Cost, Vertex>;
        
        using iterator = typename std::vector<Edge>::iterator;
        
        std::map<Vertex, std::vector<Edge> > edges;
        
        inline const std::vector<Edge> neighbors(Vertex v) {
            return this->edges[v];
        }
    };
    
    // Vertices, edges, and costs created on demand
    
    template <typename V, typename C> struct DynamicGraph {
        
        using Vertex = V;
        using Cost = C;
        using Edge = std::pair<Cost, Vertex>;
        
        using iterator = typename std::vector<Edge>::iterator;
        
        /*class Delegate {
            
            public: virtual const std::vector<Edge> neighbors(Vertex v) = 0;
        };*/
        
        using EdgesForVertexCB = std::function<std::vector<Edge>(Vertex)>;
        
        std::map<Vertex, std::vector<Edge> > edges;
        
        /*std::shared_ptr<Delegate> delegate;*/
        
        EdgesForVertexCB edges_cb;
        
        inline const std::vector<Edge> neighbors(Vertex v) {
            
            if (!this->edges.count(v)) {
                
                //this->edges[v] = this->delegate->neighbors(v);
                this->edges[v] = this->edges_cb(v);
            }
            
            return this->edges[v];
        }
    };
        
}
    

#endif // GRAPH_HPP
