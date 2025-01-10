#pragma once

#include<string>
#include<string_view>
#include<cstddef>
#include<format>

namespace bio
{
    class Instruction{
        public:
            Instruction(std::string_view mnemonic, std::string_view operrands, std::size_t size);

            std::string_view mnemonic() const;
            std::string_view operrands() const;
            std::size_t size() const;

        private:

            std::string mnemonic_;
            std::string operrands_;
            std::size_t size_;
    };
}

/**
 * Specialisation of std::formatter for MemoryRegionProtection.
 */
template <> 
struct std::formatter<bio::Instruction>
{
    // simple implementation, we don't need to parse the format string
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::begin(ctx);
    }

    // format according to to_string implementation
    auto format(const bio::Instruction &obj, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), "{} {} ({})",obj.mnemonic(), obj.operrands(), obj.size());
    }
};
