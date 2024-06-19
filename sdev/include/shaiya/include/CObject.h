#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/SVector.h"

namespace shaiya
{
    struct CUser;

    #pragma pack(push, 1)
    struct CObject
    {
        SVector pos;
        //

        static void PSendViewCombat(CUser* user, void* data, int len);
    };
    #pragma pack(pop)
}
