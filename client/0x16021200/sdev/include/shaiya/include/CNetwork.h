#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CNetwork
    {
        static void Send(void* buf, int len)
        {
            typedef void(__cdecl* LPFN)(void*, int);
            (*(LPFN)0x5EA9A0)(buf, len);
        }
    };
    #pragma pack(pop)
}
