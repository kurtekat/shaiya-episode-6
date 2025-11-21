#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/ItemList.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>
#include "BaseItem.h"
#include "BillingItemInfo.h"
#include "BlockInfo.h"
#include "CCharacterList.h"
#include "ConcernMarket.h"
#include "CPointItem.h"
#include "CQuick.h"
#include "CSkill.h"
#include "DeleteFriend.h"
#include "DeleteItem.h"
#include "DeleteQuest.h"
#include "FriendInfo.h"
#include "PointItemGift.h"
#include "PointLog.h"
#include "SavePoint.h"
#include "SDBDispatchClient.h"
#include "SNode.h"
#include "SSyncList.h"
#include "StatResetBackup.h"

namespace shaiya
{
    struct CItem;
    struct CQuest;
    struct CSkill;
    struct SConnection;

    using CharacterList = Array<CCharacterList, 5>;
    using Inventory = Array<Array<CItem*, 24>, 6>;
    using Warehouse = Array<CItem*, 240>;
    using ProductLog = Array<PointLog, 10>;
    using StoredPointItems = Array<CPointItem*, 240>;
    using Bank = Array<BillingItemInfo, 240>;

    enum struct UserWhere : int32_t
    {
        Default,
        WorldLeave,
        WorldEnter
    };

    #pragma pack(push, 1)
    struct CUser : SDBDispatchClient, SNode
    {
        uint32_t billingId;                   //0x38
        int32_t serverId;                     //0x3C
        String<32> username;                  //0x40
        uint32_t charId;                      //0x60
        uint8_t slot;                         //0x64
        Country country;                      //0x65
        Grow maxGrow;                         //0x66
        Family family;                        //0x67
        Grow grow;                            //0x68
        uint8_t hair;                         //0x69
        uint8_t face;                         //0x6A
        uint8_t size;                         //0x6B
        Job job;                              //0x6C
        Sex sex;                              //0x6D
        uint16_t level;                       //0x6E
        uint16_t statusPoints;                //0x70
        uint16_t skillPoints;                 //0x72
        uint32_t exp;                         //0x74
        uint32_t money;                       //0x78
        uint32_t bankMoney;                   //0x7C
        uint32_t kills;                       //0x80
        uint32_t deaths;                      //0x84
        uint32_t wins;                        //0x88
        uint32_t losses;                      //0x8C
        uint32_t killLv;                      //0x90
        uint32_t deathLv;                     //0x94
        uint16_t mapId;                       //0x98
        uint16_t direction;                   //0x9A
        float posX;                           //0x9C
        float posY;                           //0xA0
        float posZ;                           //0xA4
        uint16_t honor;                       //0xA8
        int16_t vg;                           //0xAA
        uint8_t cg;                           //0xAC
        uint8_t og;                           //0xAD
        uint8_t ig;                           //0xAE
        PAD(1);
        uint16_t strength;                    //0xB0
        uint16_t dexterity;                   //0xB2
        uint16_t intelligence;                //0xB4
        uint16_t wisdom;                      //0xB6
        uint16_t reaction;                    //0xB8
        uint16_t luck;                        //0xBA
        uint16_t health;                      //0xBC
        uint16_t mana;                        //0xBE
        uint16_t stamina;                     //0xC0
        PAD(2);
        // 259200000
        tick32_t nextGuildJoinTime;           //0xC4
        String<21> charName;                  //0xC8
        PAD(3);
        Inventory inventory;                  //0xE0
        Warehouse warehouse;                  //0x320
        Bank bank;                            //0x6E0
        SSyncList<CSkill> applySkills;        //0x33E0
        int32_t skillCount;                   //0x340C
        Array<CSkill*, 256> skills;           //0x3410
        int32_t quickSlotCount;               //0x3810
        Array<CQuick, 128> quickSlots;        //0x3814
        SSyncList<CQuest> quests;             //0x3B14
        SSyncList<CQuest> completedQuests;    //0x3B40
        CharacterList characterList;          //0x3B6C
        int32_t baseItemCount;                //0x3D38
        PAD(4);
        Array<BaseItem, 10> baseItems;        //0x3D40
        Array<FriendInfo, 100> friends;       //0x4060
        Array<BlockInfo, 100> blocks;         //0x6130
        StatResetBackup statResetBackup;      //0x8070
        PAD(2);
        time32_t charExitTime;                //0x8084
        int32_t charRenameSlot;               //0x8088
        String<21> newCharName;               //0x808C
        // 0x80A1
        PAD(3);
        Array<SavePoint, 4> savePoints;       //0x80A4
        uint32_t points;                      //0x80F4
        ProductLog productLog;                //0x80F8
        PointItemGift pointItemGift;          //0x8260
        StoredPointItems storedPointItems;    //0x8298
        uint32_t purchaseTargetId;            //0x8658
        uint32_t purchaseNumber;              //0x865C
        uint32_t autoConnectWar;              //0x8660
        uint32_t guildId;                     //0x8664
        ConcernMarket concernMarket;          //0x8668
        bool appearanceChange;                //0x86B0
        bool skillReset;                      //0x86B1
        PAD(2);
        int32_t dbSkillCount;                     //0x86B4
        SSyncList<DeleteItem> deleteItems;        //0x86B8
        SSyncList<DeleteItem> deleteStoredItems;  //0x86E4
        SSyncList<DeleteQuest> deleteQuests;      //0x8710
        SSyncList<DeleteFriend> deleteFriends;    //0x873C
        SSyncList<DeleteFriend> deleteBlocks;     //0x8768
        PAD(28); // pointItems (std::list)        //0x8794
        CRITICAL_SECTION csPointItems;            //0x87B0
        volatile unsigned pointsLock;             //0x87C8
        SSyncList<DeleteFriend> pointUpdates;     //0x87CC
        SConnection* connection;              //0x87F8
        CRITICAL_SECTION csUser;              //0x87FC
        UserWhere where;                      //0x8814
        bool saveCountry;                     //0x8818
        PAD(3);
        // 900000
        tick32_t nextDBSaveTime;              //0x881C
        PAD(4);
        CRITICAL_SECTION csItems;             //0x8824
        CRITICAL_SECTION csSkills;            //0x883C
        PAD(4);
        // 0x8858

        // custom
        Array<ItemList<17>, 5> equipment;     //0x8858
    };
    #pragma pack(pop)

    //static_assert(sizeof(CUser) == 0x8858);
    static_assert(sizeof(CUser) == 0x8902);
}
