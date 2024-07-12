#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    struct SStaticText;

    #pragma pack(push, 1)
    // 004185A0 ctor
    struct CMonster
    {
        PAD(4);
        D3DVECTOR pos;          //0x04
        D3DVECTOR dir;          //0x10
        D3DVECTOR up;           //0x1C
        ULONG id;               //0x28
        UINT32 mobId;           //0x2C
        PAD(28);
        UINT32 status;          //0x4C
        PAD(4);
        UINT32 maxHealth;       //0x54
        UINT32 health;          //0x58
        D3DVECTOR movePos;      //0x5C
        D3DVECTOR moveDir;      //0x68
        UINT32 model;           //0x74
        PAD(36);
        ULONG targetId;         //0x9C
        UINT16 targetDmgHP;     //0xA0
        UINT16 targetDmgSP;     //0xA2
        UINT16 targetDmgMP;     //0xA4
        UINT16 healHealth;      //0xA6
        PAD(12);
        UINT8 attackSpeed;      //0xB4
        UINT8 moveSpeed;        //0xB5
        PAD(66);
        SStaticText* nameText;  //0xF8
        long namePointX;        //0xFC
        PAD(52);
        // 0x134
    };
    #pragma pack(pop)

    static_assert(sizeof(CMonster) == 0x134);
}
