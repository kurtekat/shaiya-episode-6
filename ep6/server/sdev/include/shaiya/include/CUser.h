#pragma once
#include <shaiya/common.h>
#include <shaiya/include/CFriend.h>
#include <shaiya/include/CMiniGame.h>
#include <shaiya/include/CSkill.h>
#include <shaiya/include/MyShop.h>
#include <shaiya/include/SConnection.h>
#include <shaiya/include/SSyncList.h>
#include <shaiya/include/SVector.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct AdminInfo
    {
        ULONG questionId;          //0x580C
        ULONG chatSendToId;        //0x5810
        bool visible;              //0x5814
        bool attackable;           //0x5815
        PAD(2);
        TickCount moveEnableTime;  //0x5818
        TickCount chatEnableTime;  //0x581C
        ULONG chatListenToId;      //0x5820
        ULONG chatListenFromId;    //0x5824
        PAD(4);
    };

    enum struct AttackType : UINT32
    {
        None,
        Basic,
        Skill
    };

    enum struct Attribute : UINT32
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

    struct BanCharacter
    {
        ULONG id;       //0x00
        char name[21];  //0x04
        char memo[51];  //0x19
        // 0x4C
    };

    enum struct BattleState : UINT32
    {
        None,
        RequestSent,
        RequestRecv,
        Countdown,
        Start,
        Transaction
    };

    struct BillingItem
    {
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
    };

    struct CloakBadge
    {
        UINT8 frontPattern;
        UINT8 backPattern;
        UINT8 emblem;
        UINT8 frontColor;
        UINT8 backColor;
        UINT8 emblemColor;
    };

    struct CloneEquipment
    {
        UINT8 type;
        UINT8 typeId;
        UINT8 enchantStep;
    };

    #ifdef SHAIYA_EP6
    struct CloneUser
    {
        PAD(8);
        bool dead;                //0x08
        bool sitMode;             //0x09
        Country country;          //0x0A
        Family family;            //0x0B
        UINT8 hair;               //0x0C
        UINT8 face;               //0x0D
        UINT8 size;               //0x0E
        Job job;                  //0x0F
        Sex sex;                  //0x10
        UINT8 partyType;          //0x11
        Grow grow;                //0x12
        PAD(1);
        UINT32 kills;             //0x14
        CloneEquipment equipment[17];  //0x18
        char charName[21];        //0x4B
        CloakBadge cloakBadge;    //0x60
        char guildName[25];       //0x66
        UINT8 packetLength;       //0x7F
        // 0x80
    };
    #else
    struct CloneUser
    {
        PAD(8);
        bool dead;                //0x08
        bool sitMode;             //0x09
        Country country;          //0x0A
        Family family;            //0x0B
        UINT8 hair;               //0x0C
        UINT8 face;               //0x0D
        UINT8 size;               //0x0E
        Job job;                  //0x0F
        Sex sex;                  //0x10
        UINT8 partyType;          //0x11
        Grow grow;                //0x12
        PAD(1);
        UINT32 kills;             //0x14
        CloneEquipment equipment[8];  //0x18
        char charName[21];        //0x30
        CloakBadge cloakBadge;    //0x45
        char guildName[25];       //0x4B
        UINT8 packetLength;       //0x64
        PAD(3);
        // 0x68
    };
    #endif

    enum struct CharmType : UINT32
    {
        None,
        WhiteTiger,
        BlueDragon,
        RedPhoenix
    };

    enum struct LogoutType : UINT32
    {
        None,
        CharacterScreen,
        Exit
    };

    enum struct PartyType : UINT8
    {
        None,
        Member,
        Boss
    };

    enum struct Permission : UINT8
    {
        AdminA = 1,
        AdminB = 2,
        AdminC = 3,
        AdminD = 4,
        AdminE = 5,
        Normal = 11
    };

    struct ProductItem
    {
        char code[24];  //0x00
        PAD(4);
        UINT32 cost;    //0x1C
        // 0x20
    };

    struct QuickSlot
    {
        UINT8 bag;
        UINT8 slot;
        UINT16 srcBag;
        UINT16 srcSlot;
    };

    enum struct RecallType : UINT32
    {
        Default,
        GateKeeper = 1,
        Portal = 1,
        SavePoint,
        Rune,
        PartyMemberSummonRune,
        MovementRune,
        Unknown,
        MoveChar = 0xF904,
        MoveCharZone = 0xF905,
        MoveParty = 0xF90C,
        MoveTo = 0xFA09,
        MoveZone = 0xFA0A,
        MoveMap = 0xFA11,
        MoveInsZone = 0xFA12
    };

    enum struct RecallItemType : UINT32
    {
        None,
        SavePoint1,
        SavePoint2,
        SavePoint3,
        SavePoint4,
        PartyMemberSummonRune = 100,
        MovementRune = 101,
        Unknown = 254,
        Rune = 255
    };

    enum struct RecoveryType : UINT32
    {
        Sit,
        Normal,
        Combat
    };

    struct SavePoint
    {
        UINT32 mapid[4];
        SVector pos[4];
        // 0x40
    };

    enum struct ShapeType : UINT8
    {
        None,
        Chicken = 4,
        Dog = 5,
        Horse = 6,
        Pig = 7,
        Fox = 10,
        Wolf = 11,
        Knight = 12,
        Stealth = 13,
        Disguise = 100,
        Transformation = 102,
    };

    enum struct StateType : UINT32
    {
        None,
        Death,
        Combat
    };

    enum struct TargetType : UINT32
    {
        None,
        User,
        Mob
    };

    enum struct VehicleState : UINT32
    {
        None,
        Summon,
        Riding
    };

    enum struct Where : UINT32
    {
        None,
        LeaveZone = 3,
        EnterZone = 4
    };

    struct CUser
    {
        SConnection connection;            //0x00
        SVector pos;                       //0xD0
        ULONG id;                          //0xDC
        FWDDECL CZone* zone;               //0xE0
        UINT32 cellX;                      //0xE4
        UINT32 cellZ;                      //0xE8
        PAD(60);
        ULONG charId;                      //0x128
        UINT8 slot;                        //0x12C
        Country country;                   //0x12D
        Family family;                     //0x12E
        Grow grow;                         //0x12F
        PAD(1);
        UINT8 hair;                        //0x131
        UINT8 face;                        //0x132
        UINT8 size;                        //0x133
        Job job;                           //0x134
        Sex sex;                           //0x135
        UINT16 level;                      //0x136
        UINT16 statPoints;                 //0x138
        UINT16 skillPoints;                //0x13A
        UINT32 exp;                        //0x13C
        UINT32 money;                      //0x140
        PAD(4);
        Count kills;                       //0x148
        Count deaths;                      //0x14C
        Count victories;                   //0x150
        Count defeats;                     //0x154
        UINT32 killLv;                     //0x158
        UINT32 deathLv;                    //0x15C
        UINT16 mapId;                      //0x160
        UINT16 direction;                  //0x162
        UINT16 honor;                      //0x164
        UINT16 vg;                         //0x166
        UINT8 cg;                          //0x168
        UINT8 og;                          //0x169
        UINT16 ig;                         //0x16A
        UINT16 strength;                   //0x16C
        UINT16 dexterity;                  //0x16E
        UINT16 intelligence;               //0x170
        UINT16 wisdom;                     //0x172
        UINT16 recovery;                   //0x174
        UINT16 luck;                       //0x176
        UINT32 maxHealth;                  //0x178
        UINT32 maxMana;                    //0x17C
        UINT32 maxStamina;                 //0x180
        char charName[21];                 //0x184
        // 0x199
        PAD(13);
        UINT16 itemQuality[13];            //0x1A6
        FWDDECL CItem* inventory[6][24];   //0x1C0
        FWDDECL CItem* warehouse[240];     //0x400
        BillingItem bank[240];             //0x7C0
        SSyncList<CSkill> applySkillList;  //0xA90
        UINT32 skillCount;                 //0xABC
        CSkill* skill[256];                //0xAC0
        UINT32 quickSlotCount;             //0xEC0
        QuickSlot quickSlot[58];           //0xEC4
        // 0x1020
        PAD(508);
        UINT32 abilityStrength;          //0x121C
        UINT32 abilityDexterity;         //0x1220
        UINT32 abilityIntelligence;      //0x1224
        UINT32 abilityWisdom;            //0x1228
        UINT32 abilityRecovery;          //0x122C
        UINT32 abilityLuck;              //0x1230
        UINT32 health;                   //0x1234
        UINT32 mana;                     //0x1238
        UINT32 stamina;                  //0x123C
        UINT32 combatHealthRecovery;     //0x1240
        UINT32 combatStaminaRecovery;    //0x1244
        UINT32 combatManaRecovery;       //0x1248
        UINT32 sitHealthRecovery;        //0x124C
        UINT32 sitStaminaRecovery;       //0x1250
        UINT32 sitManaRecovery;          //0x1254
        UINT32 addHealthRecovery;        //0x1258
        UINT32 addStaminaRecovery;       //0x125C
        UINT32 addManaRecovery;          //0x1260
        UINT32 healthRecovery;           //0x1264
        UINT32 staminaRecovery;          //0x1268
        UINT32 manaRecovery;             //0x126C
        RecoveryType recoveryType;       //0x1270
        PAD(8);
        Attribute weaponAttribute;       //0x127C
        Attribute armorAttribute;        //0x1280
        PAD(92);
        UINT32 addAttackPower;           //0x12E0
        UINT32 maxAddAtkPower;           //0x12E4
        UINT32 addDefense;               //0x12E8
        UINT32 addMagicResistance;       //0x12EC
        UINT32 abilityAttackRange;       //0x12F0
        UINT32 abilityAttackSpeed;       //0x12F4
        UINT32 abilityMoveSpeed;         //0x12F8
        UINT32 abilityCriticalHitRate;   //0x12FC
        PAD(4);
        UINT32 abilityAbsorption;        //0x1304
        UINT32 interpretationLv;         //0x1308
        UINT32 bagsUnlocked;             //0x130C
        PAD(52);
        BOOL isImmobilized;              //0x1344
        BOOL isUnconscious;              //0x1348
        BOOL isSleeping;                 //0x134C
        PAD(4);
        UINT16 transformMobId;           //0x1354
        PAD(10);
        ShapeType shapeType;             //0x1360
        PAD(3);
        UINT32 targetTransformMobId;     //0x1364
        CloneUser* clone;                //0x1368
        BOOL isInvincible;               //0x136C
        PAD(20);
        UINT32 abilityMeleeHitRate;      //0x1384
        UINT32 abilityMeleeAtkPower;     //0x1388
        UINT32 abilityMeleeEvasionRate;  //0x138C
        UINT32 abilityAddMeleeDefense;   //0x1390
        UINT32 abilityRangeHitRate;      //0x1394
        UINT32 abilityRangeAtkPower;     //0x1398
        UINT32 abilityRangeEvasionRate;  //0x139C
        UINT32 abilityAddRangeDefense;   //0x13A0
        UINT32 abilityMagicHitRate;      //0x13A4
        UINT32 abilityMagicAtkPower;     //0x13A8
        UINT32 abilityMagicEvasionRate;  //0x13AC
        UINT32 abilityMagicResistance;   //0x13B0
        BOOL isMeleeAttackBlinded;       //0x13B4
        UINT32 meleeEvasionStatus;       //0x13B8
        UINT32 meleeEvasionPercent;      //0x13BC
        UINT32 meleeMirrorSkillId;       //0x13C0
        UINT32 meleeMirrorSkillLv;       //0x13C4
        UINT32 meleeHitRate;             //0x13C8
        UINT32 minMeleeAtkPower;         //0x13CC
        UINT32 meleeEvasionRate;         //0x13D0
        UINT32 meleeDefense;             //0x13D4
        UINT32 meleeCriticalHitRate;     //0x13D8
        PAD(4);
        BOOL isRangeAttackBlinded;       //0x13E0
        UINT32 rangeEvasionStatus;       //0x13E4
        UINT32 rangeEvasionPercent;      //0x13E8
        UINT32 rangeMirrorSkillId;       //0x13EC
        UINT32 rangeMirrorSkillLv;       //0x13F0
        UINT32 rangeHitRate;             //0x13F4
        UINT32 minRangeAtkPower;         //0x13F8
        UINT32 rangeEvasionRate;         //0x13FC
        UINT32 rangeDefense;             //0x1400
        UINT32 rangeCriticalHitRate;     //0x1404
        PAD(4);
        BOOL isSilenced;                 //0x140C
        UINT32 magicEvasionStatus;       //0x1410
        UINT32 magicEvasionCounter;      //0x1414
        UINT32 magicMirrorSkillId;       //0x1418
        UINT32 magicMirrorSkillLv;       //0x141C
        // bug: decreases hit rate
        UINT32 magicHitRate;             //0x1420
        UINT32 minMagicPower;            //0x1424
        UINT32 magicEvasionRate;         //0x1428
        UINT32 magicResistance;          //0x142C
        UINT32 magicCriticalHitRate;     //0x1430
        PAD(16);
        StateType stateType;             //0x1444
        PAD(4);
        bool sitMode;                    //0x144C
        UINT8 elevation;                 //0x144D
        PAD(2);
        BOOL runMode;                    //0x1450
        BOOL combatMode;                 //0x1454
        AttackType attackType;           //0x1458
        UINT32 attackSkillIndex;         //0x145C
        PAD(8);
        TickCount attackTypeSkillTime;   //0x1468
        TickCount attackTypeBasicTime;   //0x146C
        TickCount rebirthTimeout;        //0x1470
        BOOL rebirthOnPartyBoss;         //0x1474
        PAD(4);
        VehicleState vehicleState;       //0x147C
        TickCount vehicleGotOnRideTime;  //0x1480
        PAD(8);
        ULONG vehicleRidingCharId;       //0x148C
        ULONG vehicleInviteCharId;       //0x1490
        TickCount vehicleInviteTimeout;  //0x1494
        PAD(12);
        TickCount itemGroupTimeout[12];  //0x14A4
        // 0x14D4
        PAD(4);
        UINT32 kcHealth;                 //0x14D8
        UINT32 kcStamina;                //0x14DC
        UINT32 kcMana;                   //0x14E0
        UINT32 kcStrength;               //0x14E4
        UINT32 kcRecovery;               //0x14E8
        UINT32 kcIntelligence;           //0x14EC
        UINT32 kcWisdom;                 //0x14F0
        UINT32 kcDexterity;              //0x14F4
        UINT32 kcLuck;                   //0x14F8
        UINT32 kcSitHealthRecovery;      //0x14FC
        UINT32 kcSitStaminaRecovery;     //0x1500
        UINT32 kcSitManaRecovery;        //0x1504
        UINT32 kcCombatHealthRecovery;   //0x1508
        UINT32 kcCombatStaminaRecovery;  //0x150C
        UINT32 kcCombatManaRecovery;     //0x1510
        UINT32 kcCriticalHitRate;        //0x1514
        UINT32 kcPhysicalHitRate;        //0x1518
        UINT32 kcMeleeDefense;           //0x151C
        UINT32 kcRangeDefense;           //0x1520
        UINT32 kcMagicResistance;        //0x1524
        UINT32 kcMeleeEvasionRate;       //0x1528
        UINT32 kcRangeEvasionRate;       //0x152C
        UINT32 kcMagicEvasionRate;       //0x1530
        // custom
        UINT32 confirmExchangeState;    //0x1534
        unsigned u0x1538;
        unsigned u0x153C;
        unsigned u0x1540;
        TargetType targetType;          //0x1544
        // CUser->id, CMob->id, CNpc->id
        ULONG targetId;                 //0x1548
        PAD(120);
        CUser* exchangeUser;            //0x15C4
        PAD(28);
        UINT8 exchangeState;            //0x15E4
        PAD(79);
        MyShop myShop;                  //0x1634
        FWDDECL CParty* party;          //0x17F4
        ULONG partyInviteCharId;        //0x17F8
        bool partySearchEnabled;        //0x17FC
        PAD(3);
        UINT32 guildId;                 //0x1800
        UINT32 guildLv;                 //0x1804
        PAD(8);
        FWDDECL CGuild* guild;              //0x1810
        FWDDECL CGuildCreate* guildCreate;  //0x1814
        CMiniGame miniGame;             //0x1818
        UINT32 buddyCount;              //0x1838
        CFriend buddy[100];             //0x183C
        UINT32 banCount;                //0x377C
        BanCharacter banChar[100];      //0x3780
        ULONG buddyInviteCharId;        //0x5530
        PAD(76);
        BOOL joinGuildDisable;          //0x5580
        BOOL joinedGuildRankBattle;     //0x5584
        PAD(4);
        BattleState battleState;        //0x558C
        PAD(4);
        ULONG battleCharId;             //0x5594
        PAD(12);
        ULONG battleGuildId;            //0x55A4
        PAD(588);
        Where where;                    //0x57F4
        PAD(8);
        UINT64 sessionId;               //0x5800
        Permission permission;          //0x5808
        PAD(3);
        AdminInfo adminInfo;            //0x580C
        ULONG userUid;                  //0x582C
        PAD(4);
        char username[32];              //0x5834
        PAD(1);
        bool isInitEquipment;           //0x5855
        PAD(34);
        LogoutType logoutType;          //0x5878
        TickCount logoutTime;           //0x587C
        PAD(48);
        Count whereErrors;              //0x58B0
        RecallType recallType;          //0x58B4
        TickCount recallTime;           //0x58B8
        UINT32 recallMapId;             //0x58BC
        SVector recallPos;              //0x58C0
        PAD(4);
        TickCount partyInviteTimeout;   //0x58D0
        PAD(8);
        bool isMessageToServer;         //0x58DC
        PAD(7);
        TickCount shoutEnableTime;      //0x58E4
        UINT8 statResetCount;           //0x58E8
        UINT8 skillResetCount;          //0x58E9
        bool statResetEvent;            //0x58EA
        bool skillResetEvent;           //0x58EB
        PAD(16);
        UINT32 recallItemBag;           //0x58FC
        UINT32 recallItemSlot;          //0x5900 
        RecallItemType recallItemType;  //0x5904
        UINT32 recallItemGroup;         //0x5908
        SavePoint savePoint;            //0x590C
        CharmType charmType;            //0x594C
        UINT32 increaseGoldRate;        //0x5950
        BOOL eternalEndurance;          //0x5954
        BOOL preventExpLoss;            //0x5958
        BOOL preventItemDrop;           //0x595C
        BOOL preventEquipDrop;          //0x5960
        BOOL recallWarehouse;           //0x5964
        BOOL doubleWarehouse;           //0x5968
        UINT32 increaseExpRate;         //0x596C
        // true = exp * 1.5
        BOOL expMultiplied;             //0x5970
        BOOL continuousResurrection;    //0x5974
        BOOL nameChange;                //0x5978
        BOOL battlefieldRune;           //0x597C
        // this makes no sense
        ProductItem product[10];        //0x5980
        UINT32 points;                  //0x5AC0 
        BOOL disableShop;               //0x5AC4
        PAD(4);
        BillingItem itemBox[240];       //0x5ACC
        // 0x5E8C
        PAD(1044);
        // 0x62A0

        static void CancelActionExc(CUser* user/*edi*/);
        static void ExchangeCancelReady(CUser* user/*ecx*/, CUser* exchangeUser/*esi*/);
        static void GetGuildName(CUser* user, char* output);
        static int GetPartyType(CUser* user);
        static void InitEquipment(CUser* user/*ecx*/);
        static void InitEquipment(CUser* user/*ecx*/, BOOL reset);
        static void ItemBagToBag(CUser* user/*ecx*/, int srcBag, int srcSlot, int destBag, int destSlot);
        static bool ItemCreate(CUser* user/*ecx*/, CGameData::ItemInfo* info, int count);
        static bool ItemDelete(CUser* user, int type, int typeId);
        static void ItemEquipmentAdd(CUser* user/*edi*/, CItem* item/*eax*/, int slot);
        static void ItemEquipmentOptionAdd(CUser* user/*eax*/, CItem* item/*esi*/);
        static void ItemEquipmentOptionRem(CUser* user/*eax*/, CItem* item/*esi*/);
        static void ItemGet(CUser* user/*ecx*/, CItem* item);
        static void ItemRemove(CUser* user/*ecx*/, int bag, int slot/*ebx*/);
        static void ItemUse(CUser* user, int bag, int slot, ULONG targetId, UINT32 byTargetType);
        static void ItemUseNSend(CUser* user, int bag, int slot, BOOL moveMap);
        static void SendAdminCmdError(CUser* user, UINT16 error/*ecx*/);
        static void SendCharacterHonor(CUser* user/*ecx*/);
        static void SendDBMoney(CUser* user/*eax*/);
        static void SendDBSkillPoint(CUser* user/*eax*/);
        static void SendDBStatPoint(CUser* user/*eax*/);
        static void SendDBStatusUp(CUser* user/*eax*/);
        static void SendEnergyAllToParty(CUser* user/*eax*/);
        static void SendEquipment(CUser* user/*ecx*/, int slot);
        static void SendMaxHP(CUser* user/*esi*/);
        static void SendMaxMP(CUser* user/*esi*/);
        static void SendMaxSP(CUser* user/*esi*/);
        static void SendRecoverMe(CUser* user/*ecx*/, int health, int stamina, int mana);
        static void SendRecoverAdd(CUser* user/*eax*/, int health/*ecx*/, int stamina/*edx*/, int mana);
        static void SendRecoverSet(CUser* user/*esi*/, int health/*ecx*/, int stamina/*edx*/, int mana);
        static void SendRunMode(CUser* user, BOOL runMode);
        static void SendShape(CUser* user/*ecx*/);
        static void SendSpeed(CUser* user/*ecx*/);
        static void SendUserShape(CUser* user);
        static void SetAttack(CUser* user/*esi*/);
        static void StatResetSkill(CUser* user/*eax*/, BOOL isEvent);
        static void StatResetStatus(CUser* user/*edi*/, BOOL isEvent);
        static void TauntMob(CUser* user, float dist, int aggro);
        static void UpdateKCStatus(CUser* user/*eax*/);
        static void UseItemSkill(CUser* user/*edi*/, CGameData::SkillInfo* info/*eax*/);
    };
    #pragma pack(pop)
}
