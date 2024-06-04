#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/item/ItemDivType.h>

// CUser::PacketParty

namespace shaiya
{
    #pragma pack(push, 1)
    struct PartyItemDivIncoming
    {
        UINT16 opcode{ 0xB0F };
        ItemDivType itemDivType;

        PartyItemDivIncoming() = default;

        PartyItemDivIncoming(ItemDivType itemDivType)
            : itemDivType(itemDivType)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PartyAutoJoinIncoming
    {
        UINT16 opcode{ 0xB10 };
        bool isAutoJoin;

        PartyAutoJoinIncoming() = default;

        PartyAutoJoinIncoming(bool isAutoJoin)
            : isAutoJoin(isAutoJoin)
        {
        }
    };
    #pragma pack(pop)
}
