#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    enum struct GameItemZoneEnterType : uint8_t
    {
        UserDrop = 1,
        MobDrop
    };

    #pragma pack(push, 1)
    // TP_ITEM_ENTER
    struct GameItemZoneEnterOutgoing
    {
        uint16_t opcode{ 0x401 };
        uint32_t objectId;
        GameItemZoneEnterType enterType;
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
        float x;
        float y;
        float z;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameItemZoneLeaveOutgoing
    {
        uint16_t opcode{ 0x402 };
        uint32_t objectId;
    };
    #pragma pack(pop)
}
