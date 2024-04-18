#include "compactor.h"
#include "pot_manager.h"

#define COMPACTOR_ENABLED (1)

namespace pot::exp
{
#if defined(COMPACTOR_ENABLED) && COMPACTOR_ENABLED
    constexpr static auto DEFAULT_COMPACT_LIMIT = 32;
    
    auto compactor =[](){ std::thread( []() {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            
            if (auto& pm = pot::PotManager::get(); pm)
            {
                auto& pot = pot::PotManager::get().pot();

                if (pot.size() > DEFAULT_COMPACT_LIMIT)
                {
        
                    pot.trim_to(compact(par, pot.begin(), pot.end()));
                }
            }
        }
        }).detach();

        return 0;
    }();

#endif


} // namespace pot::exp

