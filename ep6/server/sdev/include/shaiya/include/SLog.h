#pragma once
#include <shaiya/common.h>

#include <string>
#include <stdio.h>

namespace shaiya
{
    constexpr Address* g_GameLog = 0x587970;
    
    class SLog
    {
    public:
            static void log(const std::string& text);
    private:
            static FILE* get_log_file();
    };
}
