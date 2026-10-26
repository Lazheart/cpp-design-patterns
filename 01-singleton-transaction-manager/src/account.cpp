#include "txn/account.hpp"

#include <utility>

Account::Account(std::string id, double initialBalance)
    : id_(std::move(id)), balance_(initialBalance) {}

const std::string& Account::id() const noexcept {
    return id_;
}

double Account::getBalance() const noexcept {
    return balance_.load(std::memory_order_relaxed);
}

void Account::applyDelta(double delta) noexcept {
    // In C++20, std::atomic<double> has fetch_add
    balance_.fetch_add(delta, std::memory_order_relaxed);
}
