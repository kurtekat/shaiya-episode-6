#pragma once
#include <shaiya/include/common.h>
#include "common.h"

namespace shaiya
{
    struct SStaticText;

    #pragma pack(push, 1)
    // 004185A0 ctor
    struct CMonster
    {
        void* vftable;          //0x00
        D3DVECTOR pos;          //0x04
        D3DVECTOR dir;          //0x10
        D3DVECTOR up;           //0x1C
        uint32_t id;            //0x28
        uint32_t mobId;         //0x2C
        PAD(28);
        uint32_t status;        //0x4C
        PAD(4);
        uint32_t maxHealth;     //0x54
        uint32_t health;        //0x58
        D3DVECTOR movePos;      //0x5C
        D3DVECTOR moveDir;      //0x68
        uint32_t model;         //0x74
        PAD(36);
        uint32_t targetId;      //0x9C
        uint16_t targetDmgHP;   //0xA0
        uint16_t targetDmgSP;   //0xA2
        uint16_t targetDmgMP;   //0xA4
        uint16_t healHP;        //0xA6
        PAD(12);
        uint8_t attackSpeed;    //0xB4
        uint8_t moveSpeed;      //0xB5
        PAD(66);
        SStaticText* nameText;  //0xF8
        int32_t namePointX;     //0xFC
        PAD(52);
        // 0x134
        
        static D3DXMATRIX* GetBoneMatrix(CMonster* mob, int boneNumber);
    };
    #pragma pack(pop)

    static_assert(sizeof(CMonster) == 0x134);
}
