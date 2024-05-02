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
    #pragma pack(pop)

#ifdef SHAIYA_EP6
    #pragma pack(push, 1)
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
    #pragma pack(pop)
#else
    #pragma pack(push, 1)
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
    #pragma pack(pop)
#endif

    #pragma pack(push, 1)
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
        ReqJob job;             //0x10A
        UINT16 hg;              //0x110
        INT16 vg;               //0x112
        UINT8 cg;               //0x114
        UINT8 og;               //0x115
        UINT8 ig;               //0x116
        PAD(1);
        UINT16 prevQuestId;     //0x118
        bool partyRequired;     //0x11A
        ReqJob partyJob;        //0x11B
        PAD(3);
        UINT32 minimumTime;     //0x124
        UINT32 delay;           //0x128
        PAD(8);
        BOOL repeatable;        //0x134
        UINT8 startType;        //0x138
        UINT8 startNpcType;     //0x139
        UINT16 startNpcTypeId;  //0x13A
        UINT8 startItemType;    //0x13C
        UINT8 startItemTypeId;  //0x13D
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
#ifdef SHAIYA_EP6
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
    #pragma pack(pop)

    struct CQuestData
    {
        static QuestInfo* GetQuest(int questId/*eax*/);
    };
}
