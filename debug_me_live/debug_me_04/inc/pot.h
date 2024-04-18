#ifndef INCLUDED_POT_H
#define INCLUDED_POT_H

#include <iostream>
#include <string>
#include <string_view>
#include "deposit.h"


namespace pot{
    /**
     * @brief A pot is a collection of deposits that are used to save money for a goal.
     * 
     */
    class Pot {

        /// @brief The goal of the pot.
        std::string goal_;

        /// @brief The target amount of money to save.
        double deposits_target_;

        /// @brief An array of deposits.
        Deposit * deposits_;

        /// @brief  The number of deposits in the array.
        int deposits_size_;

        /// @brief The capacity of the array.
        int deposits_capacity_;


        Deposit * find_deposit(std::string_view name) const;

    public:
        using Iterator = Deposit *;
        using ConstIterator = Deposit const *;

        Pot(std::string const& goal, double target);
        ~Pot() noexcept;

        std::string_view goal() const;   // BUG should return std::string instead of std::string_view
        void add_deposit(std::string_view name, double amount);
        double total_for(std::string_view name) const;
        bool is_contributor(std::string_view name) const;

        double target() const;
        double total() const;
        double remaining() const;

        ConstIterator begin() const;
        ConstIterator end() const;

        Iterator begin();
        Iterator end();

        void trim_to(Iterator new_end);
        
        std::size_t size() const;

        friend std::ostream& operator<<(std::ostream& os, Pot const& pot);

    };

    std::ostream& operator<<(std::ostream& os, Pot const& pot);
}

#endif