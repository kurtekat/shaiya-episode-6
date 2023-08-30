#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/CParty.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct RaidConfigLootIncoming
    {
        UINT16 opcode{ 0xB0F };
        ItemDivType itemDivType;
    };

    struct RaidConfigLootOutgoing
    {
        UINT16 opcode{ 0xB0F };
        ItemDivType itemDivType;
    };
    #pragma pack(pop)
}
