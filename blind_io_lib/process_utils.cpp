#include "process_utils.h"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <optional>
#include <ranges>
#include <span>
#include <stdexcept>
#include <string_view>
#include <vector>


#define NOMINMAX
#include <Windows.h>

#include <Psapi.h>
#include "process.h"
namespace bio
{
    std::vector<std::uint32_t> get_pids()
    {
        std::vector<DWORD> pids{1024};
        DWORD bytes_retunred = 0;

        do{
            pids.resize(pids.size() * 2);

            if(::K32EnumProcesses(pids.data(), static_cast<std::uint32_t> (pids.size() * sizeof(DWORD)), &bytes_retunred) == 0)
            {
                throw std::runtime_error("Failed to get PIDs");
            }

        } while (bytes_retunred == pids.size() * sizeof(DWORD));

        //need to revise this! Im not familar with modern C++.
        return pids
        | std::views::take(bytes_retunred / sizeof(DWORD))
        | std::views::transform([](auto pid) -> std::uint32_t{return pid;})
        | std::ranges::to<std::vector>();

    }


    std::vector<Process> find_process(std::string_view name)
    {
        std::vector<Process> procs{};

        for(const auto pid : get_pids())
        {
            try{
                Process proc{pid};
                if(proc.name() == name)
                procs.push_back(std::move(proc));
            }
            catch(std::runtime_error&)
            {

            }
        }

        return procs;
    }


    void replace_memory(
    const Process &process,
    const MemoryRegion &region,
    std::span<const std::uint8_t> find,
    std::span<const std::uint8_t> replace,
    std::optional<std::size_t> num_occurrences)
{
    assert(find.size() == replace.size());
    assert(region.test_protection(MemoryRegionProtection::READ | MemoryRegionProtection::WRITE));

    auto mem = process.read(region);
    auto mem_span = std::span(mem);

    auto remaining_ocurrences = num_occurrences.value_or(std::numeric_limits<std::size_t>::max());

    while (!mem_span.empty() && (remaining_ocurrences > 0))
    {
        if (const auto found = std::ranges::search(mem_span, find); !found.empty())
        {
            const auto begin = std::ranges::distance(std::cbegin(mem_span), std::cbegin(found));

            std::memcpy(mem_span.data() + begin, replace.data(), replace.size());

            process.write(region, mem);

            mem_span = mem_span.subspan(begin);
            --remaining_ocurrences;
        }
        else
        {
            break;
        }
    }
}
    
} 