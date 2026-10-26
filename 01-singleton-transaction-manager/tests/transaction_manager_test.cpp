#include "txn/transaction_manager.hpp"

#include <gtest/gtest.h>

#include <thread>
#include <vector>

TEST(SingletonTest, SameInstanceAcrossThreads) {
    std::vector<TransactionManager*> addresses(10, nullptr);
    std::vector<std::thread> threads;
    threads.reserve(10);

    for (size_t i = 0; i < 10; ++i) {
        threads.emplace_back([&addresses, i] {
            addresses[i] = &TransactionManager::getInstance();
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    TransactionManager* const expected = &TransactionManager::getInstance();
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(addresses[i], expected);
    }
}

TEST(TransactionManagerTest, ConcurrentDepositAndWithdraw) {
    auto& manager = TransactionManager::getInstance();
    Account account("ACC-CONCURRENT", 1000.0);

    constexpr int threadCount = 10;
    std::vector<std::thread> threads;
    threads.reserve(threadCount);

    for (int i = 0; i < threadCount; ++i) {
        threads.emplace_back([&manager, &account] {
            manager.deposit(&account, 100.0);
            manager.withdraw(&account, 50.0);
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    // 1000 + (10 * 100) - (10 * 50) = 1500
    EXPECT_DOUBLE_EQ(account.getBalance(), 1500.0);
}

TEST(TransactionManagerTest, InsufficientFundsThrowsException) {
    auto& manager = TransactionManager::getInstance();
    Account account("ACC-POOR", 50.0);

    EXPECT_THROW(manager.withdraw(&account, 100.0), InsufficientFundsException);
    EXPECT_DOUBLE_EQ(account.getBalance(), 50.0);
}

TEST(TransactionManagerTest, HistoryRecording) {
    auto& manager = TransactionManager::getInstance();
    Account account("ACC-HISTORY", 200.0);

    const size_t initialHistoryCount = manager.history().size();

    manager.deposit(&account, 50.0);
    manager.withdraw(&account, 30.0);

    const auto history = manager.history();
    EXPECT_EQ(history.size(), initialHistoryCount + 2);

    const auto& lastOp = history.back();
    EXPECT_EQ(lastOp.type, Transaction::Type::Withdraw);
    EXPECT_DOUBLE_EQ(lastOp.amount, 30.0);
    EXPECT_EQ(lastOp.accountId, "ACC-HISTORY");
}
