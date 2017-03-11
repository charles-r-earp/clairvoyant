#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <queue>
#include <map>
#include <utility>
#include <tuple>
#include <functional>
#include <initializer_list>

#include <lambda>

#include <iostream>

namespace cvt {
    
    template<typename T> bool same(T a, T b) {
        return a < b == b < a;
    }
    
    template<typename V, typename E> struct graph {
            
        using Vertex = V;
        using Edge = E; 
        using Connection = std::pair<Edge, Vertex>;
        
        std::map<Vertex, std::vector<Connection> > connections;
        
        inline std::vector<Connection> operator[](const Vertex &v) {
            return this->connections[v];
        }
    };
    
    template<typename V> struct vertex_graph {
        
        using Vertex = V;
        using Edge = std::pair<Vertex, Vertex>;
        using Connection = std::pair<Edge, Vertex>;
        
        std::map<Vertex, std::vector<Vertex> > connected_vertices;
        
        inline std::vector<Connection> operator[](const Vertex &v) { 
            std::vector<Connection> connections;
            for (auto next : this->connected_vertices[v]) {
                connections.push_back(std::make_pair(std::make_pair(v, next), next) );
            }
            return connections;
        }
    };
    
    template<typename V, typename E> struct dynamic_graph {
        
        using Vertex = V;
        using Edge = E;
        using Connection = typename graph<Vertex, Edge>::Connection;
        
        graph<Vertex, Edge> storage;
        lambda::lambda<std::vector<Connection>(Vertex)> callback;
        
        inline std::vector<Connection> operator[](const Vertex &v) {
            
            if (!this->storage.count(v)) {
                this->storage[v] = this->callback(v);
            }
            
            return this->connections[v];
        }
    };
    
    template<typename V, typename E = typename vertex_graph<V>::Edge, typename C = int> struct graph_search {
        
        using Vertex = V;
        using Edge = E;
        using Cost = C;
        
        lambda::lambda<bool(Vertex)> completed = [](Vertex)->bool{ return false; };
        lambda::lambda<Cost(Edge)> edge_cost = [](Edge)->Cost{ return 1; };
        lambda::lambda<Cost(Vertex)> heuristic_cost = [](Vertex)->Cost{ return 0; };
        
        
        template<class Graph> auto min_cost_path(Graph graph, Vertex start) -> std::vector<typename Graph::Connection> {
            return search(graph, start, completed, edge_cost, heuristic_cost);
        }
        
        inline const void set_goal(Vertex goal) {
            this->completed = [goal](Vertex v) { return same(v, goal); };
        }
        
    };
    
    template<class Graph, typename Cost = int> 
       auto search(Graph graph, 
               typename Graph::Vertex start, 
               lambda::lambda<bool(typename Graph::Vertex)> completed,
               lambda::lambda<Cost(typename Graph::Edge)> edge_cost = [](typename Graph::Edge)->Cost{ return 1; },
               lambda::lambda<Cost(typename Graph::Vertex)> heuristic_cost = [](typename Graph::Vertex)->Cost{ return 0; }
                ) -> std::vector<typename Graph::Connection> {
    
        using Vertex = typename Graph::Vertex;
        using Edge = typename Graph::Edge;
        using Connection = typename Graph::Connection;
        using Node = std::pair<Cost, Connection>;
            
            
        // construct containers
            
        std::priority_queue<Node, std::vector<Node>, std::greater<Node> > frontier;
        std::map<Vertex, std::pair<Vertex, Edge> > visited;
        std::map<Vertex, Cost> cost_map;
            
        // initialize
            
        Vertex current = start;
            
        bool init = false;
            
        //std::cout << "Searching...";
            
        do {
            if (init) {
                current = frontier.top().second.second;
                frontier.pop();
            }
                
            init = true;
                
            //std::cout << "Visiting: " << current << std::endl;
                
          //  std::cout << "Visit";
                
            
            if (completed(current)) {
                break;
            }
                
        //    std::cout << "3.1";
                
            for (Connection connection : graph[current]) {
                    
                Edge e = connection.first;
                Cost cost = edge_cost(e);
                Vertex v = connection.second;
                
          //      std::cout << "Open";
                    
                //std::cout << "\tOpening: " << v << std::endl;
                
                if (!cost_map.count(v) || cost < cost_map.at(v)) {
                        
                    Cost heuristic = heuristic_cost(v);
                        
                    frontier.push(std::make_pair(cost + heuristic, connection));
                    visited[v] = std::make_pair(current, e);
                    cost_map[v] = cost;
                }
                    
            }
                
                
        } while(!frontier.empty());
            
        std::vector<Connection> path;
            
        while (!same(current, start)) {
                
           // std::cout << "Reconstructing: " << current << std::endl;
                
            auto pair = visited.at(current);
                
            path.push_back(std::make_pair(pair.second, current) );
                
            current = pair.first;
        }
        
        std::reverse(path.begin(), path.end());
            
        return path;
         
    }
    
    
    
    
    
   #if false 
    namespace graph {
        
        
        
        template <typename V> struct VertexGraph {
        
            using Vertex = V;
            using Edge = V;
            using Type = V;
            
            std::map<Vertex, std::vector<Type> > connected;
            
            inline static Vertex vertex(const Type &t) {
                return t;
            }
            
            inline static Vertex edge(const Type &t) {
                return t;
            }
            
            inline const int count(const Vertex &v) {
                return this->connected.count(v);
            }

            inline std::vector<Type> operator[](const Vertex &v) { 
                return this->connected[v];
            }
        };
        
        template <typename V, typename E> struct EdgeGraph {
        
            using Vertex = V;
            using Edge = E;
            using Type = std::pair<Edge, Vertex>;
            
            std::map<Vertex, std::vector<Type> > connected;
            
            inline static Vertex vertex(const Type &t) {
                return t.second;
            }
            
            inline static Edge edge(const Type &t) {
                return t.first;
            }
            
            inline const int count(const Vertex &v) {
                return this->connected.count(v);
            }

            inline std::vector<Type> operator[](const Vertex &v) { 
                return this->connected[v];
            }
        };
        

        template <typename G, typename C> struct DynamicGraph {

            using Graph = G;
            using Callback = C;
            
            using Vertex = typename Graph::Vertex;
            using Edge = typename Graph::Edge;
            using Type = typename Graph::Type;

            Graph graph;
            Callback callback;
            
            inline static Vertex vertex(const Type &t) {
                return Graph::vertex(t);
            }
            
            inline static Edge edge(const Type &t) {
                return Graph::edge(t);
            }
            
            inline const int count(const Vertex &v) {
                return this->graph.count(v);
            }

            inline std::vector<Type> operator[](const Vertex &v) { 
                std::cout << "10";
                if (!this->count(v)) {
                    std::cout << "10-a";
                    this->graph[v] = this->callback(v);
                    std::cout << "10-b";
                }

                return this->graph[v];
            }

        };
        
        // rebase
        
        template<typename Graph> void rebase(Graph &graph, typename Graph::Vertex base) {
            // trims edges not reachable from base
        }
        
        // search
        
        template <typename Graph, typename Cost = int, typename Completed, typename CostFunction, typename CostHeuristic> 
        std::vector<typename Graph::Type> search(Graph graph, 
               const typename Graph::Vertex &start, 
               Completed completed = [](typename Graph::Vertex v) { return false; },
               CostFunction cost_function = [](typename Graph::Vertex v, typename Graph::Type t) { return 1; },
               CostHeuristic cost_heuristic = [](typename Graph::Vertex v) { return 0; }) {
            
            using Vertex = typename Graph::Vertex;
            using Type = typename Graph::Type;
            using Node = std::pair<Cost, Type>;
            
            
            // construct containers
            
            std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier;
            std::map<Vertex, std::pair<Vertex, Type> > visited;
            std::map<Vertex, Cost> cost_map;
            
            // initialize
            
            Vertex current = start;
            Cost zero;
            
            bool init = false;
            
            std::cout << "Searching...";
            
            do {
                if (init) {
                    current = Graph::vertex(frontier.top().second);
                    frontier.pop();
                }
                
                init = true;
                
                //std::cout << "Visiting: " << current << std::endl;
                
                //std::cout << "Visit";
                
                /*
                if (completed(current)) {
                    break;
                }*/
                
                //std::cout << "3.1";
                
                for (Type t : graph[current]) {
                    
                    Vertex v = Graph::vertex(t);
                    Cost cost = cost_function(current, t);
                    
                    //std::cout << "Open";
                    
                    //std::cout << "\tOpening: " << v << std::endl;
                    
                    if (!cost_map.count(v) || cost < cost_map.at(v)) {
                        
                        Cost heuristic = cost_heuristic(v);
                        
                        frontier.push(std::make_pair(cost + heuristic, t));
                        visited[v] = std::make_pair(current, t);
                        cost_map[v] = cost;
                    }
                    
                }
                
                
            } while(!frontier.empty());
            
            std::vector<typename Graph::Type> path;
            
            while (current < start != start < current) {
                
               // std::cout << "Reconstructing: " << current << std::endl;
                
                std::pair<Vertex, Type> pair = visited.at(current);
                
                path.push_back(pair.second);
                
                current = pair.first;
            }
            
            return path;
        }
            
                                         
    }
    
    #endif
        
}
    

#endif // GRAPH_HPP
