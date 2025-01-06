#include <print>
#include <stdio.h>
#include "test.h"
#include"process_utils.h"
#include "process.h"
#include <stdexcept>
#include<ranges>  
#include<span>

#include<string_view>

using namespace std::literals;

int main()
{
    std::println("starting 2");
    for(const auto &proc : bio::find_process("Notepad.exe"))
    {
        std::println("{} - > {}", proc.name(), proc.pid());
        for(const auto &region : proc.memory_regions())
        {
            //std::println("0x{:x} 0x{:x} {}", region.address(), region.size(), region.protection());
            if(region.test_protection(bio::MemoryRegionProtection::READ | bio::MemoryRegionProtection::WRITE))
            {
                bio::replace_memory(proc,region,L"vorpal", L"VORPAL",1);
                
            }
        }

  }
  std::println("Finished!");
    return 0;
}