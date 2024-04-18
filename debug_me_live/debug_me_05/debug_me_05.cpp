#include <iostream>
#include <filesystem>
#include "pot.h"
#include "pot_manager.h"

void add_some(pot::Pot& pot, int repeat);

int main(int, char * argv[])
{
    auto& pm = pot::PotManager::from_file(argv[1]);
    
    auto& pot = pm.pot();

    std::cout << "Goal: " << pot.goal() << '\n';
    std::cout << "Total: " << pot.total() << '\n';
    std::cout << "Remaining: " << pot.remaining() << '\n';
    std::cout << "Deposits:\n";

    std::cout << "Is Benna a contributor? " << std::boolalpha << pot.is_contributor("Benna") << '\n';
    std::cout << "Is Zack a contributor? " << std::boolalpha << pot.is_contributor("Zack") << '\n';

    std::cout << "Total for Benna: " << pot.total_for("benna") << '\n';
    std::cout << "Total for Rene: " << pot.total_for("Rene") << '\n';
    std::cout << "Total for Fely: " << pot.total_for("fely") << '\n';
    std::cout << "Total for Zack: " << pot.total_for("Zack") << '\n';

    std::cout << "Size: " << pot.size() << '\n';

    std::cout << "Press Enter to exit...";
    std::cin.get();
}


void add_some(pot::Pot& pot, int repeat)
{
    for (int i = 0; i < repeat; ++i) {
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
