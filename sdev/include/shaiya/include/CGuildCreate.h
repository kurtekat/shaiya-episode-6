#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SNode.h>

namespace shaiya
{
    struct CUser;

    #pragma pack(push, 1)
    struct CGuildCreate
    {
        SNode node;               //0x00
        PAD(1);
        CharArray<25> guildName;  //0x09
        PAD(2);
        UINT32 acceptCount;       //0x24
        ULONG masterId;           //0x28
        CUser* master;            //0x2C
        // 0x30
        Array<ULONG, 30> acceptList;
        // 0xA8
        Array<CUser*, 30> memberList;
        CRITICAL_SECTION cs;      //0x120
        CharArray<66> remark;     //0x138
        PAD(2);
        // 0x17C
    };
    #pragma pack(pop)
}
