#include "txn/transaction_manager.hpp"

#include <iostream>
#include <thread>
#include <vector>

int main() {
    auto& manager = TransactionManager::getInstance();
    Account account("A1", 1000.0);

    std::vector<std::thread> threads;
    threads.reserve(10);
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([&] {
            manager.deposit(&account, 100.0);
            manager.withdraw(&account, 50.0);
        });
    }
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Balance final: " << account.getBalance() << '\n';
    std::cout << "Direccion manager: " << static_cast<const void*>(&TransactionManager::getInstance())
              << '\n';
    return 0;
}
