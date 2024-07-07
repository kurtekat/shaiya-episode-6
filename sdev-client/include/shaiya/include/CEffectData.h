#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    struct CParticleData;

    #pragma pack(push, 1)
    struct CEffectData
    {
        PAD(4);
        UINT32 numMeshes;     //0x04
        UINT32 numTextures;   //0x08
        UINT32 numScenes;     //0x0C
        UINT32 numSequences;  //0x10
        PAD(20);
        char path[MAX_PATH];  //0x28
        // 0x12C

        static BOOL CreateFromFile(CEffectData* effectData, const char* path, const char* fileName/*.eft*/);
    };
    #pragma pack(pop)
}
