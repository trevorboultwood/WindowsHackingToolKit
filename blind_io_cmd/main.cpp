#include <print>
#include <stdio.h>
#include "test.h"
#include"process_utils.h"
#include "process.h"
#include <stdexcept>

int main()
{
    for(const auto &proc : bio::find_process("chrome.exe"))
    {
        std::println("{} - > {}", proc.name(), proc.pid());
        for(const auto &region : proc.memory_regions())
        {
            std::println("0x{:x} 0x{:x} {}", region.address(), region.size(), region.protection());
        }

  }
    return 0;
}