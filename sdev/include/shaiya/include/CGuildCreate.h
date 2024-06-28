#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SNode.h>

namespace shaiya
{
    struct CUser;

    #pragma pack(push, 1)
    struct CGuildCreate
    {
        PAD(9);
        CharArray<25> name;          //0x09
        PAD(2);
        UINT32 acceptCount;          //0x24
        ULONG masterId;              //0x28
        CUser* master;               //0x2C
        Array<ULONG, 30> acceptees;  //0x30
        Array<CUser*, 30> members;   //0xA8
        CRITICAL_SECTION cs;         //0x120
        CharArray<66> remark;        //0x138
        PAD(2);
        // 0x17C
    };
    #pragma pack(pop)
}
