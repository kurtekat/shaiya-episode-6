#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/NpcTypes.h>
#include "common.h"

namespace shaiya
{
    struct SStaticText;

    #pragma pack(push, 1)
    // 0049AB60 ctor
    struct CNpc
    {
        void* vftable;          //0x00
        String<51> name;        //0x04
        PAD(1);
        D3DVECTOR pos;          //0x38
        D3DVECTOR dir;          //0x44
        D3DVECTOR up;           //0x50
        uint32_t id;            //0x5C
        NpcType type;           //0x60
        PAD(1);
        uint16_t typeId;        //0x62
        PAD(28);
        bool32_t moving;        //0x80
        PAD(8);
        D3DVECTOR movePos;      //0x8C
        D3DVECTOR moveDir;      //0x98
        int32_t model;          //0xA4
        PAD(100);
        SStaticText* typeText;  //0x10C
        int32_t typePointX;     //0x110
        SStaticText* nameText;  //0x114
        int32_t namePointX;     //0x118
        PAD(16);
        // 0x12C
    };
    #pragma pack(pop)

    static_assert(sizeof(CNpc) == 0x12C);
}
