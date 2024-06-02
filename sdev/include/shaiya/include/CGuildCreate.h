#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SNode.h>

namespace shaiya
{
    struct CUser;

    #pragma pack(push, 1)
    struct CGuildCreate
    {
        SNode node;              //0x00
        UINT8 result;            //0x08
        GuildName guildName;     //0x09
        PAD(2);
        UINT32 acceptCount;      //0x24
        ULONG masterId;          //0x28
        CUser* master;           //0x2C
        // 0x30
        std::array<ULONG, 30> acceptList;
        // 0xA8
        std::array<CUser*, 30> memberList;
        CRITICAL_SECTION cs120;  //0x120
        // 0x138
        PAD(68);
        // 0x17C
    };
    #pragma pack(pop)
}
