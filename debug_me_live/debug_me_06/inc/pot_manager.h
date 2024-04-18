#ifndef INCLUDED_POT_LOADER_H
#define INCLUDED_POT_LOADER_H

#include <string>

#include "pot.h"

namespace pot
{
    class PotManager
    {
    public:
        static PotManager& get();
        static PotManager& from_file(std::string const& file_name);
        static PotManager& with_goal(std::string const& goal, double target);

        PotManager(PotManager const&) = delete;
        PotManager& operator=(PotManager const&) = delete;
                
        ~PotManager() noexcept;

        void clear();

        void reset(std::string const& goal, double target);
        void reset(std::string const& file_name);

        Pot& pot();
        Pot const& pot() const;

        operator bool() const;
        bool operator!() const;
    private:
        PotManager() = default;
        static PotManager& instance();
        bool load(std::string const& file_name);
        bool save(std::string const& file_name) const;

        std::string make_filename(std::string str) const;
        
        Pot * pot_;
        std::string file_name_;
    };
} // namespace pot

#endif // INCLUDED_POT_LOADER_H