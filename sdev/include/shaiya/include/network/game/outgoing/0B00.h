#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemDivType.h>
#include <shaiya/include/common/PartyType.h>

// CUser::PacketParty

namespace shaiya
{
    #pragma pack(push, 1)
    struct PartyItemDivOutgoing
    {
        UINT16 opcode{ 0xB0F };
        ItemDivType itemDivType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PartyAutoJoinOutgoing
    {
        UINT16 opcode{ 0xB10 };
        bool isAutoJoin;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PartyMapPingOutgoing
    {
        UINT16 opcode{ 0xB1C };
        UINT32 x;
        UINT32 y;
        UnionType partyType;

        PartyMapPingOutgoing() = default;
        
        PartyMapPingOutgoing(UINT32 x, UINT32 y, UnionType partyType)
            : x(x), y(y), partyType(partyType)
        {
        }
    };
    #pragma pack(pop)
}
