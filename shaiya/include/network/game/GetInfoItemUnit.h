#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_GETINFO_ITEMUNIT
    struct GetInfoItemUnit_EP5
    {
        uint8_t slot;
        uint8_t type;
        uint8_t typeId;
        uint16_t quality;
        Gems gems;
        CraftName craftName;
    };
    #pragma pack(pop)
}
