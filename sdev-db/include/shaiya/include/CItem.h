#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>
#include <shaiya/include/common/MakeType.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CItem
    {
        PAD(16);
        UINT64 uniqueId;      //0x10
        UINT32 itemId;        //0x18
        UINT8 type;           //0x1C
        UINT8 typeId;         //0x1D
        UINT8 count;          //0x1E
        PAD(1);
        UINT16 quality;       //0x20
        Gems gems;            //0x22
        CraftName craftName;  //0x28
        PAD(3);
        ULONG makeTime;       //0x40
        MakeType makeType;    //0x44
        PAD(3);
        // 0x48
    };
    #pragma pack(pop)

    static_assert(sizeof(CItem) == 0x48);
}
