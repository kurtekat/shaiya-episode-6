#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/PartyTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CUnionPartyInfo
    {
        UnionType partyType;   //0x00
        uint32_t groupNumber;  //0x04
        uint32_t bossId;       //0x08
        uint32_t subBossId;    //0x0C
        uint32_t divSeq;       //0x10
        bool32_t isAutoJoin;   //0x14
        uint32_t slot;         //0x18
        // 0x1C
    };
    #pragma pack(pop)

    static_assert(sizeof(CUnionPartyInfo) == 0x1C);
}
