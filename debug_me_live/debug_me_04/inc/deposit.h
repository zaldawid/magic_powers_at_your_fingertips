#ifndef INCLUDED_DEPOSIT_H
#define INCLUDED_DEPOSIT_H

#include <string_view>
#include <string>

namespace pot {
    /**
     * @brief A deposit is a contribution to a pot.
     * @note This is simple data class. It is bug-free. Seriously.
     */
    class Deposit {
        std::string name_;
        double amount_;
    public:
        Deposit() = default;
        Deposit(std::string_view name, double amount);
        std::string_view name() const;
        double amount() const;
    };
}

#endif