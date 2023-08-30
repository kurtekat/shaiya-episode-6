#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct Item0307
    {
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        Gems gems;
        CraftName craftName;
    };

    struct UserInspectIncoming
    {
        UINT16 opcode{ 0x307 };
        ULONG charId;
    };

    struct UserInspectOutgoing
    {
        UINT16 opcode{ 0x307 };
        UINT8 itemCount;
        #ifdef WITH_EXTENDED_EQUIPMENT
        Array<Item0307, ITEM_LIST_SIZE> itemList;
        #else
        Array<Item0307, 12> itemList;
        #endif
    };
    #pragma pack(pop)
}
