#include "graph/dfs_iterator.hpp"

#include <stdexcept>

DFSIterator::DFSIterator(const Graph& graph, int start) : graph_(graph) {
    if (!graph_.contains(start)) {
        throw std::invalid_argument("nodo inicial inexistente");
    }
    stack_.push(start);
}

void DFSIterator::advance() const {
    while (!stack_.empty() && visited_.contains(stack_.top())) {
        stack_.pop();
    }
}

bool DFSIterator::hasNext() const {
    advance();
    return !stack_.empty();
}

int DFSIterator::next() {
    advance();
    if (stack_.empty()) {
        throw std::out_of_range("No hay más elementos en el iterador");
    }
    const int current = stack_.top();
    stack_.pop();
    visited_.insert(current);

    const auto nbrs = graph_.neighbors(current);
    for (auto it = nbrs.rbegin(); it != nbrs.rend(); ++it) {
        if (!visited_.contains(*it)) {
            stack_.push(*it);
        }
    }
    advance();
    return current;
}
