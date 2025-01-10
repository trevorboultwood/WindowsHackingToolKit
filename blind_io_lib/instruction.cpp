#include "instruction.h"

#include<string>
#include<string_view>
#include<cstddef>

namespace bio
{
    Instruction::Instruction(std::string_view mnemonic, std::string_view operrands, std::size_t size)
    : mnemonic_(mnemonic),
    operrands_(operrands),
    size_(size)
    {

    }
    std::string_view Instruction::mnemonic() const
    {
        return mnemonic_;
        
    }
    std::string_view Instruction::operrands() const
    {
        return operrands_;

    }
    std::size_t Instruction::size() const
    {
        return size_;

        

    }
} // namespace bio
