#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_BANK_UNIT
    struct BankUnit_EP5
    {
        uint8_t slot;
        uint8_t type;
        uint8_t typeId;
        uint16_t quality;
        Gems gems;
        uint8_t count;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_BANK_UNIT
    struct BankUnit_EP6_4
    {
        uint8_t slot;
        uint8_t type;
        uint8_t typeId;
        uint16_t quality;
        Gems gems;
        uint8_t count;
        time32_t fromDate;
        time32_t toDate;
        CraftName craftName;
    };
    #pragma pack(pop)
}
