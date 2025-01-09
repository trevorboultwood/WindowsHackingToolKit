////////////////////////////////////////////////////////////////////////////////
//         Distributed under the Boost Software License, Version 1.0.         //
//            (See accompanying file LICENSE or copy at                       //
//                 https://www.boost.org/LICENSE_1_0.txt)                     //
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <filesystem>
#include <memory>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "memory_region.h"
#include "memory_region_protection.h"
#include "thread.h"

namespace bio
{

/**
 * This struct represents a remote function in a process.
 */
struct RemoteFunction
{
    /** The library name the function is in. */
    std::string library_name;

    /** The function name. */
    std::string name;

    /** The address of the function. */
    std::uintptr_t address;
};

/**
 * This class represents a view onto a running process and provides methods for interacting with it.
 */
class Process
{
  public:
    /**
     * Construct a new Process object from a pid.
     *
     * @param pid
     *   Pid of process.
     */
    Process(std::uint32_t pid);

    ~Process();
    Process(Process &&);
    Process &operator=(Process &&);

    /**
     * Get process pid.
     *
     * @returns
     *   Process pid.
     */
    std::uint32_t pid() const;

    /**
     * Get process name.
     *
     * @returns
     *   Process name.
     */
    std::string name() const;

    /**
     * Get all current memory regions fro the process.
     *
     * @returns
     *   Process memory regions.
     */
    std::vector<MemoryRegion> memory_regions() const;

    /**
     * Read a region of memory.
     *
     * @param region
     *   The region to read.
     *
     * @returns
     *   The read region.
     */
    std::vector<std::uint8_t> read(const MemoryRegion &region) const;

    /**
     * Read a region of memory.
     *
     * @param address
     *   The address (in the process) to read from.
     *
     * @param size
     *   The size of the region to read in bytes.
     *
     * @returns
     *   The read region.
     */
    std::vector<std::uint8_t> read(std::uintptr_t address, std::size_t size) const;

    /**
     * Write data to the supplied region.
     *
     * @param region
     *   The region to write to.
     *
     * @param data
     *   The data to write (must not be larger than region).
     */
    void write(const MemoryRegion &region, std::span<const std::uint8_t> data) const;


    void write(std::uintptr_t address, std::span<const std::uint8_t> data) const;

    void set_protection(std::uintptr_t address, MemoryRegionProtection new_protection) const;
    
    MemoryRegion allocate(std::size_t bytes) const;
    std::optional<MemoryRegion> allocate(std::uintptr_t address, std::size_t bytes) const;



    std::vector<Thread> threads() const;

    void load_library(const std::filesystem::path &path) const;

    void set_hook(std::uintptr_t insert_address, std::uintptr_t hook_address) const;

    std::vector<RemoteFunction> address_of_function(std::string_view name) const;

  private:
    struct implementation;

    /** Pointer to implementation. */
    std::unique_ptr<implementation> impl_;
};

}