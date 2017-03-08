#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <map>
#include <utility>
#include <functional>


namespace cvt {
    
    // adapted from http://www.redblobgames.com/pathfinding/a-star/implementation.html
    
    template <typename V, typename A> struct StaticGraph {
        
        using Vertex = V;
        using Action = A;
        using Edge = std::pair<Vertex, Action>;
        
        using iterator = typename std::vector<Edge>::iterator;
        
        std::map<Vertex, std::vector<Edge> > edges;
        
        inline static Vertex extract(Edge e) {
            return e.first;
        }
        
        inline const int count(Vertex v) const {
            return this->edges(v);
        }
        
        inline std::vector<Edge> operator[](Vertex v) {
            return this->edges[v];
        }
    };
    
    template <typename V> struct SimpleGraph {
        using Vertex = V;
        using Edge = Vertex;
        
        using iterator = typename std::vector<Edge>::iterator;
        
        std::map<Vertex, std::vector<Edge> > edges;
        
        inline static Vertex extract(Edge e) {
            return e;
        }
        
        inline const int count(Vertex v) const {
            return this->edges(v);
        }
        
        inline std::vector<Edge> operator[](Vertex v) {
            return this->edges[v];
        }
    };
    
    template <typename Graph> struct DynamicGraph {
        
        using Vertex = typename Graph::Vertex;
        using Edge = typename Graph::Edge;
        
        using NeighborsCallBack = std::function<std::vector<Edge>(Vertex)>;
        
        Graph graph;
        
        NeighborsCallBack neighbors_cb;
        
        inline static Vertex extract(Edge e) {
            return e.first;
        }
        
        const int count(Vertex v) const {
            return this->graph.count(v);
        }
        
        inline std::vector<Edge> operator[](Vertex v) {
            
            if (!this->graph.count(v)) {
                this->graph[v] = this->neighbors_cb(v);
            }
            
            return this->graph[v];
        }
    };
    
   /* template <typename V, typename C, typename A> struct ActionGraph {
    
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
    }*/
    
    
};

#endif // GRAPH_HPP
