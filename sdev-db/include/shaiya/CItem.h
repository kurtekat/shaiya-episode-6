#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>
#include <shaiya/include/common/MakeType.h>
#include "SaveType.h"
#include "SNode.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct CItem : SNode
    {
        SaveType saveType;    //0x08
        PAD(4);
        uint64_t uniqueId;    //0x10
        uint32_t itemId;      //0x18
        uint8_t type;         //0x1C
        uint8_t typeId;       //0x1D
        uint8_t count;        //0x1E
        PAD(1);
        uint16_t quality;     //0x20
        Gems gems;            //0x22
        CraftName craftName;  //0x28
        PAD(3);
        time32_t makeTime;    //0x40
        MakeType makeType;    //0x44
        PAD(3);
        // 0x48
    };
    #pragma pack(pop)

    static_assert(sizeof(CItem) == 0x48);
}
