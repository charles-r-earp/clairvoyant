#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <iostream>
#include <queue>
#include <unordered_set>

#include "Graph.hpp"

namespace cvt {
    
    template <typename Graph> void breadth_first_search(Graph graph, typename Graph::Vertex start, typename Graph::Vertex goal) {
    
        using Vertex = typename Graph::Vertex;
        using Edge = typename Graph::Edge;
        
        std::queue<Vertex> frontier;
        frontier.push(start);
        
        std::unordered_set<Vertex> visited;
        visited.insert(start);
        
        while(!frontier.empty()) {
            auto current = frontier.front();
            frontier.pop();
            
            std::cout << "Visiting " << current << std::endl;
            
            if (current == goal) {
                break;
            }
            
            for (auto next_edge : graph.neighbors(current)) {
                
                Vertex next = next_edge.second;
                
                if (!visited.count(next)) {
                    frontier.push(next);
                    visited.insert(next);
                }
            }
        }
    }
    
    template <typename Graph> void a_star_action_search(Graph graph, typename Graph::Vertex start, typename Graph::Vertex goal) {
    
        using Vertex = typename Graph::Vertex;
        using Edge = typename Graph::Edge;
        
        std::priority_queue<Edges> frontier;
        frontier.push(start);
        
        //std::unordered_set<Vertex> visited;
        //visited.insert(start);
        
        std::map<Vertex, Edge> visited_edges;
        
        while(!frontier.empty()) {
            auto current = frontier.front();
            frontier.pop();
            
            std::cout << "Visiting " << current << std::endl;
            
            if (current == goal) {
                break;
            }
            
            for (auto next_edge : graph.neighbors(current)) {
                
                Vertex next = next_edge; 
                
                if (!visited_edges.count(next)) {
                    frontier.push(next_edge);
                    visited_edges.insert(next_edge);
                }
            }
        }
    }
    
}


#endif // SEARCH_HPP
