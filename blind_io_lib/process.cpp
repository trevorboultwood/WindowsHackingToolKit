#include "process.h"

#include <cstdint>
#include<string>    
#include<Windows.h>
#include<stdexcept>
#include <Psapi.h>
#include<stddef.h>
#include<print>
#include<vector>
#include "memory_region.h"
#include "memory_region_protection.h"

namespace{
    bio::MemoryRegionProtection to_internal(DWORD protection)
    {
        switch(protection)
        {
            case PAGE_EXECUTE: return bio::MemoryRegionProtection::EXECUTE;
            case PAGE_READONLY: return bio::MemoryRegionProtection::READ;
            case PAGE_READWRITE: return bio::MemoryRegionProtection::READ | bio::MemoryRegionProtection::WRITE;
            case PAGE_EXECUTE_READ: return bio::MemoryRegionProtection::READ | bio::MemoryRegionProtection::EXECUTE;
            case PAGE_EXECUTE_READWRITE: return bio::MemoryRegionProtection::READ | bio::MemoryRegionProtection::WRITE |bio::MemoryRegionProtection::EXECUTE;
        }
        return bio::MemoryRegionProtection::NO_PROTECTION;
    }

}

namespace bio

{
    Process::Process(std::uint32_t pid)
    :pid_(pid)
    ,handle_(::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,pid_), ::CloseHandle)
    {
        if(!handle_){
            throw std::runtime_error("Failed to open process");
        }

    }

    std::uint32_t Process::pid() const
    {
        return pid_;
    }

    std::string Process::name() const
    {
        HMODULE module{};

        DWORD bytes_needed = 0;
        if(::K32EnumProcessModules(handle_,&module, sizeof(module), &bytes_needed) == 0)
        {
            throw std::runtime_error("failed to get first module");
        }
        

        std::string module_name(MAX_PATH, '\0');

        const auto chrs_written = ::K32GetModuleBaseNameA(handle_, module, module_name.data(), static_cast <DWORD> (module_name.size()));

        if(chrs_written == 0)
        {
            throw std::runtime_error("Failed to get module base name");

        }
        module_name.resize(chrs_written);
        

        return module_name;


    }


    std::vector<MemoryRegion> Process::memory_regions() const {
        std::vector<MemoryRegion> regions{};
        MEMORY_BASIC_INFORMATION mem_info{};
        std::byte *addr = 0x0;
        
        while(::VirtualQueryEx(handle_, addr, &mem_info, sizeof(mem_info)) != 0)
        {
            if(mem_info.State == MEM_COMMIT)
            {
                regions.push_back({reinterpret_cast<std::uintptr_t>(mem_info.BaseAddress), mem_info.RegionSize,to_internal( mem_info.Protect)});
                //std::println("{} {} {}", mem_info.BaseAddress, mem_info.RegionSize, mem_info.Protect);
            }
            addr += mem_info.RegionSize;


        }

    return regions; 

    }
}