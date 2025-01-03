#include "process_utils.h"

#include <cstdint>
#include <vector>
#include <Windows.h>
#include <ranges> //modern!
#include <stdexcept>
#include <Psapi.h>
#include"process.h"

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
    
} 