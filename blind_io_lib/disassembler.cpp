#include "disassembler.h"
#include<memory>
#include<stdexcept>


#include <capstone/capstone.h>
namespace bio
{
    struct Disassembler::implwmentation
    {
        ::csh handle;



    };

    Disassembler::Disassembler()
    :impl_(std::make_unique<implwmentation>())
    {
        if(::cs_open(CS_ARCH_X86, CS_MODE_64, &impl_->handle) != CS_ERR_OK)
        {
            throw std::runtime_error("failed to initialize capstone");
        }
        

        if(::cs_option(impl_->handle, CS_OPT_DETAIL, CS_OPT_ON) != CS_ERR_OK)
        {
            throw std::runtime_error("failed to set capstone option");
        }


    }

    Disassembler::~Disassembler()
    {
        ::cs_close(&impl_->handle);
    }

}