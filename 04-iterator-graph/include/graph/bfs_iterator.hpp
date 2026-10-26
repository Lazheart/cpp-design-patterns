#pragma once
#include "graph/graph.hpp"
#include "graph/graph_iterator.hpp"

#include <queue>
#include <unordered_set>

class BFSIterator final : public GraphIterator {
public:
    BFSIterator(const Graph& graph, int start);

    [[nodiscard]] bool hasNext() const override;
    int next() override;

private:
    const Graph& graph_;
    std::queue<int> queue_;
    std::unordered_set<int> visited_;
};
