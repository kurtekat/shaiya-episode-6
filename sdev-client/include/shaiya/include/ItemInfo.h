#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    enum struct ItemCountry : UINT8
    {
        Human,
        Elf,
        Light,
        DeathEater,
        Vail,
        Fury,
        Neutral
    };

    enum struct ItemExtDuration : UINT8
    {
        None,
        Unexpandable,
        Expandable
    };

    enum struct ItemReqOg : UINT8
    {
        Tradable,
        AccountBound,
        CharacterBound
    };

    #pragma pack(push, 1)
    struct ItemInfo
    {
        char* name;             //0x00
        char* desc;             //0x04
        UINT8 type;             //0x08
        UINT8 typeId;           //0x09
        UINT8 model;            //0x0A
        UINT8 icon;             //0x0B
        UINT8 level;            //0x0C
        PAD(1);
        ItemCountry country;    //0x0E
        ReqJob job;             //0x0F
        Grow grow;              //0x15
        UINT16 reqStr;          //0x16
        UINT16 reqDex;          //0x18
        UINT16 reqRec;          //0x1A
        UINT16 reqInt;          //0x1C
        UINT16 reqWis;          //0x1E
        INT32 reqLuc;           //0x20
        INT16 reqVg;            //0x24
        ItemReqOg reqOg;        //0x26
        UINT8 reqIg;            //0x27
        UINT16 range;           //0x28
        UINT8 attackTime;       //0x2A
        Attribute attribute;    //0x2B
        UINT8 special;          //0x2C
        UINT8 slotCount;        //0x2D
        UINT16 quality;         //0x2E
        UINT16 effect1;         //0x30
        UINT16 effect2;         //0x32
        UINT16 effect3;         //0x34
        UINT16 effect4;         //0x36
        PAD(20);
        UINT32 buy;             //0x4C
        UINT32 sell;            //0x50
        UINT32 dropGrade;       //0x54
        UINT8 composeCount;     //0x58
        UINT8 count;            //0x59
        PAD(2);
        UINT32 duration;        //0x5C
        // 0x60
        ItemExtDuration extDuration;
        PAD(47);
        UINT8 vehicleModel;     //0x90
        PAD(3);
        UINT8 vehicleSeats;     //0x94
        PAD(3);
        UINT32 vehicleSpeed;    //0x98
        bool isSnowboard;       //0x9C
        PAD(15);
        // 0xAC
    };
    #pragma pack(pop)
}
