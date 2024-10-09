#pragma once
#include "include/shaiya/common.h"

namespace shaiya
{
    struct CEffectModel;
    struct CParticleData;
    struct CTexture;

    enum struct EffectDataType : UINT32
    {
        EFT,
        EF2,
        EF3
    };

    struct EffectScene
    {
    };

    struct EffectSequence
    {
    };

    #pragma pack(push, 1)
    struct CEffectData
    {
        void* vftable;               //0x00
        UINT32 numEffectModels;      //0x04
        UINT32 numTextures;          //0x08
        UINT32 numScenes;            //0x0C
        UINT32 numSequences;         //0x10
        PAD(4);
        CEffectModel* effectModels;  //0x18
        CTexture* textures;          //0x1C
        EffectScene* scenes;         //0x20
        EffectSequence* sequences;   //0x24
        CharArray<MAX_PATH> path;    //0x28
        // 0x12C

        static BOOL CreateFromFile(CEffectData* effectData, const char* path, const char* fileName/*.eft*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CEffectData) == 0x12C);
}
