#ifndef CLAIRVOYANT_HPP
#define CLAIRVOYANT_HPP

#include "graph.hpp"
#include "neural.hpp"

namespace cvt {

    template<typename Graph, typename C> struct Clairvoyant { 
        
        using State = typename Graph::Vertex;
        using Action = typename Graph::Edge;
        
        Graph graph;
        
        template<typename Completed, typename CostFunction, typename CostHeuristic>
            inline const Action best(const State &search_from, 
                                     Completed completed = [](typename Graph::Vertex v) { return false; },
                                     CostFunction cost_function = [](typename Graph::Vertex v, typename Graph::Type t) { return 1; },
                                     CostHeuristic cost_heuristic = [](typename Graph::Vertex v) { return 0; })) {
            
            std::vector< Type > path = search(graph, search_from, completed, cost_function, cost_heuristic);
            return Graph::edge(path.front());
        }
        
    };
}


#endif // CLAIRVOYANT_H