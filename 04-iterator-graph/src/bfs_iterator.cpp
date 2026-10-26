#include "graph/bfs_iterator.hpp"

#include <stdexcept>

BFSIterator::BFSIterator(const Graph& graph, int start) : graph_(graph) {
    if (!graph_.contains(start)) {
        throw std::invalid_argument("nodo inicial inexistente");
    }
    queue_.push(start);
    visited_.insert(start);
}

bool BFSIterator::hasNext() const {
    return !queue_.empty();
}

int BFSIterator::next() {
    if (queue_.empty()) {
        throw std::out_of_range("No hay más elementos en el iterador");
    }
    const int current = queue_.front();
    queue_.pop();
    for (const int n : graph_.neighbors(current)) {
        if (visited_.insert(n).second) {
            queue_.push(n);
        }
    }
    return current;
}
