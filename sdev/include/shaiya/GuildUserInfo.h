#pragma once
#include <shaiya/include/common.h>
#include "SNode.h"

namespace shaiya
{
    struct CUser;

    #pragma pack(push, 1)
    struct GuildUserInfo : SNode
    {
        uint32_t charId;            //0x08
        String<21> charName;        //0x0C
        PAD(3);
        int32_t job;                //0x24
        int32_t level;              //0x28
        int32_t rank;               //0x2C
        CUser* user;                //0x30
        uint32_t gameWarBillingId;  //0x34
        bool32_t grbZoneEnterFlag;  //0x38
        // 0x3C
    };
    #pragma pack(pop)

    static_assert(sizeof(GuildUserInfo) == 0x3C);
}
