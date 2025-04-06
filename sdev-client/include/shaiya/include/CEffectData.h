#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct CEffectModel;
    struct CParticleData;
    struct CTexture;

    enum struct EffectDataType : int32_t
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
        int32_t numEffectModels;     //0x04
        int32_t numTextures;         //0x08
        int32_t numScenes;           //0x0C
        int32_t numSequences;        //0x10
        PAD(4);
        CEffectModel* effectModels;  //0x18
        CTexture* textures;          //0x1C
        EffectScene* scenes;         //0x20
        EffectSequence* sequences;   //0x24
        String<260> path;            //0x28
        // 0x12C

        static int CreateFromFile(CEffectData* effectData, const char* path, const char* fileName/*.eft*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(CEffectData) == 0x12C);
}
