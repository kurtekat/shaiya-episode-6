#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_MOB_ATTACKPC
    struct GameMobAttackCharOutgoing
    {
        uint16_t opcode{ 0x605 };
        uint8_t damageType;
        uint32_t objectId;
        uint32_t targetId;
        uint16_t health;
        uint16_t mana;
        uint16_t stamina;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_MOB_RECOVER
    struct GameMobRecoverOutgoing
    {
        uint16_t opcode{ 0x610 };
        uint32_t objectId;
        uint32_t healthAdd;
    };
    #pragma pack(pop)
}
