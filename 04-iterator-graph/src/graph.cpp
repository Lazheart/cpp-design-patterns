#include "graph/graph.hpp"

void Graph::addEdge(int from, int to) {
    if (!nodes_.contains(from)) {
        nodes_.emplace(from, Node(from));
    }
    if (!nodes_.contains(to)) {
        nodes_.emplace(to, Node(to));
    }
    nodes_[from].addNeighbor(to);
}

std::span<const int> Graph::neighbors(int id) const {
    const auto it = nodes_.find(id);
    if (it == nodes_.end()) {
        return {};
    }
    return it->second.out();
}

bool Graph::contains(int id) const {
    return nodes_.contains(id);
}
