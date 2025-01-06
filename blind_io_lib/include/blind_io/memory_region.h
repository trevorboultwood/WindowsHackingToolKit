#pragma once
#include<cstdint>

#include<cstddef>
#include"memory_region_protection.h"

namespace bio
{
    class MemoryRegion{
        public:
            MemoryRegion(std::uintptr_t address,std::size_t size, MemoryRegionProtection protection);
            std::uintptr_t address() const;
            std::size_t size() const;
            MemoryRegionProtection protection() const;
            bool test_protection(MemoryRegionProtection protection) const;
        private:
            std::uintptr_t address_;
            std::size_t size_;
            MemoryRegionProtection protection_;

    };
} // namespace bio
