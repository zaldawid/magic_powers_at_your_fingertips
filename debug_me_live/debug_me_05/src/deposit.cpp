#include "deposit.h"

namespace pot {
    Deposit::Deposit(std::string_view name, double amount)
        : name_{name}, amount_{amount}
    {}

    std::string_view Deposit::name() const
    {
        return name_;
    }

    double Deposit::amount() const
    {
        return amount_;
    }
}