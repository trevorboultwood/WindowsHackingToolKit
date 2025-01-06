#pragma once

#include <cstdint>
#include <vector>
#include<string>
#include"auto_release.h"
#include<vector>
#include "memory_region.h"
#define NOMINMAX //Windows.h defines and replaces min and max
#include<Windows.h>
#include<span>


namespace bio
{
    class Process
    {
        public:
            Process(std::uint32_t pid);
            std::uint32_t pid() const;
            std::string name() const;
            std::vector<MemoryRegion> memory_regions() const;
            std::vector<std::uint8_t> read(const MemoryRegion & region) const;
            void write( const MemoryRegion &region, std::span<const std::uint8_t> data) const;
            
        private:
            std::uint32_t pid_;
            AutoRelease<HANDLE> handle_;
    };
} 