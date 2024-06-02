#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    enum struct GameLogBossMobActionType : UINT8
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
    // ActionType 173
    struct GameLogBossMobIncoming
    {
        UINT16 opcode{ 0xA04 };
        UINT32 mapId;
        float x;
        float y;
        float z;
        GameLogBossMobActionType actionType;
        std::array<char, 32> text1;
        std::array<char, 32> text3;
        std::array<char, 32> text4;
        UINT32 damage;
        UINT32 health;
    };
    #pragma pack(pop)
}
