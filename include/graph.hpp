#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <queue>
#include <map>
#include <utility>
#include <tuple>
#include <functional>
#include <initializer_list>


#include <iostream>

namespace cvt {
    
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
                
                std::cout << "Visit";
                
                /*
                if (completed(current)) {
                    break;
                }*/
                
                std::cout << "3.1";
                
                for (Type t : graph[current]) {
                    
                    Vertex v = Graph::vertex(t);
                    Cost cost = cost_function(current, t);
                    
                    std::cout << "Open";
                    
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
        
}
    

#endif // GRAPH_HPP
