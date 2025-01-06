#pragma once

#include <cstdint>
#include <vector>
#include<string>
#include"auto_release.h"
#include<vector>
#include "memory_region.h"
#include"Windows.h"


namespace bio
{
    class Process
    {
        public:
            Process(std::uint32_t pid);
            std::uint32_t pid() const;
            std::string name() const;
            std::vector<MemoryRegion> memory_regions() const;
            
        private:
            std::uint32_t pid_;
            AutoRelease<HANDLE> handle_;
    };
} 