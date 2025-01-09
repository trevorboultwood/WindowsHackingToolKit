#pragma once

#include<string>
#include<string_view>
#include<cstddef>



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