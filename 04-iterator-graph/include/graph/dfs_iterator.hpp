#pragma once
#include "graph/graph.hpp"
#include "graph/graph_iterator.hpp"

#include <stack>
#include <unordered_set>

class DFSIterator final : public GraphIterator {
public:
    DFSIterator(const Graph& graph, int start);

    [[nodiscard]] bool hasNext() const override;
    int next() override;

private:
    void advance() const;

    const Graph& graph_;
    mutable std::stack<int> stack_;
    mutable std::unordered_set<int> visited_;
};
