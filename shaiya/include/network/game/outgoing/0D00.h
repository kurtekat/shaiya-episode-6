#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/item/CraftName.h>
#include <shaiya/include/item/Gems.h>

// CUser::PacketGuild

namespace shaiya
{
    #pragma pack(push, 1)
    struct Item0D29
    {
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        Gems gems;
        UINT8 count;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GuildBankItemListOutgoing
    {
        UINT16 opcode{ 0xD29 };
        UINT8 itemCount;
        Array<Item0D29, 50> itemList;

        constexpr int size_without_list() { return 3; }
    };
    #pragma pack(pop)
}
