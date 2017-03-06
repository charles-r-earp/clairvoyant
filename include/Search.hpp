#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <functional>

// A* Search of Graph

namespace cvt {

    using EdgesForNodeCB = std::function<std::vector<&Edge>(&Node));
    
    &Path search(Graph &graph, Node &start, Node &end, EdgesForNodeCB &nextEdges); // empty path on failure
}


endif // SEARCH_HPP