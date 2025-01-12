#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/SNode.h"

namespace shaiya
{
    struct CUser;

    #pragma pack(push, 1)
    struct CGuildCreate
    {
        SNode node;                 //0x00
        PAD(1);
        CharArray<25> name;         //0x09
        PAD(2);
        UINT32 joinCount;           //0x24
        ULONG masterId;             //0x28
        CUser* master;              //0x2C
        Array<ULONG, 30> joiners;   //0x30
        Array<CUser*, 30> members;  //0xA8
        CRITICAL_SECTION cs;        //0x120
        CharArray<65> remark;       //0x138
        PAD(3);
        // 0x17C
    };
    #pragma pack(pop)

    static_assert(sizeof(CGuildCreate) == 0x17C);
}
