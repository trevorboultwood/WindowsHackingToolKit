#pragma once
#include <string_view>
#include <format>

namespace bio{


    enum class MemoryRegionProtection{

        NO_PROTECTION = 0,
        READ = 1<<0,
        WRITE = 1<< 1,
        EXECUTE = 1<<2
    };

std::string to_string(MemoryRegionProtection protection);


MemoryRegionProtection &operator|=(MemoryRegionProtection &prot1, MemoryRegionProtection prot2);
MemoryRegionProtection operator|(MemoryRegionProtection prot1, MemoryRegionProtection prot2);
MemoryRegionProtection &operator&=(MemoryRegionProtection &prot1, MemoryRegionProtection prot2);
MemoryRegionProtection operator&(MemoryRegionProtection prot1, MemoryRegionProtection prot2);
MemoryRegionProtection &operator^=(MemoryRegionProtection &prot1, MemoryRegionProtection prot2);
MemoryRegionProtection operator^(MemoryRegionProtection prot1, MemoryRegionProtection prot2);


}

template<>
struct std::formatter<bio::MemoryRegionProtection>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::begin(ctx);
    }
    auto format(const bio::MemoryRegionProtection &obj, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(),"{}", to_string(obj));
    }
};