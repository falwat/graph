# graph

Graph implementation with c++

## How to use

- Include header.

```cpp
#include "graph.h"
```

- Create a Graph object.

```cpp
Graph g;
```

- Add node(also known as `vertex`) to this graph.

```cpp
// Add node 0
g.add_node(0);
// Add node 1 with custom attributs
g.add_node(1, {{"x", 100}, {"y", 200}});
```

- Add edge to this graph.

```cpp
g.add_edge(0, 1, 0.5);
g.add_edge(1, 2, 1.0);
g.add_edge(0, 2, 2);
// node 3 will be automatically added to the graph
g.add_edge(0, 3, 0.3);
g.add_edge(1, 3, 0.3);
```

- Use `Graph::has_edge()` to check if the edge(0, 1) is in this graph.

```
std::cout << std::boolalpha;
std::cout << g.has_edge(0, 1) << std::endl;
```

- Get the neighbors of node 0 in this graph

```cpp
auto neighbors = g.get_neighbors(0);
std::cout << "The neighbors of node 0: ";
for (auto &&n : neighbors)
{
    std::cout << " " << n->get_id();
}
std::cout << std::endl;
```

- Get the shortest simple path from node 0 to node 2.
```cpp
auto [dist, path] = g.shortest_simple_paths(0, 2);
std::cout << "The shortest distance from node 0 to node 2: " << dist;
std::cout << "\nThe shortest path from node 0 to node 2: ";
for (auto &&i : path)
{
    std::cout << " " << i;
}
std::cout << std::endl;
```

See [demo.cpp](./demo.cpp) to get it all.
