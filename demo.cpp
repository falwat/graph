#include <any>
#include <iostream>
#include <variant>
#include "graph.h"

int main(int, char**) {
    Graph g;
    g.add_node(0, {{"x", 100}, {"y", 200}});
    g.add_node(1);
    g.add_node(2);
    g.add_edge(0, 1, 0.5);
    g.add_edge(1, 2, 1.0);
    g.add_edge(0, 2, 2);
    g.add_edge(0, 3, 0.3);
    g.add_edge(1, 3, 0.3);
    std::cout << std::boolalpha;
    std::cout << "Has edge(0, 1): " << g.has_edge(0, 1) << std::endl;
    auto neighbors = g.get_neighbors(0);
    std::cout << "The neighbors of node 0: ";
    for (auto &&n : neighbors)
    {
        std::cout << " " << n->get_id();
    }
    std::cout << std::endl;
    
    auto [dist, path] = g.shortest_simple_paths(0, 2);
    std::cout << "The shortest distance from node 0 to node 2: " << dist;
    std::cout << "\nThe shortest path from node 0 to node 2: ";
    for (auto &&i : path)
    {
        std::cout << " " << i;
    }
    std::cout << std::endl;
    return 0;
}
