#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/NpcTypes.h>
#include "QuestLink.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct Npc
    {
        NpcType type;          //0x00
        PAD(1);
        uint16_t typeId;       //0x02
        int32_t model;         //0x04
        int32_t moveDistance;  //0x08
        int32_t moveSpeed;     //0x0C
        NpcTeam country;       //0x10
        String<256> name;      //0x14
        QuestLink questLink;   //0x114
        // 0x124
    };
    #pragma pack(pop)

    static_assert(sizeof(Npc) == 0x124);
}
