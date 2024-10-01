#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/PartyType.h>

// CUser::PacketParty

namespace shaiya
{
    #pragma pack(push, 1)
    struct PartyItemDivIncoming
    {
        UINT16 opcode{ 0xB0F };
        enum struct 
            ItemDivType : UINT32 {
            Group = 1,
            Random,
            Unknown,
            Master
        } itemDivType;
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
