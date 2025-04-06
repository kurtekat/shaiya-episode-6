#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/PartyTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_PARTY_SETDIVTYPE
    struct GamePartySetDivTypeOutgoing
    {
        uint16_t opcode{ 0xB0F };
        DivType divType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_PARTY_SETAUTOJOIN
    struct GamePartySetAutoJoinOutgoing
    {
        uint16_t opcode{ 0xB10 };
        bool isAutoJoin;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GamePartyBossMapPosOutgoing
    {
        uint16_t opcode{ 0xB1C };
        uint32_t x;
        uint32_t y;
        UnionType partyType;
    };
    #pragma pack(pop)
}
