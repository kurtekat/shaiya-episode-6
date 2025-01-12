#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/QuestTypes.h>

namespace shaiya
{
    static unsigned g_QuestData = 0x4093300;

    #pragma pack(push, 1)
    struct QuestItem
    {
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct QuestResult_EP5
    {
        UINT16 needMobId;     //0x00
        UINT8 needMobCount;   //0x02
        UINT8 needItemId;     //0x03
        UINT8 needItemCount;  //0x04
        PAD(3);
        UINT32 needTime;      //0x08
        UINT16 needHg;        //0x0C
        INT16 needVg;         //0x0E
        UINT8 needOg;         //0x10
        PAD(3);
        UINT32 exp;           //0x14
        UINT32 gold;          //0x18
        UINT8 type;           //0x1C
        UINT8 typeId;         //0x1D
        UINT16 nextQuestId;   //0x1E
        // 0x20
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct QuestInfo_EP5
    {
        UINT16 questId;            //0x00
        QuestName questName;       //0x02
        // summary (ignored)
        PAD(224);                  //0x22
        UINT16 minLevel;           //0x102
        UINT16 maxLevel;           //0x104
        Country country;           //0x106
        Grow grow;                 //0x107
        bool male;                 //0x108
        bool female;               //0x109
        bool fighter;              //0x10A
        bool defender;             //0x10B
        bool ranger;               //0x10C
        bool archer;               //0x10D
        bool mage;                 //0x10E
        bool priest;               //0x10F
        UINT16 hg;                 //0x110
        INT16 vg;                  //0x112
        UINT8 cg;                  //0x114
        UINT8 og;                  //0x115
        UINT8 ig;                  //0x116
        PAD(1);
        UINT16 prevQuestId;        //0x118
        bool requireParty;         //0x11A
        bool partyFighter;         //0x11B
        bool partyDefender;        //0x11C
        bool partyRanger;          //0x11D
        bool partyArcher;          //0x11E
        bool partyMage;            //0x11F
        bool partyPriest;          //0x120
        PAD(3);
        UINT32 minimumTime;        //0x124
        UINT32 time;               //0x128
        UINT32 tickStartTerm;      //0x12C
        UINT32 tickKeepTime;       //0x130
        UINT32 tickReceiveCount;   //0x134
        UINT8 startType;           //0x138
        UINT8 startNpcType;        //0x139
        UINT16 startNpcTypeId;     //0x13A
        UINT8 startItemType;       //0x13C
        UINT8 startItemTypeId;     //0x13D
        // 0x13E
        Array<QuestItem, 3> requiredItems;
        UINT8 endType;             //0x147
        UINT8 endNpcType;          //0x148
        PAD(1);
        UINT16 endNpcTypeId;       //0x14A
        // 0x14C
        Array<QuestItem, 3> farmItems;
        UINT8 pvpKillCount;        //0x155
        UINT16 requiredMobId1;     //0x156
        UINT16 requiredMobId2;     //0x158
        UINT8 requiredMobCount1;   //0x15A
        UINT8 requiredMobCount2;   //0x15B
        UINT8 resultType;          //0x15C
        UINT8 resultUserSelect;    //0x15D
        PAD(2);
        // 0x160
        Array<QuestResult_EP5, 3> results;
        // 0x1C0
        PAD(16);
        // 0x1D0
    };
    #pragma pack(pop)

    static_assert(sizeof(QuestInfo_EP5) == 0x1D0);

    #pragma pack(push, 1)
    struct QuestResult_EP6
    {
        UINT16 needMobId;     //0x00
        UINT8 needMobCount;   //0x02
        UINT8 needItemId;     //0x03
        UINT8 needItemCount;  //0x04
        PAD(3);
        UINT32 needTime;      //0x08
        UINT16 needHg;        //0x0C
        INT16 needVg;         //0x0E
        UINT8 needOg;         //0x10
        PAD(3);
        UINT32 exp;           //0x14
        UINT32 gold;          //0x18
        // 0x1C
        Array<QuestItem, 3> items;
        // 0x25
        PAD(3);
        UINT16 nextQuestId;   //0x28
        PAD(2);
        // 0x2C
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct QuestInfo_EP6
    {
        UINT16 questId;            //0x00
        QuestName questName;       //0x02
        // summary (ignored)
        PAD(224);                  //0x22
        UINT16 minLevel;           //0x102
        UINT16 maxLevel;           //0x104
        Country country;           //0x106
        Grow grow;                 //0x107
        bool male;                 //0x108
        bool female;               //0x109
        bool fighter;              //0x10A
        bool defender;             //0x10B
        bool ranger;               //0x10C
        bool archer;               //0x10D
        bool mage;                 //0x10E
        bool priest;               //0x10F
        UINT16 hg;                 //0x110
        INT16 vg;                  //0x112
        UINT8 cg;                  //0x114
        UINT8 og;                  //0x115
        UINT8 ig;                  //0x116
        PAD(1);
        UINT16 prevQuestId;        //0x118
        bool requireParty;         //0x11A
        bool partyFighter;         //0x11B
        bool partyDefender;        //0x11C
        bool partyRanger;          //0x11D
        bool partyArcher;          //0x11E
        bool partyMage;            //0x11F
        bool partyPriest;          //0x120
        PAD(3);
        UINT32 minimumTime;        //0x124
        UINT32 time;               //0x128
        UINT32 tickStartTerm;      //0x12C
        UINT32 tickKeepTime;       //0x130
        UINT32 tickReceiveCount;   //0x134
        UINT8 startType;           //0x138
        UINT8 startNpcType;        //0x139
        UINT16 startNpcTypeId;     //0x13A
        UINT8 startItemType;       //0x13C
        UINT8 startItemTypeId;     //0x13D
        // 0x13E
        Array<QuestItem, 3> requiredItems;
        UINT8 endType;             //0x147
        UINT8 endNpcType;          //0x148
        PAD(1);
        UINT16 endNpcTypeId;       //0x14A
        // 0x14C
        Array<QuestItem, 3> farmItems;
        UINT8 pvpKillCount;        //0x155
        UINT16 requiredMobId1;     //0x156
        UINT16 requiredMobId2;     //0x158
        UINT8 requiredMobCount1;   //0x15A
        UINT8 requiredMobCount2;   //0x15B
        UINT8 resultType;          //0x15C
        UINT8 resultUserSelect;    //0x15D
        PAD(2);
        // 0x160
        Array<QuestResult_EP6, 6> results;
        // 0x268
        PAD(28);
        // 0x284
    };
    #pragma pack(pop)

    static_assert(sizeof(QuestInfo_EP6) == 0x284);
    using QuestInfo = QuestInfo_EP6;

    struct CQuestData
    {
        static QuestInfo* GetQuest(int questId/*eax*/);
    };
}
