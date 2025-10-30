#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct CUser;

    #pragma pack(push, 1)
    struct PartyUser
    {
        int32_t index;
        CUser* user;
    };
    #pragma pack(pop)

    static_assert(sizeof(PartyUser) == 0x8);
}
