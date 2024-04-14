#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CDataFile
    {
        enum struct Attribute : UINT8
        {
            None,
            Fire1,
            Water1,
            Earth1,
            Wind1,
            Fire2,
            Water2,
            Earth2,
            Wind2
        };

        enum struct Country : UINT8
        {
            Human,
            Elf,
            Light,
            DeathEater,
            Vail,
            Fury,
            Neutral
        };

        enum struct Grow : UINT8
        {
            Easy,
            Normal,
            Hard,
            Ultimate
        };

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
            Country country;        //0x0E
            bool attackFighter;     //0x0F
            bool defenseFighter;    //0x10
            bool patrolRogue;       //0x11
            bool shootRogue;        //0x12
            bool attackMage;        //0x13
            bool defenseMage;       //0x14
            Grow grow;              //0x15
            UINT16 reqStr;          //0x16
            UINT16 reqDex;          //0x18
            UINT16 reqRec;          //0x1A
            UINT16 reqInt;          //0x1C
            UINT16 reqWis;          //0x1E
            INT32 reqLuc;           //0x20
            INT16 reqVg;            //0x24
            UINT8 reqOg;            //0x26
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
            PAD(54);
            UINT8 vehicleModel;     //0x90
            PAD(3);
            UINT8 vehicleSeats;     //0x94
            PAD(3);
            UINT32 vehicleSpeed;    //0x98
            bool isSnowboard;       //0x9C
            PAD(15);
            // 0xAC
        };

        struct SkillInfo
        {
            UINT16 skillId;  //0x00
            UINT8 skillLv;   //0x02
            PAD(15);
            UINT16 level;    //0x12
            PAD(38);
            UINT8 range;     //0x3A
            PAD(23);
            UINT32 damage;   //0x52
            PAD(298);
            // 0x180
        };

        struct MobInfo
        {
            char* name;           //0x00
            UINT16 model;         //0x04
            UINT16 level;         //0x06
            UINT32 ai;            //0x08
            UINT32 health;        //0x0C
            // not wings
            UINT8 height;         //0x10
            UINT8 radius;         //0x11
            Attribute attribute;  //0x12
            PAD(1);
            UINT32 delay;         //0x14
            UINT8 range;          //0x18
            PAD(3);
            UINT32 chaseDelay;    //0x1C
            UINT8 chaseRange;     //0x20
            PAD(28);
            BOOL isWings;         //0x40
            // 0x44
        };

        static ItemInfo* GetItemInfo(int type, int typeId);
        static MobInfo* GetMobInfo(int mobId);
        static SkillInfo* GetSkillInfo(int skillId, int skillLv);
    };
    #pragma pack(pop)
}
