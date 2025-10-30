#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>
#include "SNode.h"

namespace shaiya
{
    struct CUser;

    #pragma pack(push, 1)
    struct CGuildCreate : SNode
    {
        bool typeCreate;              //0x08
        String<25> name;              //0x09
        PAD(2);
        int32_t okayCount;            //0x24
        uint32_t masterId;            //0x28
        CUser* master;                //0x2C
        Array<uint32_t, 30> userIds;  //0x30
        Array<CUser*, 30> users;      //0xA8
        CRITICAL_SECTION cs;          //0x120
        String<65> remark;            //0x138
        PAD(3);
        // 0x17C
    };
    #pragma pack(pop)

    static_assert(sizeof(CGuildCreate) == 0x17C);
}
