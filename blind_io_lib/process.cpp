#include "process.h"

#include <cstdint>
#include<string>    
#include<Windows.h>
#include<stdexcept>
#include <Psapi.h>
namespace bio
{
    Process::Process(std::uint32_t pid)
    :pid_(pid)
    ,handle_(::OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,pid_), ::CloseHandle)
    {
        if(!handle_){
            throw std::runtime_error("Failed to open process");
        }

    }

    std::uint32_t Process::pid() const
    {
        return pid_;
    }

    std::string Process::name() const
    {
        HMODULE module{};

        DWORD bytes_needed = 0;
        if(::K32EnumProcessModules(handle_,&module, sizeof(module), &bytes_needed) == 0)
        {
            throw std::runtime_error("failed to get first module");
        }
        

        std::string module_name(MAX_PATH, '\0');

        const auto chrs_written = ::K32GetModuleBaseNameA(handle_, module, module_name.data(), static_cast <DWORD> (module_name.size()));

        if(chrs_written == 0)
        {
            throw std::runtime_error("Failed to get module base name");

        }
        module_name.resize(chrs_written);
        

        return module_name;


    }
}