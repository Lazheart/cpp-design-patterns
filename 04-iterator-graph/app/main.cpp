#include "graph/bfs_iterator.hpp"
#include "graph/dfs_iterator.hpp"
#include "graph/graph.hpp"

#include <iostream>
#include <memory>

int main() {
    Graph g;
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);

    std::unique_ptr<GraphIterator> it = std::make_unique<BFSIterator>(g, 1);
    std::cout << "BFS: ";
    while (it->hasNext()) {
        std::cout << it->next() << ' ';
    }
    std::cout << '\n';

    it = std::make_unique<DFSIterator>(g, 1);
    std::cout << "DFS: ";
    while (it->hasNext()) {
        std::cout << it->next() << ' ';
    }
    std::cout << '\n';

    return 0;
}
