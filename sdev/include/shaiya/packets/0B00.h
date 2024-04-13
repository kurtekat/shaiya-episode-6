#pragma once
#include <include/shaiya/common.h>

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
    struct PartyItemDivOutgoing
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
    struct PartyAutoJoinOutgoing
    {
        UINT16 opcode{ 0xB10 };
        bool isAutoJoin;
    };
    #pragma pack(pop)
}
