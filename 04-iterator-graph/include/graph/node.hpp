#pragma once
#include <vector>

class Node {
public:
    explicit Node(int id = 0) : id_(id) {}

    [[nodiscard]] int id() const noexcept {
        return id_;
    }

    [[nodiscard]] const std::vector<int>& out() const noexcept {
        return out_;
    }

    void addNeighbor(int neighborId) {
        out_.push_back(neighborId);
    }

private:
    int id_;
    std::vector<int> out_;
};
