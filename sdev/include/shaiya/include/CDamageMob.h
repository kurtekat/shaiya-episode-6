#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SNode.h>
#include <shaiya/include/common/SSyncList.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct stDamageMob
    {
        SNode node;        //0x00 
        UINT8 damageType;  //0x08
        PAD(3);
        ULONG charId;      //0x0C
        UINT32 maxDamage;  //0x10
        UINT32 maxAggro;   //0x14
        PAD(4);
        // 0x1C
    };

    struct CDamageMob
    {
        PAD(4);
        SSyncList<stDamageMob> list;
        // 0x30
    };
    #pragma pack(pop)
}
