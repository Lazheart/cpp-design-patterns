#include "txn/transaction_manager.hpp"

#include <mutex>

TransactionManager& TransactionManager::getInstance() {
    static TransactionManager instance;
    return instance;
}

void TransactionManager::deposit(Account* account, double amount) {
    if (!account || amount <= 0.0) {
        return;
    }
    std::lock_guard<std::mutex> lock(mtx_);
    account->applyDelta(amount);
    history_.push_back({Transaction::Type::Deposit, amount, account->id()});
}

void TransactionManager::withdraw(Account* account, double amount) {
    if (!account || amount <= 0.0) {
        return;
    }
    std::lock_guard<std::mutex> lock(mtx_);
    if (account->getBalance() < amount) {
        throw InsufficientFundsException("Fondos insuficientes en la cuenta: " + account->id());
    }
    account->applyDelta(-amount);
    history_.push_back({Transaction::Type::Withdraw, amount, account->id()});
}

std::vector<Transaction> TransactionManager::history() const {
    std::lock_guard<std::mutex> lock(mtx_);
    return history_;
}
