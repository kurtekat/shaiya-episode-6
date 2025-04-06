#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_NPC_ENTER
    struct GameNpcZoneEnterOutgoing
    {
        uint16_t opcode{ 0xE01 };
        uint32_t objectId;
        uint8_t npcType;
        uint16_t npcTypeId;
        float x;
        float y;
        float z;
        uint16_t direction;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameNpcZoneLeaveOutgoing
    {
        uint16_t opcode{ 0xE02 };
        uint32_t objectId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_NPC_MOVE
    struct GameNpcMoveOutgoing
    {
        uint16_t opcode{ 0xE03 };
        uint32_t objectId;
        uint8_t motion;
        float x;
        float y;
        float z;
    };
    #pragma pack(pop)
}
