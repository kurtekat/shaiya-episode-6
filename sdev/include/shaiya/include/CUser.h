#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/AuthStatus.h>
#include <shaiya/include/common/BillingItem.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>
#include <shaiya/include/common/ShapeType.h>
#include <shaiya/include/SConnection.h>
#include <shaiya/include/SNode.h>
#include <shaiya/include/SSyncList.h>
#include "include/shaiya/include/CExchange.h"
#include "include/shaiya/include/CFriend.h"
#include "include/shaiya/include/CloneUser.h"
#include "include/shaiya/include/CMiniGame.h"
#include "include/shaiya/include/CUserCrypto.h"
#include "include/shaiya/include/MyShop.h"
#include "include/shaiya/include/SVector.h"
#include "include/shaiya/include/TownMoveScroll.h"

namespace shaiya
{
    struct CDamage;
    struct CGuild;
    struct CGuildCreate;
    struct CItem;
    struct CQuest;
    struct CParty;
    struct CSkill;
    struct CZone;
    struct ItemInfo;
    struct SkillInfo;

    using Inventory = Array<Array<CItem*, 24>, 6>;
    using Warehouse = Array<CItem*, 240>;

    using ItemQualityLv = Array<UINT8, 13>;
    using ItemQuality = Array<UINT16, 13>;

    using ItemQualityLvEx = Array<UINT8, 24>;
    using ItemQualityEx = Array<UINT16, 24>;

    using Bank = Array<BillingItem, 240>;

    #pragma pack(push, 1)
    struct ProductItem
    {
        CharArray<21> productCode;  //0x00
        PAD(3);
        ULONG purchaseDate;         //0x18
        UINT32 itemPrice;           //0x1C
        // 0x20
    };
    #pragma pack(pop)

    using ProductLog = Array<ProductItem, 10>;

    #pragma pack(push, 1)
    struct SkillAbility70
    {
        UINT16 skillId;
        UINT8 skillLv;
        bool triggered;
        DWORD keepTick;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct SkillAbilityEx
    {
        SkillAbility70 type70;
        UINT32 increaseQuestExpRate;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct StoredPointItems
    {
        // uses 240
        Array<BillingItem, 640> items;
        CRITICAL_SECTION cs;
    };
    #pragma pack(pop)

    enum struct UserAttackType : UINT32
    {
        None,
        Basic,
        Skill
    };

    enum struct UserAttribute : UINT32
    {
        None,
        Fire,
        Water,
        Earth,
        Wind,
        Fire2,
        Water2,
        Earth2,
        Wind2
    };

    enum struct UserCharmType : UINT32
    {
        None,
        WhiteTiger,
        BlueDragon,
        RedPhoenix
    };

    enum struct UserHealthAssistType : UINT32
    {
        Sp,
        Mp,
        SpMp
    };

    enum struct UserLogoutType : UINT32
    {
        None,
        CharacterScreen,
        Exit
    };

    enum struct UserPartyType : UINT8
    {
        None,
        Member,
        Leader
    };

    enum struct UserPvPStatus : UINT32
    {
        None,
        RequestSent,
        RequestReceived,
        Countdown,
        Start,
        Exchange
    };

    enum struct UserRecallType : UINT32
    {
        Default,
        GateKeeper = 1,
        Portal = 1,
        SavePoint,
        RecallRune,
        PartyMemberSummon,
        PartyMemberMoveTo,
        // itemId 100169 (EP5)
        MoveWar,
        // custom
        TownMoveScroll,
        MoveMapId200 = 10,
        MoveChar = 0xF904,
        MoveCharZone = 0xF905,
        MoveParty = 0xF90C,
        MoveTo = 0xFA09,
        MoveZone = 0xFA0A,
        MoveMap = 0xFA11,
        MoveInsZone = 0xFA12
    };

    enum struct UserRecallItemType : UINT32
    {
        None,
        SavePoint1,
        SavePoint2,
        SavePoint3,
        SavePoint4,
        PartyMemberSummon = 100,
        PartyMemberMoveTo = 101,
        // itemId 100169 (EP5)
        MoveWar = 254,
        RecallRune = 255
    };

    enum struct UserRecoveryType : UINT32
    {
        Sit,
        Normal,
        Combat
    };

    enum struct UserStatus : UINT32
    {
        None,
        Death,
        Combat
    };

    enum struct UserTargetType : UINT32
    {
        None,
        User,
        Mob
    };

    enum struct UserVehicleStatus : UINT32
    {
        None,
        Summon,
        Riding
    };

    enum struct UserWhere : UINT32
    {
        Default,
        WorldLeave,
        ZoneWait,
        ZoneLeave,
        ZoneEnter
    };

    #pragma pack(push, 1)
    struct UserKillCountStatus
    {
        PAD(4);                    //0x14D4
        UINT32 health;             //0x14D8
        UINT32 stamina;            //0x14DC
        UINT32 mana;               //0x14E0
        UINT32 strength;           //0x14E4
        UINT32 recovery;           //0x14E8
        UINT32 intelligence;       //0x14EC
        UINT32 wisdom;             //0x14F0
        UINT32 dexterity;          //0x14F4
        UINT32 luck;               //0x14F8
        UINT32 sitHpRecovery;      //0x14FC
        UINT32 sitSpRecovery;      //0x1500
        UINT32 sitMpRecovery;      //0x1504
        UINT32 combatHpRecovery;   //0x1508
        UINT32 combatSpRecovery;   //0x150C
        UINT32 combatMpRecovery;   //0x1510
        UINT32 criticalHitRate;    //0x1514
        UINT32 hitRate;            //0x1518
        UINT32 defense;            //0x151C
        UINT32 rangedDefense;      //0x1520
        UINT32 magicResistance;    //0x1524
        UINT32 evasionRate;        //0x1528
        UINT32 rangedEvasionRate;  //0x152C
        UINT32 magicEvasionRate;   //0x1530
        PAD(16);
        // 0x70
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserQuickSlot
    {
        UINT8 bag;
        UINT8 slot;
        UINT8 srcBag;
        PAD(1);
        UINT16 srcSlot;
        // 0x06
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserSavePoint
    {
        Array<UINT32, 4> mapId;
        Array<SVector, 4> pos;
        // 0x40
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserWeaponMasterySpeed
    {
        PAD(1);
        UINT8 oneHandedSword;
        UINT8 twoHandedSword;
        UINT8 oneHandedAxe;
        UINT8 twoHandedAxe;
        UINT8 dualWield;
        UINT8 spear;
        UINT8 oneHandedBlunt;
        UINT8 twoHandedBlunt;
        UINT8 reverseDagger;
        UINT8 dagger;
        UINT8 crossbow;
        UINT8 staff;
        UINT8 bow;
        UINT8 javelin;
        UINT8 knuckles;
        PAD(4);
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserWeaponMasteryPower
    {
        PAD(1);
        UINT8 oneHandedSword;
        UINT8 twoHandedSword;
        UINT8 oneHandedAxe;
        UINT8 twoHandedAxe;
        UINT8 dualWield;
        UINT8 spear;
        UINT8 oneHandedBlunt;
        UINT8 twoHandedBlunt;
        UINT8 reverseDagger;
        UINT8 dagger;
        UINT8 crossbow;
        UINT8 staff;
        UINT8 bow;
        UINT8 javelin;
        UINT8 knuckles;
        PAD(4);
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CUser
    {
        SConnection connection;                //0x00
        SVector pos;                           //0xD0
        ULONG id;                              //0xDC
        CZone* zone;                           //0xE0
        UINT32 cellX;                          //0xE4
        UINT32 cellZ;                          //0xE8
        PAD(60);
        ULONG charId;                          //0x128
        UINT8 slot;                            //0x12C
        Country country;                       //0x12D
        Family family;                         //0x12E
        Grow grow;                             //0x12F
        Grow maxGrow;                          //0x130
        UINT8 hair;                            //0x131
        UINT8 face;                            //0x132
        UINT8 size;                            //0x133
        Job job;                               //0x134
        Sex sex;                               //0x135
        UINT16 level;                          //0x136
        UINT16 statPoint;                      //0x138
        UINT16 skillPoint;                     //0x13A
        UINT32 exp;                            //0x13C
        UINT32 money;                          //0x140
        UINT32 bankMoney;                      //0x144
        UINT32 kills;                          //0x148
        UINT32 deaths;                         //0x14C
        UINT32 wins;                           //0x150
        UINT32 losses;                         //0x154
        UINT32 killLv;                         //0x158
        UINT32 deathLv;                        //0x15C
        UINT16 mapId;                          //0x160
        UINT16 direction;                      //0x162
        UINT16 honor;                          //0x164
        INT16 vg;                              //0x166
        UINT8 cg;                              //0x168
        UINT8 og;                              //0x169
        UINT16 ig;                             //0x16A
        UINT16 strength;                       //0x16C
        UINT16 dexterity;                      //0x16E
        UINT16 intelligence;                   //0x170
        UINT16 wisdom;                         //0x172
        UINT16 reaction;                       //0x174
        UINT16 luck;                           //0x176
        UINT32 maxHealth;                      //0x178
        UINT32 maxMana;                        //0x17C
        UINT32 maxStamina;                     //0x180
        CharArray<21> charName;                //0x184
        ItemQualityLv itemQualityLv;           //0x199
        ItemQuality itemQuality;               //0x1A6
        Inventory inventory;                   //0x1C0
        Warehouse warehouse;                   //0x400
        Bank bank;                             //0x7C0
        SSyncList<CSkill> applySkills;         //0xA90
        UINT32 skillCount;                     //0xABC
        Array<CSkill*, 256> skills;            //0xAC0
        UINT32 quickSlotCount;                 //0xEC0
        Array<UserQuickSlot, 128> quickSlots;  //0xEC4
        SSyncList<CQuest> completedQuests;     //0x11C4
        SSyncList<CQuest> quests;              //0x11F0
        UINT32 abilityStrength;                //0x121C
        UINT32 abilityDexterity;               //0x1220
        UINT32 abilityIntelligence;            //0x1224
        UINT32 abilityWisdom;                  //0x1228
        UINT32 abilityReaction;                //0x122C
        UINT32 abilityLuck;                    //0x1230
        UINT32 health;                         //0x1234
        UINT32 mana;                           //0x1238
        UINT32 stamina;                        //0x123C
        UINT32 combatHpRecovery;               //0x1240
        UINT32 combatSpRecovery;               //0x1244
        UINT32 combatMpRecovery;               //0x1248
        UINT32 sitHpRecovery;                  //0x124C
        UINT32 sitSpRecovery;                  //0x1250
        UINT32 sitMpRecovery;                  //0x1254
        UINT32 addHpRecovery;                  //0x1258
        UINT32 addSpRecovery;                  //0x125C
        UINT32 addMpRecovery;                  //0x1260
        UINT32 healthRecovery;                 //0x1264
        UINT32 staminaRecovery;                //0x1268
        UINT32 manaRecovery;                   //0x126C
        UserRecoveryType recoveryType;         //0x1270
        UINT32 decreaseMpCostPercentage;       //0x1274
        UINT32 decreaseSpCostPercentage;       //0x1278
        UserAttribute weaponAttribute;         //0x127C
        UserAttribute armorAttribute;          //0x1280
        PAD(92);
        UINT32 addAttackPower;                 //0x12E0
        UINT32 maxAddAttackPower;              //0x12E4
        UINT32 addDefense;                     //0x12E8
        UINT32 addMagicResistance;             //0x12EC
        UINT32 abilityAttackRange;             //0x12F0
        UINT32 abilityAttackSpeed;             //0x12F4
        UINT32 abilityMoveSpeed;               //0x12F8
        UINT32 abilityCriticalHitRate;         //0x12FC
        UINT32 decreaseSkillResetTime;         //0x1300
        UINT32 abilityAbsorption;              //0x1304
        UINT32 interpretationLv;               //0x1308
        UINT32 bagsUnlocked;                   //0x130C
        UserWeaponMasterySpeed weaponSpeed;    //0x1310
        UserWeaponMasteryPower weaponPower;    //0x1324
        PAD(4);
        UINT32 shieldMasteryDefense;           //0x133C
        UserHealthAssistType hpAssistType;     //0x1340
        BOOL immobilized;                      //0x1344
        BOOL unconscious;                      //0x1348
        BOOL sleeping;                         //0x134C
        BOOL degenerated;                      //0x1350
        UINT16 transformMobId;                 //0x1354
        PAD(2);
        // typeDetail 74, 75 and 76
        UINT32 debuffTypeDetail;               //0x1358
        // typeDetail 70
        ULONG debuffCasterId;                  //0x135C
        ShapeType shapeType;                   //0x1360
        PAD(3);
        UINT32 shapeMobId;                     //0x1364
        CloneUser* clone;                      //0x1368
        BOOL invincible;                       //0x136C
        bool preventDeath;                     //0x1370
        bool preventDying;                     //0x1371
        bool preventAggro;                     //0x1372
        bool danceOfDeath;                     //0x1373
        bool etainShield;                      //0x1374
        PAD(3);
        bool passiveSkillApplied;              //0x1378
        PAD(1);
        UINT16 passiveSkillId;                 //0x137A
        UINT8 passiveSkillLv;                  //0x137C
        PAD(3);
        DWORD passiveSkillUseTick;             //0x1380
        UINT32 abilityHitRate;                 //0x1384
        UINT32 abilityAttackPower;             //0x1388
        UINT32 abilityEvasionRate;             //0x138C
        UINT32 abilityAddDefense;              //0x1390
        UINT32 abilityRangedHitRate;           //0x1394
        UINT32 abilityRangedAttackPower;       //0x1398
        UINT32 abilityRangedEvasionRate;       //0x139C
        UINT32 abilityAddRangedDefense;        //0x13A0
        UINT32 abilityMagicHitRate;            //0x13A4
        UINT32 abilityMagicPower;              //0x13A8
        UINT32 abilityMagicEvasionRate;        //0x13AC
        UINT32 abilityAddMagicResistance;      //0x13B0
        BOOL attackBlinded;                    //0x13B4
        UINT32 evasionStatus;                  //0x13B8
        UINT32 evasionPercentage;              //0x13BC
        UINT32 mirrorSkillId;                  //0x13C0
        UINT32 mirrorSkillLv;                  //0x13C4
        UINT32 hitRate;                        //0x13C8
        UINT32 minAttackPower;                 //0x13CC
        UINT32 evasionRate;                    //0x13D0
        UINT32 defense;                        //0x13D4
        UINT32 criticalHitRate;                //0x13D8
        PAD(4);
        BOOL rangedAttackBlinded;              //0x13E0
        UINT32 rangedEvasionStatus;            //0x13E4
        UINT32 rangedEvasionPercentage;        //0x13E8
        UINT32 rangedMirrorSkillId;            //0x13EC
        UINT32 rangedMirrorSkillLv;            //0x13F0
        UINT32 rangedHitRate;                  //0x13F4
        UINT32 minRangedAttackPower;           //0x13F8
        UINT32 rangedEvasionRate;              //0x13FC
        UINT32 rangedDefense;                  //0x1400
        UINT32 rangedCriticalHitRate;          //0x1404
        PAD(4);
        BOOL silenced;                         //0x140C
        UINT32 magicEvasionStatus;             //0x1410
        UINT32 magicEvasionCounter;            //0x1414
        UINT32 magicMirrorSkillId;             //0x1418
        UINT32 magicMirrorSkillLv;             //0x141C
        // bug: decreases hit rate
        UINT32 magicHitRate;                   //0x1420
        UINT32 minMagicPower;                  //0x1424
        UINT32 magicEvasionRate;               //0x1428
        UINT32 magicResistance;                //0x142C
        UINT32 magicCriticalHitRate;           //0x1430
        PAD(16);
        UserStatus status;                     //0x1444
        PAD(4);
        bool sitting;                          //0x144C
        UINT8 motionValue;                     //0x144D
        PAD(2);
        BOOL running;                          //0x1450
        BOOL attacking;                        //0x1454
        UserAttackType attackType;             //0x1458
        UINT32 prevSkillUseIndex;              //0x145C
        PAD(4);
        UINT32 itemQualityDecreaseSlot;        //0x1464
        DWORD attackTypeSkillTick;             //0x1468
        DWORD attackTypeBasicTick;             //0x146C
        DWORD rebirthExpireTick;               //0x1470
        BOOL leaderResurrect;                  //0x1474
        UINT32 expLossRate;                    //0x1478
        UserVehicleStatus vehicleStatus;       //0x147C
        DWORD vehicleRideTick;                 //0x1480
        UINT32 vehicleShapeType;               //0x1484
        UINT32 vehicleShapeTypeAdd;            //0x1488
        ULONG vehicleRideCharId;               //0x148C
        ULONG vehicleRideRequestSenderId;      //0x1490
        DWORD vehicleRideRequestExpireTick;    //0x1494
        ULONG partySummonRequestSenderId;      //0x1498
        DWORD partySummonRequestExpireTick;    //0x149C
        DWORD nextRecoveryTick;                //0x14A0
        Array<DWORD, 12> itemCooldown;         //0x14A4
        UserKillCountStatus kcStatus;          //0x14D4
        // 0x1544
        PAD(16);
        UserTargetType targetType;             //0x1554
        // CUser->id, CMob->id
        ULONG targetId;                        //0x1558
        PAD(100);
        CExchange exchange;                    //0x15C0
        CExchangePvP exchangePvP;              //0x15E8
        MyShop myShop;                         //0x1634
        CParty* party;                         //0x17F4
        ULONG partyRequestSenderId;            //0x17F8
        bool partySearchEnabled;               //0x17FC
        PAD(3);
        ULONG guildId;                         //0x1800
        UINT32 guildLv;                        //0x1804
        PAD(8);
        CGuild* guild;                         //0x1810
        CGuildCreate* guildCreate;             //0x1814
        CMiniGame miniGame;                    //0x1818
        UINT32 buddyCount;                     //0x1838
        Array<CFriend, 100> buddyList;         //0x183C
        UINT32 blockCount;                     //0x377C
        // 0x3780
        Array<BlockUser, 100> blockList;       //0x3780
        ULONG buddyRequestSenderId;            //0x5530
        PAD(76);
        BOOL joinGuildDisabled;                //0x5580
        BOOL grbZoneEnterFlag;                 //0x5584
        BOOL insZoneEnterFlag;                 //0x5588
        UserPvPStatus pvpStatus;               //0x558C
        DWORD pvpRequestExpireTick;            //0x5590
        ULONG pvpRequestTargetId;              //0x5594
        SVector pvpPos;                        //0x5598
        ULONG gvgRequestTargetId;              //0x55A4
        SVector gvgPos;                        //0x55A8
        DWORD gvgRequestExpireTick;            //0x55B4
        PAD(8);
        CUserCrypto crypto;                    //0x55C0
        UserWhere where;                       //0x57F4
        PAD(8);
        UINT64 sessionId;                      //0x5800
        AuthStatus authStatus;                 //0x5808
        PAD(3);
        ULONG questionId;                      //0x580C
        ULONG chatSendToTargetId;              //0x5810
        bool visible;                          //0x5814
        bool attackable;                       //0x5815
        PAD(2);
        DWORD enableMoveTick;                  //0x5818
        DWORD enableChatTick;                  //0x581C
        ULONG chatListenToTargetId;            //0x5820
        ULONG chatListenCharId;                //0x5824
        PAD(4);
        // UserUID
        ULONG userId;                          //0x582C
        UINT32 serverId;                       //0x5830
        CharArray<32> username;                //0x5834
        bool attackItemOptionFlag;             //0x5854
        bool ignoreMaxHpMpSpSpeed;             //0x5855
        PAD(14);
        UINT32 questKillPCCount;               //0x5864
        UINT32 questKillMobCount;              //0x5868
        PAD(12);
        UserLogoutType logoutType;             //0x5878
        DWORD logoutTick;                      //0x587C
        int connectionCloseType;               //0x5880
        PAD(44);
        UINT32 numWhereErrors;                 //0x58B0
        UserRecallType recallType;             //0x58B4
        DWORD recallTick;                      //0x58B8
        UINT32 recallMapId;                    //0x58BC
        SVector recallPos;                     //0x58C0
        PAD(4);
        DWORD partyRequestExpireTick;          //0x58D0
        PAD(8);
        bool isMessageToServer;                //0x58DC
        PAD(7);
        DWORD enableShoutTick;                 //0x58E4
        UINT8 statResetCount;                  //0x58E8
        UINT8 skillResetCount;                 //0x58E9
        bool statResetEvent;                   //0x58EA
        bool skillResetEvent;                  //0x58EB
        DWORD lockOnTick;                      //0x58EC
        PAD(4);
        ULONG billingRemainTime;               //0x58F4
        PAD(4);
        UINT32 recallItemBag;                  //0x58FC
        UINT32 recallItemSlot;                 //0x5900
        UserRecallItemType recallItemType;     //0x5904
        UINT32 recallItemGroup;                //0x5908
        UserSavePoint savePoint;               //0x590C
        UserCharmType charmType;               //0x594C
        UINT32 increaseGoldRate;               //0x5950
        BOOL eternalEndurance;                 //0x5954
        BOOL preventExpLoss;                   //0x5958
        BOOL preventItemDrop;                  //0x595C
        BOOL preventEquipmentDrop;             //0x5960
        BOOL recallWarehouse;                  //0x5964
        BOOL doubleWarehouse;                  //0x5968
        UINT32 increaseExpRate;                //0x596C
        // true = exp * 1.5
        BOOL expMultiplied;                    //0x5970
        BOOL continuousResurrection;           //0x5974
        BOOL nameChange;                       //0x5978
        BOOL battlefieldRune;                  //0x597C
        ProductLog productLog;                 //0x5980
        UINT32 points;                         //0x5AC0
        volatile UINT disableShop;             //0x5AC4
        DWORD reloadPointTick;                 //0x5AC8
        StoredPointItems storedPointItems;     //0x5ACC
        // 0x6264
        PAD(32);
        CRITICAL_SECTION cs;                   //0x6284
        PAD(4);
        // 0x62A0

        // custom
        ItemQualityLvEx itemQualityLvEx;       //0x62A0
        ItemQualityEx itemQualityEx;           //0x62B8
        TownMoveScroll townMoveScroll;         //0x62E8
        SkillAbilityEx skillAbility;           //0x62F4

        static void AddApplySkillBuff(CUser* user, SkillInfo* skillInfo);
        static void AddApplySkillDebuff(CUser* user, CSkill* skill, SkillInfo* skillInfo);
        static void AddExpFromUser(CUser* user/*esi*/, ULONG lastAttackUserId, int exp, BOOL isQuest);
        static void CancelActionExc(CUser* user/*edi*/);
        static void ChkAddMoneyGet(CUser* user/*ecx*/, ULONG money/*edx*/);
        static void ExchangeCancelReady(CUser* user/*ecx*/, CUser* exchangeUser/*esi*/);
        static void GetGuildName(CUser* user/*ebx*/, char* output);
        static int GetPartyType(CUser* user);
        static bool HasBuffUpLevel(CUser* user/*esi*/, SkillInfo* info/*ebx*/);
        static void InitEquipment(CUser* user/*ecx*/);
        static void InitEquipment(CUser* user/*ecx*/, BOOL reset);
        static void ItemBagToBag(CUser* user/*ecx*/, int srcBag, int srcSlot, int destBag, int destSlot);
        static void ItemBagToBank(CUser* user/*edx*/, int srcBag, int srcSlot, int destBag/*100*/, int destSlot/*ecx*/);
        static void ItemBankToBag(CUser* user/*edx*/, int srcBag/*100*/, int srcSlot/*ecx*/, int destBag, int destSlot);
        static void ItemBankToBank(CUser* user/*esi*/, int srcBag/*100*/, int srcSlot, int destBag/*100*/, int destSlot/*ecx*/);
        static bool ItemCreate(CUser* user/*ecx*/, ItemInfo* info, int count);
        static bool ItemDelete(CUser* user, int type, int typeId);
        static void ItemEquipmentAdd(CUser* user/*edi*/, CItem* item/*eax*/, int slot);
        static void ItemEquipmentRem(CUser* user/*edx*/, CItem* item/*ecx*/, int slot);
        static void ItemEquipmentOptionAdd(CUser* user/*eax*/, CItem* item/*esi*/);
        static void ItemEquipmentOptionRem(CUser* user/*eax*/, CItem* item/*esi*/);
        static void ItemGet(CUser* user/*ecx*/, CItem* item);
        static void ItemGetMoney(CUser* user/*edx*/, int money/*ecx*/);
        static void ItemRemove(CUser* user/*ecx*/, int bag, int slot/*ebx*/);
        static void ItemUse(CUser* user, int bag, int slot, ULONG targetId, int byTargetType);
        static void ItemUseNSend(CUser* user, int bag, int slot, BOOL moveMap);
        static bool QuestAddItem(CUser* user, int type, int typeId/*ecx*/, int count, int* outBag, int* outSlot/*edx*/, ItemInfo* outInfo);
        static CQuest* QuestFind(CUser* user/*edi*/, int questId);
        static void QuestRemove(CUser* user/*esi*/, CQuest* quest/*eax*/, BOOL bySuccess);
        static void RemApplySkillBuff(CUser* user/*ecx*/, SkillInfo* skillInfo);
        static void RemApplySkillDebuff(CUser* user/*esi*/, CSkill* skill/*ebx*/, SkillInfo* skillInfo/*edx*/);
        static void SendAdminCmdError(CUser* user, UINT16 error/*ecx*/);
        static void SendAdminCmdSuccess(CUser* user);
        static void SendLogAdmin(CUser* user/*edx*/, const char* desc/*edi*/);
        static void SendLogAdmin(CUser* user/*ecx*/, const char* desc/*edi*/, const char* targetName/*ebx*/);
        static void SendLogAdmin(CUser* user/*ecx*/, const char* desc/*edi*/, const char* targetName/*ebx*/, const char* text);
        static void SendCharacterHonor(CUser* user/*ecx*/);
        static void SendDBExp(CUser* user/*eax*/);
        static void SendDBMoney(CUser* user/*eax*/);
        static void SendDBBankMoney(CUser* user/*eax*/);
        static void SendDBStatusUp(CUser* user/*eax*/);
        static void SendDBGrow(CUser* user/*eax*/);
        static void SendDBLevel(CUser* user/*eax*/);
        static void SendDBSkillPoint(CUser* user/*eax*/);
        static void SendDBStatPoint(CUser* user/*eax*/);
        static void SendDBAgentQuickSlot(CUser* user/*eax*/);
        static void SendEnergyAllToParty(CUser* user/*eax*/);
        static void SendEquipment(CUser* user/*ecx*/, int slot);
        static void SendMaxHP(CUser* user/*esi*/);
        static void SendMaxMP(CUser* user/*esi*/);
        static void SendMaxSP(CUser* user/*esi*/);
        static void SendRecoverChange(CUser* user/*esi*/, int health/*ecx*/, int stamina/*edx*/, int mana);
        static void SendRecoverMe(CUser* user/*ecx*/, int health, int stamina, int mana);
        static void SendRecoverAdd(CUser* user/*eax*/, int health/*ecx*/, int stamina/*edx*/, int mana);
        static void SendRecoverSet(CUser* user/*esi*/, int health/*ecx*/, int stamina/*edx*/, int mana);
        static void SendRunMode(CUser* user, BOOL runMode);
        static void SendShape(CUser* user/*ecx*/);
        static void SendSpeed(CUser* user/*ecx*/);
        static void SendUserShape(CUser* user);
        static void SetAttack(CUser* user/*esi*/);
        static void SetGameLogMain(CUser* user/*edi*/, void* packet/*esi*/);
        static void SetSkillAbility(CUser* user, int typeEffect/*ecx*/, int type/*edx*/, int value/*eax*/);
        static void StatResetSkill(CUser* user/*eax*/, BOOL isEvent);
        static void StatResetStatus(CUser* user/*edi*/, BOOL isEvent);
        static void TauntMob(CUser* user, float dist, int aggro);
        static void UpdateKCStatus(CUser* user/*eax*/);
        static void UseItemSkill(CUser* user/*edi*/, SkillInfo* info/*eax*/);
    };
    #pragma pack(pop)

    //static_assert(sizeof(CUser) == 0x62A0);
    static_assert(sizeof(CUser) == 0x6300);
}
