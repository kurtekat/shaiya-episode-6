#pragma once
#include <shaiya/include/common.h>
#include "QuestItem.h"

namespace shaiya
{
    #pragma pack(push, 1)
    struct QuestResult_EP5
    {
        uint16_t needMobId;     //0x00
        uint8_t needMobCount;   //0x02
        uint8_t needItemId;     //0x03
        uint8_t needItemCount;  //0x04
        PAD(3);
        uint32_t needTime;      //0x08
        uint16_t needHg;        //0x0C
        int16_t needVg;         //0x0E
        uint8_t needOg;         //0x10
        PAD(3);
        uint32_t exp;           //0x14
        uint32_t money;         //0x18
        uint8_t itemType;       //0x1C
        uint8_t itemTypeId;     //0x1D
        uint16_t nextQuestId;   //0x1E
        // 0x20
    };
    #pragma pack(pop)

    static_assert(sizeof(QuestResult_EP5) == 0x20);

    #pragma pack(push, 1)
    struct QuestResult_EP6
    {
        uint16_t needMobId;     //0x00
        uint8_t needMobCount;   //0x02
        uint8_t needItemId;     //0x03
        uint8_t needItemCount;  //0x04
        PAD(3);
        uint32_t needTime;      //0x08
        uint16_t needHg;        //0x0C
        int16_t needVg;         //0x0E
        uint8_t needOg;         //0x10
        PAD(3);
        uint32_t exp;           //0x14
        uint32_t money;         //0x18
        // 0x1C
        Array<QuestItem, 3> itemList;
        // 0x25
        PAD(3);
        uint16_t nextQuestId;   //0x28
        PAD(2);
        // 0x2C
    };
    #pragma pack(pop)

    static_assert(sizeof(QuestResult_EP6) == 0x2C);
}
