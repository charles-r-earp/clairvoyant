#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <queue>
#include <map>
#include <set>
#include <utility>
#include <tuple>
#include <functional>
#include <initializer_list>

#include <lambda>

#include <iostream>

namespace cvt {
    
    template<typename V> struct graph {
            
        using Vertex = V;
        
        std::map<Vertex, std::vector<Vertex> > edges;
        
        inline std::size_t count(const Vertex &v) {
            
            return this->edges.count(v);
        }
        
        inline std::vector<Vertex>& operator[](const Vertex &v) {
            
            return this->edges[v];
        }
        
    };
    
    
    
    template<typename V> struct dynamic_graph {
        
        using Vertex = V;
        
        graph<Vertex> graph;
        
        lambda::lambda<std::vector<Vertex>(Vertex)> callback;
        
        inline std::size_t count(const Vertex &v) {
            
            return this->graph.count(v);
        }
        
        inline std::vector<Vertex>& operator[](const Vertex &v) {
            
            if (!this->graph.count(v)) {
                
                this->graph[v] = this->callback(v);
            }
            
            return this->graph[v];
        }
        
    };
    
    /*
    
    template<typename V, typename E = typename vertex_graph<V>::Edge, typename C = int> struct graph_search {
        
        using Vertex = V;
        using Edge = E;
        using Cost = C;
        using Connection = typename graph<Vertex, Edge>::Connection;
        
        mutable lambda::lambda<bool(const Vertex&)> completed = [](const Vertex&)->bool{ return false; };
        mutable lambda::lambda<Cost(const Edge&)> edge_cost = [](const Edge&)->Cost{ return 1; };
        mutable lambda::lambda<Cost(const Vertex&)> heuristic_cost = [](const Vertex&)->Cost{ return 0; };
        
        template<class Graph> bool run(Graph &graph, 
                                  Vertex &current, 
                                  std::map<Vertex, std::pair<Vertex, Edge> > &visited,
                                  std::map<Vertex, Cost> &cost_map) const {

            using Node = std::pair<Cost, Connection>;
            
            std::priority_queue<Node, std::vector<Node>, std::greater<Node> > frontier;

            do {
                if (!frontier.empty()) {
                    current = frontier.top().second.second;
                    frontier.pop();
                }

                if (this->completed(current)) {
                    return true;
                }

               for (Connection connection : graph.get(current)) {

                    Edge e = connection.first;
                    Cost cost = this->edge_cost(e);
                    Vertex v = connection.second;
                    
                    //std::cout << " cost: " << cost << std::endl; 

                    if (!cost_map.count(v) || cost < cost_map.at(v)) {

                        Cost heuristic = this->heuristic_cost(v);
                        frontier.push(std::make_pair(cost + heuristic, connection));
                        visited[v] = std::make_pair(current, e);
                        cost_map[v] = cost;
                    }

                }

                //std::cout << "End... Frontier size: " << frontier.size() << std::endl;
            } while(!frontier.empty());
            
            return false;

        }
        
        template<typename Graph>
        inline std::vector<Connection> path(Graph &graph, const Vertex &start) {
            std::map<Vertex, std::pair<Vertex, Edge> > visited;
            Vertex current = start;
            std::map<Vertex, Cost> cost_map;
            this->run(graph, current, visited, cost_map);
            
            return reconstruct_path(visited, current);
        }

        inline void set_goal(const Vertex &goal) {
            this->completed = [goal](Vertex v) { return same(v, goal); };
        }

        inline void  set_fixed_edge_cost(const Cost &cost) {
            this->edge_cost = [cost](Edge)->Cost{ return cost; };
        }               
    };
    
    */
    
    
    
    
    
    
    
   
        
}
    

#endif // GRAPH_HPP
