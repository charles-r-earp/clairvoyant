#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <iostream>
#include <queue>
#include <set>
#include <sstream>

#include "Graph.hpp"

namespace cvt {
    
    template <typename Vertex> std::vector<Vertex> reconstruct_path(Vertex start, Vertex goal, std::map<Vertex, Vertex> &came_from) {
        Vertex current = goal;
        std::vector<Vertex> path({current});
        
        while (current != start) {
            current = came_from[current]; 
            path.push_back(current);
        }
        
        path.push_back(start);
        
        std::reverse(path.begin(), path.end());
        
        return path;
    }
    
    template <typename Graph> std::vector<typename Graph::Vertex> breadth_first_search(Graph graph, typename Graph::Vertex start, typename Graph::Vertex goal) {
    
        using Vertex = typename Graph::Vertex;
        using Edge = typename Graph::Edge;
        
        std::queue<Vertex> frontier;
        frontier.push(start);
        
        //std::set<Vertex> visited;
        //visited.insert(start);
        
        std::map<Vertex, Vertex> came_from;
        came_from[start] = start;
        
        Vertex current = start;
        
        while(!frontier.empty()) {
            current = frontier.front();
            frontier.pop();
            
            //std::cout << "Visiting " << ss.str() << std::endl;
            
            if (current == goal) {
                break;
            }
            
            for (auto next_edge : graph.neighbors(current)) {
                
                Vertex next = next_edge.second;
                
                if (!came_from.count(next)) {
                    frontier.push(next);
                    came_from[next] = current;
                }
            }
        }
        
        return reconstruct_path(start, current, came_from);
        
    }
    
}


#endif // SEARCH_HPP