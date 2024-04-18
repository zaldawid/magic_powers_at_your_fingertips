#include "pot_manager.h"
#include <algorithm>
#include <cctype>
#include <fstream>

namespace pot
{

    PotManager& PotManager::get()
    {
        static PotManager instance{};
        return instance;
    }

    PotManager& PotManager::from_file(std::string const& file_name)
    {
        auto& instance = get();
        instance.reset(file_name);
        return instance;
    }

    PotManager& PotManager::with_goal(std::string const& goal, double target)
    {
        auto& instance = get();
        instance.reset(goal, target);
        return instance;
    }

    PotManager::~PotManager() noexcept
    {
        clear();
    }

    void PotManager::clear()
    {
        if (pot_)
        {
            save(file_name_);
            delete pot_;
            pot_ = nullptr;
            file_name_ = "";
        }
    }

    void PotManager::reset(std::string const& goal, double target)
    {
        if (pot_) 
        {
            throw std::runtime_error{ "PotManager::reset: Pot already exists. Call `clear` first." };
        }
        pot_ = new Pot{ goal, target };
        file_name_ = make_filename(goal);
    }

    void PotManager::reset(std::string const& file_name)
    {
        if (pot_) 
        {
            throw std::runtime_error{ "PotManager::reset: Pot already exists. Call `clear` first." };
        }
        load(file_name);
    }

    Pot& PotManager::pot()
    {
        return *pot_;
    }

    Pot const& PotManager::pot() const
    {
        return *pot_;
    }


    bool PotManager::load(std::string const &file_name)
    {
        if (std::ifstream in{file_name})
        {
            std::string goal{};
            double target{};

            if (std::getline(in, goal, ',') && in >> target >> std::ws)
            {
                reset(goal, target);
                file_name_ = file_name;

                std::string name{};
                double amount{};
                while (std::getline(in, name, ',') && in >> amount && (in.eof() || in >> std::ws))
                {
                    pot_->add_deposit(name, amount);
                }
                return true;
            }
        }
        return false;
    }

    bool PotManager::save(std::string const &file_name) const 
    {
        if (std::ofstream out{file_name})
        {
            out << pot_->goal() << ", " << pot_->target() << '\n';
            for (auto const& deposit : *pot_)
            {
                out << deposit.name() << ", " << deposit.amount() << '\n';
            }
            return true;
        }
        return false;

    }

    std::string PotManager::make_filename(std::string str) const
    {
        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::tolower(c); });
        std::replace_if(str.begin(), str.end(), [](unsigned char c){return std::isspace(c); }, '_');
        return str;
    }



} // namespace pot
