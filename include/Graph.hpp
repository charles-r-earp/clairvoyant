#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <map>
#include <utility>
<<<<<<< HEAD
=======
#include <memory>
>>>>>>> cbfb70bb3d4401b8cede278f40feeea1c4c96db6
#include <functional>


namespace cvt {
    
    // Vertices, edges, and costs constructed before searching
    
<<<<<<< HEAD
    template <typename V, typename A> struct StaticGraph {
        
=======
    template <typename V, typename C> struct StaticGraph {
        // adapted from http://www.redblobgames.com/pathfinding/a-star/implementation.html
>>>>>>> cbfb70bb3d4401b8cede278f40feeea1c4c96db6
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
    
<<<<<<< HEAD
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
    
=======
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
>>>>>>> cbfb70bb3d4401b8cede278f40feeea1c4c96db6
    

#endif // GRAPH_HPP
