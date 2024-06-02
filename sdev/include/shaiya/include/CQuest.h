#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SNode.h>

namespace shaiya
{
    struct QuestInfo;

    #pragma pack(push, 1)
    struct CQuest
    {
        SNode node;            //0x00
        UINT32 id;             //0x08
        UINT8 bySuccess;       //0x0C
        PAD(3);
        DWORD makeTime;        //0x10
        DWORD delay;           //0x14
        DWORD keepTime;        //0x18
        UINT8 count1;          //0x1C
        UINT8 count2;          //0x1D
        UINT8 count3;          //0x1E
        PAD(1);
        QuestInfo* questInfo;  //0x20
        // 0x24
    };
    #pragma pack(pop)
}
