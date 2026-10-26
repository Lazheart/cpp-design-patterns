#pragma once
#include <atomic>
#include <string>

class TransactionManager;

class Account {
public:
    Account(std::string id, double initialBalance = 0.0);

    [[nodiscard]] const std::string& id() const noexcept;
    [[nodiscard]] double getBalance() const noexcept;

private:
    void applyDelta(double delta) noexcept;
    friend class TransactionManager;

    std::string id_;
    std::atomic<double> balance_;
};
