#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CParticleData
    {
        PAD(44);
        D3DVECTOR pos;     //0x2C
        D3DVECTOR dir;     //0x38
        D3DVECTOR up;      //0x44
        PAD(180);
        int effectDataId;  //0x104
        //
    };
    #pragma pack(pop)
}
