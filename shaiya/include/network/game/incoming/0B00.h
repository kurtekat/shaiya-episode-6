#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/PartyTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TPC_PARTY_SETDIVTYPE
    struct GamePartySetDivTypeIncoming
    {
        uint16_t opcode{ 0xB0F };
        DivType divType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_PARTY_SETAUTOJOIN
    struct GamePartySetAutoJoinIncoming
    {
        uint16_t opcode{ 0xB10 };
        bool isAutoJoin;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GamePartyBossMapPosIncoming
    {
        uint16_t opcode{ 0xB1C };
        uint32_t x;
        uint32_t y;
        UnionType partyType;
    };
    #pragma pack(pop)
}
