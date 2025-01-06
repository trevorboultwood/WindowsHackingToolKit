#pragma once

#include <cstdint>
#include <vector>
#include<string>
#include "process.h"
#include<optional>
#include<span>
#include<cstddef>
#include<ranges>

#include<type_traits>

template<class T>
concept Character = 

std::same_as<T,char> ||
std::same_as<T,signed char> ||
std::same_as<T,unsigned char> ||
std::same_as<T,wchar_t> ||
std::same_as<T,char8_t> ||
std::same_as<T,char16_t> ||
std::same_as<T,char32_t>;


namespace bio
{
    std::vector<std::uint32_t> get_pids();
    std::vector<Process> find_process(std::string_view name);

    void replace_memory( const Process &process, 
        const MemoryRegion &region, 
        const std::span<const std:: uint8_t> find, 
        std::span<const std::uint8_t> replace, 
        std::optional<std::size_t> num_occurences = std::nullopt);

    template <class R>
    void replace_memory(
    const Process &process,
    const MemoryRegion &region,
    R &&find,
    R &&replace,
    std::optional<std::size_t> num_occurrences = std::nullopt) requires std::ranges::contiguous_range<R>
    {
        const auto find_bytes = reinterpret_cast<const std::uint8_t *>(std::ranges::data(find));
        const auto replace_bytes = reinterpret_cast<const std::uint8_t *>(std::ranges::data(replace));

        replace_memory(
            process,
            region,
            {find_bytes, std::ranges::size(find) * sizeof(std::ranges::range_value_t<R>)},
            {replace_bytes, std::ranges::size(replace) * sizeof(std::ranges::range_value_t<R>)},
            num_occurrences);
    }

   template<Character T, std::size_t N>
   void replace_memory(
        const Process &process,
        const MemoryRegion &region,
        const T(&find)[N],
        const T(&replace)[N],
        std::optional<std::size_t> num_occurrences = std::nullopt)
    {
        replace_memory(process, region, std::span{find, N-1}, std::span{replace, N-1}, num_occurrences);
    }


} 