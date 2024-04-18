#include "pot.h"

#include <iostream>
#include <string>
#include <string_view>
#include <set>
#include <vector>
#include <functional>


namespace pot
{

    /**
     * @brief Converts a string to lowercase.
     * @param str The string to convert
     * @return The lowercase version of the input string
     * 
     */
    std::string to_lower(std::string_view str)
    {
        std::string result{str};
        for (char& c : result)
        {
            c = std::tolower(c);
        }
        return result;
    }

    /// @brief  The default capacity of the deposits array.
    constexpr static auto DEFAULT_CAPACITY = 16;

    /**
     * @brief Construct a new Pot:: Pot object
     * 
     * @param goal The goal of the pot.
     * @param target The target amount of money to save.
     */
    Pot::Pot(std::string const& goal, double target) :
        goal_{goal}, 
        deposits_target_{target}, 
        deposits_{new Deposit[DEFAULT_CAPACITY]},
        deposits_size_{0},
        deposits_capacity_{DEFAULT_CAPACITY}
    {}

    /**
     * @brief Destroy the Pot:: Pot object
     */
    Pot::~Pot() noexcept
    {
        delete[] deposits_;
    }

    /**
     * @brief Returns the goal of the pot.
     * 
     * @return std::string_view the goal of the pot.
     * @note If the goal is an empty string, "No goal" is returned.
     */
    std::string_view Pot::goal() const
    {
        using namespace std::literals::string_view_literals;
        return goal_.empty() ? "No goal"sv : goal_;
    }

    /**
     * @brief Adds a new deposit to the pot.
     * 
     * @param name The name of the contributor.
     * @param amount The amount contributed.
     */
    void Pot::add_deposit(std::string_view name, double amount)
    {
        if (deposits_size_ == deposits_capacity_)
        {
            deposits_capacity_ = deposits_capacity_ == 0 ? 2 : deposits_capacity_ * 2;
            Deposit * new_deposits = new Deposit[deposits_capacity_]{};
            for (int i = 0; i < deposits_capacity_; ++i)
            {  
                new_deposits[i] = deposits_[i];
            }
            delete[] deposits_;
            deposits_ = new_deposits;
        }

        deposits_[deposits_size_++] = Deposit{name, amount};
    }

    /**
     * @brief The total amount contributed by a contributor.
     * 
     * @param name The name of the contributor.
     * @return double The amount contributed by the contributor with the given name so far.
     */
    double Pot::total_for(std::string_view name) const
    {
        double total{};
        for (int i = 0; i < deposits_size_; ++i)
        {
            if (to_lower(deposits_[i].name()) == to_lower(name))
            {
                total += deposits_[i].amount();
            }
        }
        return total;
    }

    /**
     * @brief The target amount of money to save.
     * 
     * @return double The target amount of money to save.
     */
    double Pot::target() const
    {
        return deposits_target_;
    }

    /**
     * @brief The total amount contributed to the pot.
     * 
     * @return double The total amount contributed to the pot.
     */
    double Pot::total() const
    {
        double total{};
        for (auto i{0}; i < deposits_size_; ++i)
        {
            total += deposits_[i].amount();
        }
        return total;
    }

    /**
     * @brief The amount remaining that needs to be saved to reach the target.
     * 
     * @return double The remaining amount.
     */
    double Pot::remaining() const
    {
        return deposits_target_ - total();
    }

    /**
     * @brief Check is a person is a contributor.
     * 
     * @param name The name of the person to check.
     * @return true If the person is a contributor.
     * @return false Otherwise.
     */
    bool Pot::is_contributor(std::string_view name) const
    {
        Deposit * deposit = find_deposit(name, 0);
        if (deposit == nullptr)
        {
            return false;
        }
        return to_lower(name) == to_lower(deposit->name());
    }

    /**
     * @brief Finds the first deposit of a contributor with the given name.
     * 
     * @param name The name of the contributor
     * @param start The index to start searching from.
     * @return Deposit* The pointer to the deposit of this contributor.
     */
    Deposit * Pot::find_deposit(std::string_view name, int start) const
    {
        for (int i = start; i < deposits_size_; ++i)
        {
            if (to_lower(deposits_[i].name()) == to_lower(name))
            {
                return &deposits_[i];
            }
        }
        return nullptr;
    }

    Deposit const * Pot::begin() const
    {
        return deposits_;
    }

    Deposit const * Pot::end() const
    {
        return deposits_ + deposits_size_;
    }

    Deposit * Pot::begin()
    {
        return deposits_;
    }

    Deposit * Pot::end()
    {
        return deposits_ + deposits_size_;
    }

    std::size_t Pot::size() const
    {
        return deposits_size_;
    }

    void Pot::trim_to(Iterator new_end)
    {
        deposits_size_ = std::distance(begin(), new_end);
    }

    std::ostream& operator<<(std::ostream& os, Pot const& pot)
    {
        os << "Pot: " << pot.goal() << "\n";
        os << "Target: " << pot.target() << "\n";
        os << "Total: " << pot.total() << "\n";
        os << "Remaining: " << pot.remaining() << "\n";
        os << "Deposits:\n";
        for (auto deposit : pot)
        {
            os << "  * " << deposit.name() << ": " << deposit.amount() << "\n";
        }

        return os;
    }

}