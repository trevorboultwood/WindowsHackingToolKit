#pragma once

#include <cstdint>
#include <vector>
#include<string>
#include "process.h"

namespace bio
{
    std::vector<std::uint32_t> get_pids();
    std::vector<Process> find_process(std::string_view name);
} 