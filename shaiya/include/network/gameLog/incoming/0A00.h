#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    enum struct GameLogBossMobActionType : uint8_t
    {
        None, 
        Attack, 
        Damage, 
        Heal, 
        Death, 
        DebuffAdd, 
        DebuffRemove, 
        ItemDrop, 
        MoneyDrop
    };

    #pragma pack(push, 1)
    // TP_GAMELOG_BOTHMOB
    // ActionType 173
    struct GameLogBossMobIncoming
    {
        uint16_t opcode{ 0xA04 };
        uint32_t mapId;
        float x;
        float y;
        float z;
        GameLogBossMobActionType actionType;
        String<32> bossName;  // Text1
        String<32> charName;  // Text3
        String<32> skillName; // Text4
        uint32_t damage;
        uint32_t health;
    };
    #pragma pack(pop)
}
