#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <iostream>
#include <queue>
#include <set>
<<<<<<< HEAD
#include <functional>
=======
#include <sstream>
>>>>>>> cbfb70bb3d4401b8cede278f40feeea1c4c96db6

#include "Graph.hpp"

namespace cvt {
    
<<<<<<< HEAD
    
    template <typename Graph, typename Cost = int> class Search {
        
        public: using Vertex = typename Graph::Vertex;
        public: using Edge = typename Graph::Edge;
        public: using CostedEdge = std::pair<Cost, Edge>;
        public: using Path = std::vector<CostedEdge>; 
        public: using CostFunction = std::function<Cost(Path)>;
        
        public: Graph graph;
        public: CostFunction cost;
        public: Vertex start;
        
        private: std::priority_queue<CostedEdge, std::vector<CostedEdge>, std::greater<CostedEdge>> frontier;
        private: std::map<Vertex, std::pair<Vertex, CostedEdge> > visited;
        private: Vertex current;
        
        public: Search(Graph graph, Vertex start, CostFunction cost) {
            this->graph = graph;
            this->start = start;
            this->cost = cost;
            
            this->initialize();
        }
        
        public: Search(Graph &graph, Vertex start) {
            this->graph = graph;
            this->start = start;
            this->cost = [](Path p){ return Cost(); };
            
            this->initialize();
        }
        
        public: Vertex step_forward() {
            
            this->visit(this->current);
            
            if (!this->frontier.empty()) {
                CostedEdge current_costed_edge = this->frontier.top();
                Edge current_edge = current_costed_edge.second;
                Vertex current = graph.extract(current_edge);
                
                this->frontier.pop();
                
                //this->visit(current);
                
                this->current = current;
            }
            
            return this->current;
        }
        
        public: const Path reconstruct_path(Vertex v) {
            
            Path path;
            
            if (this->visited.count(v)) {
                while(v != this->start) {
                
                    Vertex last; 
                    CostedEdge costed_edge;
                    std::tie(last, costed_edge) = this->visited[v];
                    path.push_back(costed_edge);
                    v = last;
                }
                
                std::reverse(path.begin(), path.end());
            }
            
            return path;
        }
        
        public: Path search(Vertex goal) {
            while (this->current != goal) {
                this->step_forward();
            }
            return this->reconstruct_path(this->current);
        }
        
        
        private: inline void initialize() {
            //this->visit(this->start);
            
            this->current = this->start;
        }
        
        private: void visit(Vertex current) { 
            
            std::cout << "Visiting: " << current << std::endl;
        
            Path path = this->reconstruct_path(current);
            Cost cost = this->cost(path);
            
            for (Edge next_edge : graph[current]) {
                    
                Vertex next = graph.extract(next_edge);
                
                std::cout << "\tAdding: " << next << std::endl;
                
                if (!visited.count(next)) {
                        
                    CostedEdge next_costed_edge = std::make_pair/*<Cost, Edge>*/(cost, next_edge);
                    
                    this->frontier.push(next_costed_edge);
                    this->visited[next] = std::make_pair/*<Vertex, Edge>*/(current, next_costed_edge);
                }
            }
            
            std::cout << "End" << std::endl;
        }
        
        
    };
    
    /*template <typename Graph> void breadth_first_search(Graph graph, typename Graph::Vertex start, typename Graph::Vertex goal) {
=======
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
>>>>>>> cbfb70bb3d4401b8cede278f40feeea1c4c96db6
    
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
    }*/
    
}


#endif // SEARCH_HPP
