#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    FWDDECL CUser;

    #pragma pack(push, 1)
    struct CObject
    {
        static void PSendViewCombat(CUser* user, void* data, int len);
    };
    #pragma pack(pop)
}
