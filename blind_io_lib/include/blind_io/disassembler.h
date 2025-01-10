#pragma once

#include<memory>
#include <vector>
#include "instruction.h"
#include <span>


namespace bio
{
    class Disassembler
    {
        public:

        Disassembler();
        ~Disassembler();

        std::vector<Instruction> disassemble(std::span<const uint8_t> data) const;


        private:
        
        struct implwmentation;

        std::unique_ptr<implwmentation> impl_;


    };
} // namespace bio
