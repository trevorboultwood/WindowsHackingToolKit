#pragma once

#include<memory>



namespace bio
{
    class Disassembler
    {
        public:

        Disassembler();
        ~Disassembler();



        private:
        
        struct implwmentation;

        std::unique_ptr<implwmentation> impl_;


    };
} // namespace bio
