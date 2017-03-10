#ifndef CLAIRVOYANT_HPP
#define CLAIRVOYANT_HPP

#include "graph.hpp"
#include "model.hpp"
//#include "neural.hpp"

namespace cvt {
/*
    template<typename G, typename C> struct Clairvoyant { 
        
        using Graph = G;
        
        using State = typename Graph::Vertex;
        using Type = typename Graph::Type;
        using Cost = C;
        
        Graph graph;
        std::function<bool(State)> completed;
        std::function<Cost(State, Type)> cost_function;
        std::function<Cost(State)> cost_heuristic;
        
        inline const Action best(const State &search_from) {
            std::vector< Type > path = search(graph, search_from, completed, cost_function, cost_heuristic);
            
            return path.front().first;
        }
        
        inline void update(const State &new_state) {
            // trim graph
            graph::rebase(this->graph, new_state);
        }
        
    };*/
}


#endif // CLAIRVOYANT_H