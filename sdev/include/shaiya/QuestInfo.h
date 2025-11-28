#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/NpcTypes.h>
#include "QuestResult.h"

namespace shaiya
{
    inline constexpr int QuestResultCount_EP5 = 3;
    inline constexpr int QuestResultCount_EP6 = 6;

    #pragma pack(push, 1)
    struct QuestInfo_EP5
    {
        uint16_t questId;            //0x00
        String<256> questName;       //0x02
        uint16_t minLevel;           //0x102
        uint16_t maxLevel;           //0x104
        Country country;             //0x106
        Grow grow;                   //0x107
        bool male;                   //0x108
        bool female;                 //0x109
        bool fighter;                //0x10A
        bool defender;               //0x10B
        bool ranger;                 //0x10C
        bool archer;                 //0x10D
        bool mage;                   //0x10E
        bool priest;                 //0x10F
        uint16_t hg;                 //0x110
        int16_t vg;                  //0x112
        uint8_t cg;                  //0x114
        uint8_t og;                  //0x115
        uint8_t ig;                  //0x116
        PAD(1);
        uint16_t prevQuestId;        //0x118
        bool party;                  //0x11A
        bool partyFighter;           //0x11B
        bool partyDefender;          //0x11C
        bool partyRanger;            //0x11D
        bool partyArcher;            //0x11E
        bool partyMage;              //0x11F
        bool partyPriest;            //0x120
        PAD(3);
        tick32_t minimumTime;        //0x124
        tick32_t time;               //0x128
        tick32_t startTime;          //0x12C
        tick32_t keepTime;           //0x130
        tick32_t recvTime;           //0x134
        uint8_t startType;           //0x138
        uint8_t startNpcType;        //0x139
        uint16_t startNpcTypeId;     //0x13A
        uint8_t startItemType;       //0x13C
        uint8_t startItemTypeId;     //0x13D
        uint8_t getItemType1;        //0x13E
        uint8_t getItemTypeId1;      //0x13F
        uint8_t getItemCount1;       //0x140
        uint8_t getItemType2;        //0x141
        uint8_t getItemTypeId2;      //0x142
        uint8_t getItemCount2;       //0x143
        uint8_t getItemType3;        //0x144
        uint8_t getItemTypeId3;      //0x145
        uint8_t getItemCount3;       //0x146
        uint8_t endType;             //0x147
        uint8_t endNpcType;          //0x148
        PAD(1);
        uint16_t endNpcTypeId;       //0x14A
        uint8_t endItemType1;        //0x14C
        uint8_t endItemTypeId1;      //0x14D
        uint8_t endItemCount1;       //0x14E
        uint8_t endItemType2;        //0x14F
        uint8_t endItemTypeId2;      //0x150
        uint8_t endItemCount2;       //0x151
        uint8_t endItemType3;        //0x152
        uint8_t endItemTypeId3;      //0x153
        uint8_t endItemCount3;       //0x154
        uint8_t pvpKillCount;        //0x155
        uint16_t needMobId1;         //0x156
        uint16_t needMobId2;         //0x158
        uint8_t needMobCount1;       //0x15A
        uint8_t needMobCount2;       //0x15B
        uint8_t resultType;          //0x15C
        uint8_t resultUserSelect;    //0x15D
        PAD(2);
        // 0x160
        Array<QuestResult_EP5, 3> results;
        tick32_t nextQuestStartTime; //0x1C0
        tick32_t questEndTime;       //0x1C4
        tick32_t questRemainTime;    //0x1C8
        bool enableQuest;            //0x1CC
        PAD(3);
        // 0x1D0
    };
    #pragma pack(pop)

    static_assert(sizeof(QuestInfo_EP5) == 0x1D0);

    #pragma pack(push, 1)
    struct QuestInfo
    {
        uint16_t questId;            //0x00
        String<256> questName;       //0x02
        uint16_t minLevel;           //0x102
        uint16_t maxLevel;           //0x104
        Country country;             //0x106
        Grow grow;                   //0x107
        bool male;                   //0x108
        bool female;                 //0x109
        bool fighter;                //0x10A
        bool defender;               //0x10B
        bool ranger;                 //0x10C
        bool archer;                 //0x10D
        bool mage;                   //0x10E
        bool priest;                 //0x10F
        uint16_t hg;                 //0x110
        int16_t vg;                  //0x112
        uint8_t cg;                  //0x114
        uint8_t og;                  //0x115
        uint8_t ig;                  //0x116
        PAD(1);
        uint16_t prevQuestId;        //0x118
        bool party;                  //0x11A
        bool partyFighter;           //0x11B
        bool partyDefender;          //0x11C
        bool partyRanger;            //0x11D
        bool partyArcher;            //0x11E
        bool partyMage;              //0x11F
        bool partyPriest;            //0x120
        PAD(3);
        tick32_t minimumTime;        //0x124
        tick32_t time;               //0x128
        tick32_t startTime;          //0x12C
        tick32_t keepTime;           //0x130
        tick32_t recvTime;           //0x134
        uint8_t startType;           //0x138
        uint8_t startNpcType;        //0x139
        uint16_t startNpcTypeId;     //0x13A
        uint8_t startItemType;       //0x13C
        uint8_t startItemTypeId;     //0x13D
        uint8_t getItemType1;        //0x13E
        uint8_t getItemTypeId1;      //0x13F
        uint8_t getItemCount1;       //0x140
        uint8_t getItemType2;        //0x141
        uint8_t getItemTypeId2;      //0x142
        uint8_t getItemCount2;       //0x143
        uint8_t getItemType3;        //0x144
        uint8_t getItemTypeId3;      //0x145
        uint8_t getItemCount3;       //0x146
        uint8_t endType;             //0x147
        uint8_t endNpcType;          //0x148
        PAD(1);
        uint16_t endNpcTypeId;       //0x14A
        uint8_t endItemType1;        //0x14C
        uint8_t endItemTypeId1;      //0x14D
        uint8_t endItemCount1;       //0x14E
        uint8_t endItemType2;        //0x14F
        uint8_t endItemTypeId2;      //0x150
        uint8_t endItemCount2;       //0x151
        uint8_t endItemType3;        //0x152
        uint8_t endItemTypeId3;      //0x153
        uint8_t endItemCount3;       //0x154
        uint8_t pvpKillCount;        //0x155
        uint16_t requiredMobId1;     //0x156
        uint16_t requiredMobId2;     //0x158
        uint8_t requiredMobCount1;   //0x15A
        uint8_t requiredMobCount2;   //0x15B
        uint8_t resultType;          //0x15C
        uint8_t resultUserSelect;    //0x15D
        PAD(2);
        // 0x160
        Array<QuestResult_EP6, 6> results;
        // 0x268
        PAD(28);
        // 0x284
    };
    #pragma pack(pop)

    static_assert(sizeof(QuestInfo) == 0x284);
}
