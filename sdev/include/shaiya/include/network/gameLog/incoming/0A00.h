#pragma once
#include <strsafe.h>
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
        CharArray<32> text1;
        CharArray<32> text3;
        CharArray<32> text4;
        UINT32 damage;
        UINT32 health;

        GameLogBossMobIncoming() = default;

        GameLogBossMobIncoming(UINT32 mapId, float x, float y, float z, GameLogBossMobActionType actionType,
            const char* text1, const char* text3, const char* text4, UINT32 damage, UINT32 health
        ) 
            : mapId(mapId), x(x), y(y), z(z), actionType(actionType), damage(damage), health(health)
        {
            StringCbCopyA(this->text1.data(), this->text1.size(), text1);
            StringCbCopyA(this->text3.data(), this->text3.size(), text3);
            StringCbCopyA(this->text4.data(), this->text4.size(), text4);
        }
    };
    #pragma pack(pop)
}
