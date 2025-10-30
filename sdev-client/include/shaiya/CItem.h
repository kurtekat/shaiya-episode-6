#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CItem
    {
        uint8_t slots;        //0x00
        uint8_t type;         //0x01
        uint8_t typeId;       //0x02
        uint8_t count;        //0x03
        uint16_t quality;     //0x04
        Gems gems;            //0x06
        CraftName craftName;  //0x0C
        PAD(3);
        bool32_t isBagToBag;  //0x24
        time32_t fromDate;    //0x28
        time32_t toDate;      //0x2C
        uint32_t unknown;     //0x30
        // 0x34
    };
    #pragma pack(pop)

    static_assert(sizeof(CItem) == 0x34);
}
