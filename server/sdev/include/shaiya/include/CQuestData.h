#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    static Address g_QuestData = 0x4093300;

    typedef Array<char, 256> QuestName;

    #pragma pack(push, 1)
    struct QuestItem
    {
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
    };

    #ifdef SHAIYA_EP6_QUEST_RESULT
    struct QuestResult
    {
        UINT16 mobId;        //0x00
        UINT8 minMobCount;   //0x02
        PAD(1);
        UINT8 minItemCount;  //0x04
        PAD(15);
        UINT32 exp;          //0x14
        UINT32 gold;         //0x18
        // 0x1C
        Array<QuestItem, 3> item;
        PAD(1);
        UINT16 nextQuestId;  //0x26
        PAD(4);
        // 0x2C = size
    };
    #else
    struct QuestResult
    {
        UINT16 mobId;        //0x00
        UINT8 minMobCount;   //0x02
        PAD(1);
        UINT8 minItemCount;  //0x04
        PAD(15);
        UINT32 exp;          //0x14
        UINT32 gold;         //0x18
        UINT8 type;          //0x1C
        UINT8 typeId;        //0x1D
        UINT16 nextQuestId;  //0x1E
        // 0x20 = size
    };
    #endif

    struct QuestInfo
    {
        UINT16 questId;         //0x00
        QuestName questName;    //0x02
        UINT16 minLevel;        //0x102
        UINT16 maxLevel;        //0x104
        Country country;        //0x106
        Grow grow;              //0x107
        bool male;              //0x108
        bool female;            //0x109
        bool attackFighter;     //0x10A
        bool defenseFighter;    //0x10B
        bool patrolRogue;       //0x10C
        bool shootRogue;        //0x10D
        bool attackMage;        //0x10E
        bool defenseMage;       //0x10F
        PAD(8);
        UINT16 prevQuestId;     //0x118
        PAD(14);
        UINT32 timeLimit;       //0x128
        PAD(8);
        BOOL repeatable;        //0x134
        UINT8 startType;        //0x138
        UINT8 startNpcType;     //0x139
        UINT16 startNpcTypeId;  //0x13A
        PAD(2);
        // 0x13E
        Array<QuestItem, 3> reqItem;
        UINT8 endType;          //0x147
        UINT8 endNpcType;       //0x148
        PAD(1);
        UINT16 endNpcTypeId;    //0x14A
        // 0x14C
        Array<QuestItem, 3> farmItem;
        UINT8 pvpKillCount;     //0x155
        UINT16 reqMobId1;       //0x156
        UINT16 reqMobId2;       //0x158
        UINT8 reqMobCount1;     //0x15A
        UINT8 reqMobCount2;     //0x15B
        PAD(4);
        #ifdef SHAIYA_EP6_QUEST_RESULT
        // 0x160
        Array<QuestResult, 6> result;
        // 0x268
        PAD(28);
        // 0x284 = size
        #else
        // 0x160
        Array<QuestResult, 3> result;
        // 0x1C0
        PAD(16);
        // 0x1D0 = size
        #endif
    };

    struct CQuestData
    {
        static QuestInfo* GetQuest(int questId/*eax*/);
    };
    #pragma pack(pop)
}
