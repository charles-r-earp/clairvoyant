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
    
}


#endif // SEARCH_HPP