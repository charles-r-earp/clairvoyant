#ifndef CLAIRVOYANT_HPP
#define CLAIRVOYANT_HPP

#include "graph.hpp"
#include "model.hpp"
//#include "neural.hpp"

namespace cvt {

    template<typename G> struct Clairvoyant { 
        
        using Graph = G;
        
        using State = typename Graph::Vertex;
        using Action = typename Graph::Edge;
        using Type = typename Graph::Type;
        
        Graph graph;
        
        template<typename Completed, typename CostFunction, typename CostHeuristic>
            inline const Action best(const State &search_from, 
                                     Completed completed = [](typename Graph::Vertex v) { return false; },
                                     CostFunction cost_function = [](typename Graph::Vertex v, typename Graph::Type t) { return 1; },
                                     CostHeuristic cost_heuristic = [](typename Graph::Vertex v) { return 0; })) {
            std::cout << "2.1";
            std::vector< Type > path = search(graph, search_from, completed, cost_function, cost_heuristic);
            std::cout << "2.2";
            return Graph::edge(path.front());
        }
        
        inline void update(const State &new_state) {
            // trim graph
            graph::rebase(this->graph, new_state);
        }
        
    };
}


#endif // CLAIRVOYANT_H