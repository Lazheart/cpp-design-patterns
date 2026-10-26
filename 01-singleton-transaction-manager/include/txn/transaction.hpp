#pragma once
#include <string>

struct Transaction {
    enum class Type {
        Deposit,
        Withdraw
    };

    Type type;
    double amount;
    std::string accountId;
};
