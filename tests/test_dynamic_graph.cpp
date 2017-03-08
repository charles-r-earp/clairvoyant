#include <clairvoyant.hpp>

template <typename T> std::vector< std::vector<T> > permutations(std::vector<T> options, int n, int N) { // n starts at 1
    std::vector< std::vector<T> > p;
    
    if (n <= N) {
        
        for (auto item : options) {
            std::vector<T> v = {item};
            std::vector<T> u = permutations(options, n+1, N);
            
            
            v.insert(u.begin(), u.end());
            p.push_back(v);
        }
    }
    return p;
}

template <typename T> T magnitude(std::vector<T> v) {
    
    T sum;
    for (auto item : v) {
        
        sum += item*item;
    }
    return sum;
}

template <typename T> std::vector<T> add(std::vector<T> &u, std::vector<T> &v) {
    
    std::vector<T> w;
    
    for (int i = 0; i < u.size(); ++i) {
        
        w.push_back(u[i] + v[i]);
    }
    
    return w;
}

template<typename T> class Grid {
    
    //using Graph = typename cvt::DynamicGraph<std::vector<T>, T>;
    
    //using Vertex = typename Graph::Vertex;
    //using Cost = typename Graph::Cost;
    //using Edge = typename Graph::Edge;
    
    public: using Vertex = std::vector<T>;
    public: using Edge = std::pair<T, Vertex >;
    
    std::vector<Edge> moves;
    
    public: Grid(std::vector<T> spacing) {
        
        for (int i = 0; i < spacing.size(); ++i) {
            std::vector<T> v(spacing.size());
            
            // just 'faces' not edges of hypercube
            v[i] = spacing[i];
            
            T cost = magnitude(v);
            
            this->moves.push_back({cost, v});
        }
    }
    
    
    public: std::vector<Edge> neighbors(Vertex v) {
        std::vector<Edge> edges;
        
        for (auto edge : moves) {
            edge.second = add( edge.second, v);
            edges.push_back(edge);
        }
        
        return edges;
    }
    
};

#define PI 3.14159

int main() {
    std::vector<float> v = {10, 10, PI/5};
    Grid<float> grid(v);
    
    cvt::DynamicGraph<std::vector<float>, float> graph;
    
    graph.edges_cb = [&grid](Grid<float>::Vertex v) { return grid.neighbors(v); };
    
    std::vector<float> start = {0,0,0}, end = {400, 100, PI};
    
    std::vector<std::vector<float> > path = cvt::breadth_first_search(graph, start, end);
    
    for (auto v : path) {
        std::cout << "->";
        std::copy(v.begin(), v.end(), std::ostream_iterator<float>(std::cout,","));
    }
    
    std::cout << std::endl;
    
}