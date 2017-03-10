#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <queue>
#include <map>
#include <utility>
#include <functional>
#include <initializer_list>


#include <iostream>


namespace cvt {
    
    namespace graph {
        
        template <typename V> struct VertexGraph {
        
            using Vertex = V;
            using Type = V;
            
            std::map<Vertex, std::vector<Type> > connected;
            
            inline static Vertex vertex(const Type &t) {
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
            
            inline const int count(const Vertex &v) {
                return this->connected.count(v);
            }

            inline std::vector<Type> operator[](const Vertex &v) { 
                return this->connected[v];
            }
        };
        

        template <typename Graph, typename Callback> struct DynamicGraph {

            using Vertex = typename Graph::Vertex;
            using Type = typename Graph::Type;

            Graph graph;
            Callback callback;
            
            inline static Vertex vertex(const Type &t) {
                return Graph::vertex(t);
            }
            
            inline const int count(const Vertex &v) {
                return this->graph.count(v);
            }

            inline std::vector<Type> operator[](const Vertex &v) { 

                if (!this->count(v)) {
                    this->graph[v] = this->callback(v);
                }

                return this->graph[v];
            }

        };
        
        // search
        
        template <typename Graph, typename Cost = int> 
        std::vector<typename Graph::Type> search(Graph graph, 
               const typename Graph::Vertex &start, 
               std::function<bool(typename Graph::Vertex)> completed = [](typename Graph::Vertex v) { return false; },
               std::function<Cost(typename Graph::Vertex, typename Graph::Type)> cost_function 
                                                 = [](typename Graph::Vertex v, typename Graph::Type t) { return 1; },
               std::function<Cost(typename Graph::Vertex)> cost_heuristic = [](typename Graph::Vertex v) { return 0; }) {
            
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
            //frontier.push(std::make_pair(zero, current));
            //cost_map[current] = zero;
            
            bool init = false;
            
            do {
                if (init) {
                    current = frontier.top().second;
                    frontier.pop();
                }
                
                init = true;
                
                std::cout << "Visiting: " << current << std::endl;
                
                if (completed(current)) {
                    break;
                }
                
                for (Type t : graph[current]) {
                    
                    Vertex v = Graph::vertex(t);
                    Cost cost = cost_function(current, t);
                    
                    std::cout << "\tOpening: " << v << std::endl;
                    
                    if (!cost_map.count(v) || cost < cost_map.at(v)) {
                        
                        Cost heuristic = cost_heuristic(v);
                        
                        frontier.push(std::make_pair(cost + heuristic, v));
                        visited[v] = std::make_pair(current, t);
                        cost_map[v] = cost;
                    }
                    
                }
                
                
            } while(!frontier.empty());
            
            std::vector<typename Graph::Type> path;
            
            while (current != start) {
                
                std::cout << "Reconstructing: " << current << std::endl;
                
                std::pair<Vertex, Type> pair = visited.at(current);
                
                path.push_back(pair.second);
                
                current = pair.first;
            }
            
            return path;
        }
            
                                         
    }
        
}
    

#endif // GRAPH_HPP
