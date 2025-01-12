#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/PartyTypes.h>

// CUser::PacketParty

namespace shaiya
{
    #pragma pack(push, 1)
    struct PartyItemDivIncoming
    {
        UINT16 opcode{ 0xB0F };
        ItemDivType itemDivType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PartyAutoJoinIncoming
    {
        UINT16 opcode{ 0xB10 };
        bool isAutoJoin;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PartyMapPingIncoming
    {
        UINT16 opcode{ 0xB1C };
        UINT32 x;
        UINT32 y;
        UnionType partyType;
    };
    #pragma pack(pop)
}
