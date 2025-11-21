#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_EXC_ADD_DEST
    struct GamePvPExcAddDestOutgoing_EP5
    {
        uint16_t opcode{ 0x240D };
        uint8_t destSlot;
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
        uint16_t quality;
        Gems gems;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_EXC_ADD_DEST
    struct GamePvPExcAddDestOutgoing_EP6_4
    {
        uint16_t opcode{ 0x240D };
        uint8_t destSlot;
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
        uint16_t quality;
        time32_t fromDate;
        time32_t toDate;
        Gems gems;
        CraftName craftName;
    };
    #pragma pack(pop)
}
