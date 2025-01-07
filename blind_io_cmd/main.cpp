////////////////////////////////////////////////////////////////////////////////
//         Distributed under the Boost Software License, Version 1.0.         //
//            (See accompanying file LICENSE or copy at                       //
//                 https://www.boost.org/LICENSE_1_0.txt)                     //
////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <chrono>
#include <print>
#include <ranges>
#include <span>
#include <stdexcept>
#include <string_view>
#include <thread>

#include "debugger.h"
#include "process.h"
#include "process_utils.h"

using namespace std::literals;

int main()
{
    auto procs = bio::find_process("Notepad.exe");
    assert(procs.size() == 1);

    auto &proc = procs.front();

    const auto threads = proc.threads();

    std::println("{} -> {}", proc.name(), proc.pid());

    for (const auto &thread : threads)
    {
        std::println("tid: {}", thread.tid());
    }

    bio::Debugger dbg{std::move(proc)};


    const auto regs = dbg.registers(threads.front().tid());
    std::println("REGISTERS: ");
    std::println("0x{}", regs.rax);
    std::println("0x{:x}", regs.rbx);
    std::println("0x{:x}", regs.rcx);
    std::println("0x{:x}", regs.rdx);
    std::println("0x{:x}", regs.rsi);
    std::println("0x{:x}", regs.rdi);
    std::println("0x{:x}", regs.rsp);
    std::println("0x{:x}", regs.rbp);
    std::println("0x{:x}", regs.rip);
    std::println("0x{:x}", regs.r8);
    std::println("0x{:x}", regs.r9);
    std::println("0x{:x}", regs.r10);
    std::println("0x{:x}", regs.r11);
    std::println("0x{:x}", regs.r12);
    std::println("0x{:x}", regs.r13);
    std::println("0x{:x}", regs.r14);
    std::println("0x{:x}", regs.r15);


    //std::this_thread::sleep_for(5s);
    //dbg.load_library("/tmp/libtest.so");

    return 0;
}
