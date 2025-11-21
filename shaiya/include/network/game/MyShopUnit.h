#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct MyShopUnit_EP5
    {
        uint8_t shopSlot;
        uint32_t money;
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
        uint16_t quality;
        Gems gems;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct MyShopUnit_EP6_4
    {
        uint8_t shopSlot;
        uint32_t money;
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
