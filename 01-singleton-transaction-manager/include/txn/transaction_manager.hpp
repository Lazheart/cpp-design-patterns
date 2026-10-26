#pragma once
#include "txn/account.hpp"
#include "txn/insufficient_funds_exception.hpp"
#include "txn/transaction.hpp"
#include <mutex>
#include <vector>

class TransactionManager {
public:
    static TransactionManager& getInstance();

    TransactionManager(const TransactionManager&) = delete;
    TransactionManager& operator=(const TransactionManager&) = delete;
    TransactionManager(TransactionManager&&) = delete;
    TransactionManager& operator=(TransactionManager&&) = delete;

    void deposit(Account* account, double amount);
    void withdraw(Account* account, double amount);
    [[nodiscard]] std::vector<Transaction> history() const;

private:
    TransactionManager() = default;
    mutable std::mutex mtx_;
    std::vector<Transaction> history_;
};
