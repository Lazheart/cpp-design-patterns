#pragma once
#include "graph/node.hpp"

#include <span>
#include <unordered_map>

class Graph {
public:
    void addEdge(int from, int to);
    [[nodiscard]] std::span<const int> neighbors(int id) const;
    [[nodiscard]] bool contains(int id) const;

private:
    std::unordered_map<int, Node> nodes_;
};
