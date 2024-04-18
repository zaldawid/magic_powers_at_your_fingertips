#ifndef INCLUDED_EXPERIMENTAL_COMPACTOR
#define INCLUDED_EXPERIMENTAL_COMPACTOR

#include <concepts>
#include <set>
#include <string>
#include <functional>
#include <iterator>
#include <future>

#include "compactor.h"
#include "deposit.h"

namespace pot::exp
{
    struct seq_tag {};
    inline seq_tag seq;

    struct par_tag {};
    inline par_tag par;


    template <typename Iter>
    Iter compact(par_tag, Iter begin, Iter end)
    requires std::same_as<typename std::iterator_traits<Iter>::value_type, Deposit>
    {
        // case insensitive comparison for names
        auto icompare = [](const std::string& a, const std::string& b) {
            return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), 
                    [](char a, char b) { return std::tolower(a) < std::tolower(b); });
        };

        std::set<std::string, decltype(icompare)> seen_names{icompare};

        // make sure that the first elements are all unique
        // single sweep through the range and swapping elements
        // with the next unique element
        auto unique_end{begin};

        for (auto seeker{begin}; seeker != end;)
        {
            if (seen_names.insert(std::string{ seeker->name() }).second)
            {
                std::iter_swap(seeker, unique_end++);
            }
            ++seeker;
        }

        std::vector<std::future<void>> tasks{};

        for (auto first{begin}; first != unique_end; ++first)
        {
            tasks.push_back(std::async(std::launch::async, [first, unique_end] (auto end)  {
                double total = first->amount();
                auto next = unique_end;
                while (next != end)
                {
                    if (std::equal(first->name().begin(), first->name().end(), next->name().begin(),
                                   [](char a, char b) { return std::tolower(a) == std::tolower(b); }))
                    {
                        total += next->amount();
                        *next = *(--end);
                    }
                    else
                    {
                        ++next;
                    }
                }

                *first = {first->name(), total};

            }, end));
        }

        for (auto& task : tasks)
        {
            task.get();
        }
 
        return unique_end;
    }

    template <typename Iter>
    Iter compact(seq_tag, Iter begin, Iter end)
        requires std::same_as<typename std::iterator_traits<Iter>::value_type, Deposit>
    {
        // case insensitive comparison for names
        auto icompare = [](const std::string& a, const std::string& b) {
            return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(),
                                                [](char a, char b) { return std::tolower(a) < std::tolower(b); });
        };

        std::set<std::string, decltype(icompare)> seen_names{icompare};

        // make sure that the first elements are all unique
        // single sweep through the range and swapping elements
        // with the next unique element
        auto unique_end{begin};

        for (auto seeker{begin}; seeker != end;)
        {
            if (seen_names.insert(std::string{ seeker->name() }).second)
            {
                std::iter_swap(seeker, unique_end++);
            }
            ++seeker;
        }

        for (auto first{begin}; first != unique_end; ++first)
        {
            double total = first->amount();
            auto next = unique_end;
            while (next != end)
            {
                if (std::equal(first->name().begin(), first->name().end(), next->name().begin(),
                               [](char a, char b) { return std::tolower(a) == std::tolower(b); }))
                {
                    total += next->amount();
                    *next = *(--end);
                }
                else
                {
                    ++next;
                }
            }

            if (total != 0)
            {
                *first = {first->name(), total};
            }
            else
            {
                *first = *(--unique_end);
            }
        }

        return unique_end;
    };
}

#endif // INCLUDED_EXPERIMENTAL_COMPACTOR