#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SNode.h>

namespace shaiya
{
    FWDDECL CUser;

    #pragma pack(push, 1)
    struct CGuildCreate
    {
        SNode node;                    //0x00
        UINT8 result;                  //0x08
        GuildName guildName;           //0x09
        PAD(2);
        UINT32 acceptCount;            //0x24
        CharId leaderId;               //0x28
        CUser* leader;                 //0x2C
        Array<CharId, 30> acceptList;  //0x30
        Array<CUser*, 30> userList;    //0xA8
        CRITICAL_SECTION cs120;        //0x120
        // 0x138
        PAD(68);
        // 0x17C
    };
    #pragma pack(pop)
}
