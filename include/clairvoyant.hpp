#ifndef CLAIRVOYANT_HPP
#define CLAIRVOYANT_HPP

#include "graph.hpp"
#include "neural.hpp"

namespace cvt {

    template<typename G, typename C> struct clairvoyant { 
        
        using Graph = G;
        using Cost = C;
        
        using State = typename Graph::Vertex;
        using Action = typename Graph::Edge;
        
        Graph graph;
        
        template inline Action best(const State &search_from, 
                                          const graph_search<State, Action, Cost>  &search = graph_search<State, Action, Cost>()) {
            return search.min_cost_path(graph, search_from).front().first;
        }
        
    };
}


#endif // CLAIRVOYANT_H