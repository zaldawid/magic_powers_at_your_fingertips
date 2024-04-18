#include <iostream>
#include <limits>
#include "pot.h"
#include "pot_manager.h"

void add_some(pot::Pot& pot, int reapeat=1);

int main()
{
    auto& pm = pot::PotManager::with_goal("Trip to the Moon", 1500.0);
    
    auto& pot = pm.pot();

    std::cout << "How many times to add deposits? ";
    int repeat{};
    std::cin >> repeat;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();

    add_some(pot, repeat);

    std::cout << "Goal: " << pot.goal() << '\n';
    std::cout << "Total: " << pot.total() << '\n';
    std::cout << "Remaining: " << pot.remaining() << '\n';
    std::cout << "Deposits:\n";
    
    std::cout << "Is Alice a contributor? " << std::boolalpha << pot.is_contributor("Alice") << '\n';
    std::cout << "Is Derek a contributor? " << std::boolalpha << pot.is_contributor("Derek") << '\n';

    std::cout << "Total for Alice: " << pot.total_for("alice") << '\n';
    std::cout << "Total for Bob: " << pot.total_for("Bob") << '\n';
    std::cout << "Total for Cindy: " << pot.total_for("cindy") << '\n';
    std::cout << "Total for Eve: " << pot.total_for("eve") << '\n';

    std::cout << "Size: " << pot.size() << '\n';

    std::cout << "Press Enter to exit...";
    std::cin.get();

    std::cout << pot;
}

void add_some(pot::Pot& pot, int reapeat)
{
    for (int i = 0; i < reapeat; ++i) {
        pot.add_deposit("Alice", 10.0);
        pot.add_deposit("Bob", 5.0);
        pot.add_deposit("alice", 5.0);
        pot.add_deposit("Eve", 5.0);
        pot.add_deposit("bob", 5.0);
        pot.add_deposit("Alice", 5.0);
        pot.add_deposit("Cindy", 15.0);
        pot.add_deposit("eve", 25.0);
        pot.add_deposit("Bob", 5.0);
        pot.add_deposit("cindy", 15.0);
        pot.add_deposit("Bob", 5.0);
        pot.add_deposit("eve", 5.0);
    }
}