#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/PartyTypes.h>
#include <shaiya/include/common/Sex.h>
#include <shaiya/include/common/SkillTypes.h>
#include <shaiya/include/common/UserTypes.h>
#include "AdminInfo.h"
#include "Attack.h"
#include "AttackAdd.h"
#include "BillingItemInfo.h"
#include "CExchange.h"
#include "CExchangePvP.h"
#include "CFriend.h"
#include "CMiniGame.h"
#include "CObjectConnection.h"
#include "CUserCrypto.h"
#include "CDamage.h"
#include "HPAbility.h"
#include "MyShop.h"
#include "PointLog.h"
#include "SSyncList.h"
#include "StoredPointItemInfo.h"
#include "SVector.h"
#include "Target.h"
#include "UserInfo.h"

namespace shaiya
{
    struct CDamage;
    struct CGuild;
    struct CGuildCreate;
    struct CItem;
    struct CloneUser;
    struct CNpc;
    struct CParty;
    struct CZone;
    struct ItemInfo;
    struct SkillInfo;

    using ProductLog = Array<PointLog, 10>;
    using StoredPointItems = Array<StoredPointItemInfo, 640>;

    #pragma pack(push, 1)
    struct SkillAbility70
    {
        uint16_t skillId;
        uint8_t skillLv;
        bool triggered;
        tick32_t keepTime;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserKillCountStatus
    {
        PAD(4);                     //0x14D4
        int32_t health;             //0x14D8
        int32_t stamina;            //0x14DC
        int32_t mana;               //0x14E0
        int32_t strength;           //0x14E4
        int32_t reaction;           //0x14E8
        int32_t intelligence;       //0x14EC
        int32_t wisdom;             //0x14F0
        int32_t dexterity;          //0x14F4
        int32_t luck;               //0x14F8
        int32_t sitRecoveryHP;      //0x14FC
        int32_t sitRecoverySP;      //0x1500
        int32_t sitRecoveryMP;      //0x1504
        int32_t combatRecoveryHP;   //0x1508
        int32_t combatRecoverySP;   //0x150C
        int32_t combatRecoveryMP;   //0x1510
        int32_t criticalHitRate;    //0x1514
        int32_t hitRate;            //0x1518
        int32_t defense;            //0x151C
        int32_t rangedDefense;      //0x1520
        int32_t magicDefense;       //0x1524
        int32_t evasionRate;        //0x1528
        int32_t rangedEvasionRate;  //0x152C
        int32_t magicEvasionRate;   //0x1530
        PAD(16);
        // 0x70
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserWeaponMasterySpeed
    {
        PAD(1);
        uint8_t oneHandedSword;
        uint8_t twoHandedSword;
        uint8_t oneHandedAxe;
        uint8_t twoHandedAxe;
        uint8_t dualWield;
        uint8_t spear;
        uint8_t oneHandedBlunt;
        uint8_t twoHandedBlunt;
        uint8_t reverseDagger;
        uint8_t dagger;
        uint8_t crossbow;
        uint8_t staff;
        uint8_t bow;
        uint8_t javelin;
        uint8_t knuckles;
        PAD(4);
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserWeaponMasteryPower
    {
        PAD(1);
        uint8_t oneHandedSword;
        uint8_t twoHandedSword;
        uint8_t oneHandedAxe;
        uint8_t twoHandedAxe;
        uint8_t dualWield;
        uint8_t spear;
        uint8_t oneHandedBlunt;
        uint8_t twoHandedBlunt;
        uint8_t reverseDagger;
        uint8_t dagger;
        uint8_t crossbow;
        uint8_t staff;
        uint8_t bow;
        uint8_t javelin;
        uint8_t knuckles;
        PAD(4);
    };
    #pragma pack(pop)

    enum struct UserAttackType : int32_t
    {
        None, 
        Basic, 
        Skill
    };

    enum struct UserHPAssistType : int32_t
    {
        Sp, Mp, SpMp
    };

    enum struct UserLogoutType : int32_t
    {
        None,
        CharacterScreen,
        Exit
    };

    enum struct UserPvPStatus : int32_t
    {
        None,
        RequestSent,
        RequestRecv,
        Countdown,
        Start,
        Exchange
    };

    enum struct UserMovePosType : int32_t
    {
        Default,
        GateKeeper = 1,
        Portal = 1,
        SavePoint,
        RecallRune,
        PartyCall,
        PartyMove,
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

    enum struct UserRecoveryStatus : int32_t
    {
        Sit,
        Normal,
        Combat
    };

    enum struct UserStatus : int32_t
    {
        None,
        Death,
        Combat,
        Casting
    };

    enum struct UserTargetType : int32_t
    {
        None, 
        User, 
        Mob
    };

    enum struct UserVehicleStatus : int32_t
    {
        None, 
        Casting,
        Riding
    };

    enum struct UserWhere : int32_t
    {
        Default,
        WorldLeave,
        ZoneWait,
        ZoneLeave,
        ZoneEnter
    };

    #pragma pack(push, 1)
    struct CUser : CObjectConnection, UserInfo
    {
        int32_t abilityStrength;                 //0x121C
        int32_t abilityDexterity;                //0x1220
        int32_t abilityIntelligence;             //0x1224
        int32_t abilityWisdom;                   //0x1228
        int32_t abilityReaction;                 //0x122C
        int32_t abilityLuck;                     //0x1230
        int32_t health;                          //0x1234
        int32_t mana;                            //0x1238
        int32_t stamina;                         //0x123C
        int32_t combatRecoveryHP;                //0x1240
        int32_t combatRecoverySP;                //0x1244
        int32_t combatRecoveryMP;                //0x1248
        int32_t sitRecoveryHP;                   //0x124C
        int32_t sitRecoverySP;                   //0x1250
        int32_t sitRecoveryMP;                   //0x1254
        int32_t sitRecoveryAddHP;                //0x1258
        int32_t sitRecoveryAddSP;                //0x125C
        int32_t sitRecoveryAddMP;                //0x1260
        int32_t recoveryHP;                      //0x1264
        int32_t recoverySP;                      //0x1268
        int32_t recoveryMP;                      //0x126C
        UserRecoveryStatus recoveryStatus;       //0x1270
        int32_t decreaseUseMP;                   //0x1274
        int32_t decreaseUseSP;                   //0x1278
        int32_t attributeAttack;                 //0x127C
        int32_t attributeDefense;                //0x1280
        PAD(92);
        int32_t itemAttackPower;                 //0x12E0
        int32_t itemAttackPowerAdd;              //0x12E4
        int32_t itemDefense;                     //0x12E8
        int32_t itemMagicDefense;                //0x12EC
        int32_t abilityAttackRange;              //0x12F0
        int32_t abilityAttackSpeed;              //0x12F4
        int32_t abilityMoveSpeed;                //0x12F8
        int32_t abilityCriticalHitRate;          //0x12FC
        int32_t decreaseSkillWaitTime;           //0x1300
        int32_t abilityAbsorption;               //0x1304
        int32_t interpretationLv;                //0x1308
        int32_t bagsUnlocked;                    //0x130C
        UserWeaponMasterySpeed weaponSpeed;      //0x1310
        UserWeaponMasteryPower weaponPower;      //0x1324
        int32_t crossRoad;                       //0x1338
        uint8_t shieldMasteryDefense;            //0x133C
        PAD(3);
        UserHPAssistType assistType;             //0x1340
        bool32_t immobilized;                    //0x1344
        bool32_t unconscious;                    //0x1348
        bool32_t sleeping;                       //0x134C
        bool32_t degenerated;                    //0x1350
        uint16_t transformMobId;                 //0x1354
        PAD(10);
        ShapeType shapeType;                     //0x1360
        PAD(3);
        int32_t shapeMobId;                      //0x1364
        CloneUser* clone;                        //0x1368
        bool32_t invincible;                     //0x136C
        bool preventDeath;                       //0x1370
        bool preventDying;                       //0x1371
        bool preventAggro;                       //0x1372
        bool danceOfDeath;                       //0x1373
        bool etainShield;                        //0x1374
        PAD(3);
        HPAbility passiveAbility;                //0x1378
        AttackAdd attackAdd;                     //0x1384
        AttackAdd attackAddRanged;               //0x1394
        AttackAdd attackAddMagic;                //0x13A4
        Attack attack;                           //0x13B4
        Attack attackRanged;                     //0x13E0
        Attack attackMagic;                      //0x140C
        PAD(4);
        uint32_t mapCurseSkillId;                //0x143C
        uint8_t mapCursePvPKillCountAdd;         //0x1440
        uint8_t mapCursePvPExpAdd;               //0x1441
        PAD(2);
        UserStatus status;                       //0x1444
        int statusLife;                          //0x1448
        uint8_t motion;                          //0x144C
        uint8_t moveMotion;                      //0x144D
        PAD(2);
        bool32_t run;                            //0x1450
        int32_t attackMode;                      //0x1454
        UserAttackType attackType;               //0x1458
        uint32_t prevSkillUseIndex;              //0x145C
        PAD(4);
        int32_t itemQualityDecreaseSlot;         //0x1464
        tick32_t nextAttackTime;                 //0x1468
        tick32_t prevAttackTime;                 //0x146C
        tick32_t rebirthExpireTime;              //0x1470
        int32_t rebirthType;                     //0x1474
        int32_t expDropRate;                     //0x1478
        UserVehicleStatus vehicleStatus;         //0x147C
        tick32_t vehicleUseTime;                 //0x1480
        uint32_t vehicleShapeType;               //0x1484
        uint32_t vehicleShapeTypeAdd;            //0x1488
        uint32_t vehicle2ReqTargetId;            //0x148C
        uint32_t vehicle2ReqSenderId;            //0x1490
        tick32_t vehicle2ReqExpireTime;          //0x1494
        uint32_t partyCallSenderId;              //0x1498
        tick32_t partyCallExpireTime;            //0x149C
        tick32_t nextRecoverTime;                //0x14A0
        Array<tick32_t, 12> nextItemUseTimes;    //0x14A4
        UserKillCountStatus kcStatus;            //0x14D4
        Target target;                           //0x1544
        PAD(8);
        Target prevTarget;                       //0x1554
        PAD(20);
        CDamage attackDamage;                    //0x1570
        PAD(32);
        CNpc* useNpc;                            //0x15BC
        CExchange exchange;                      //0x15C0
        CExchangePvP exchangePvP;                //0x15E8
        MyShop myShop;                           //0x1634
        CParty* party;                           //0x17F4
        uint32_t partyReqSenderId;               //0x17F8
        bool partySearchRegistered;              //0x17FC
        PAD(3);
        uint32_t guildId;                        //0x1800
        uint32_t guildLv;                        //0x1804
        uint32_t guildReqSenderId;               //0x1808
        uint32_t guildMasterReqSenderId;         //0x180C
        CGuild* guild;                           //0x1810
        CGuildCreate* guildCreate;               //0x1814
        CMiniGame miniGame;                      //0x1818
        CFriend friend_;                         //0x1838
        // 0x554C
        PAD(52);
        // 259200000
        tick32_t nextGuildJoinTime;              //0x5580
        bool32_t grbZoneEnterFlag;               //0x5584
        bool32_t insZoneEnterFlag;               //0x5588
        UserPvPStatus pvpStatus;                 //0x558C
        tick32_t pvpReqExpireTime;               //0x5590
        uint32_t pvpReqTargetId;                 //0x5594
        SVector pvpPos;                          //0x5598
        uint32_t gvgReqTargetId;                 //0x55A4
        SVector gvgPos;                          //0x55A8
        tick32_t gvgReqExpireTime;               //0x55B4
        bool pvpJoin;                            //0x55B8
        PAD(3);
        bool32_t gvgReady;                       //0x55BC
        CUserCrypto crypto;                      //0x55C0
        UserWhere where;                         //0x57F4
        PAD(8);
        uint64_t sessionId;                      //0x5800
        AuthStatus authStatus;                   //0x5808
        PAD(3);
        AdminInfo adminInfo;                     //0x580C
        uint32_t billingId;                      //0x582C
        int32_t serverId;                        //0x5830
        String<32> username;                     //0x5834
        bool itemAttackFlag;                     //0x5854
        bool initStatusFlag;                     //0x5855
        PAD(2);
        bool32_t closeBySession;                 //0x5858
        bool32_t closeByDBAgent;                 //0x585C
        bool enableDBCharSelect;                 //0x5860
        bool enableDBCharRename;                 //0x5861
        PAD(2);
        int32_t questPvPKillCount;               //0x5864
        int32_t questMobKillCount;               //0x5868
        tick32_t prevMoveTime;                   //0x586C
        tick32_t questLastUseItemTime;           //0x5870
        uint8_t questLastUseItemId;              //0x5874
        PAD(3);
        UserLogoutType logoutType;               //0x5878
        tick32_t logoutTime;                     //0x587C
        bool32_t reconnectReady;                 //0x5880
        uint8_t moveByWarResult;                 //0x5884
        PAD(43);
        uint32_t undefinedPacketErrorCount;      //0x58B0
        UserMovePosType movePosType;             //0x58B4
        tick32_t movePosTime;                    //0x58B8
        uint32_t moveMapId;                      //0x58BC
        SVector movePos;                         //0x58C0
        tick32_t exchangeReqExpireTime;          //0x58CC
        tick32_t partyReqExpireTime;             //0x58D0
        tick32_t guildReqExpireTime;             //0x58D4
        tick32_t friendReqExpireTime;            //0x58D8
        bool chatItemUse;                        //0x58DC
        PAD(3);
        tick32_t nextChatItemUseTime;            //0x58E0
        tick32_t nextChatShoutTime;              //0x58E4
        uint8_t statusResetCount;                //0x58E8
        uint8_t skillResetCount;                 //0x58E9
        bool disableResetStatus;                 //0x58EA
        bool disableResetSkill;                  //0x58EB
        tick32_t lockOnTime;                     //0x58EC
        int billingType;                         //0x58F0
        time32_t billingRemainTime;              //0x58F4
        time32_t secondCharDisconnectTime;       //0x58F8
        int32_t savePosUseBag;                   //0x58FC
        int32_t savePosUseSlot;                  //0x5900
        int32_t savePosUseIndex;                 //0x5904
        uint32_t nextItemUseTimeIndex;           //0x5908
        Array<int32_t, 4> saveMapId;             //0x590C
        Array<SVector, 4> savePos;               //0x591C
        SkillCharmType charmType;                //0x594C
        uint32_t increaseGoldDropRate;           //0x5950
        bool32_t eternalEndurance;               //0x5954
        bool32_t preventExpLoss;                 //0x5958
        bool32_t preventItemDrop;                //0x595C
        bool32_t preventEquipmentDrop;           //0x5960
        bool32_t recallWarehouse;                //0x5964
        bool32_t doubleWarehouse;                //0x5968
        // exp *= 2.0 (see 00574080)
        bool32_t multiplyExp2;                   //0x596C
        // exp *= 1.5 (see 00574090)
        bool32_t multiplyExp1;                   //0x5970
        bool32_t continuousRebirth;              //0x5974
        bool32_t nameChange;                     //0x5978
        bool32_t battlefieldRune;                //0x597C
        ProductLog productLog;                   //0x5980
        uint32_t points;                         //0x5AC0
        volatile unsigned pointsLock;            //0x5AC4
        // 40000
        tick32_t nextPointReloadTime;            //0x5AC8
        StoredPointItems storedPointItems;       //0x5ACC
        CRITICAL_SECTION csStoredPointItems;     //0x624C
        // 0x6264
        PAD(32);
        CRITICAL_SECTION cs;                     //0x6284
        PAD(4);
        // 0x62A0

        // custom
        ItemQualityLv<24> itemQualityLvEx;       //0x62A0
        ItemQuality<24> itemQualityEx;           //0x62B8
        SkillAbility70 skillAbility70;           //0x62E8
        uint32_t multiplyQuestExpRate;           //0x62F0

        static void AddExpFromUser(CUser* user/*esi*/, unsigned lastTargetId, int exp, bool isQuest);
        static void CancelActionExc(CUser* user/*edi*/);
        static void ChkAddMoneyGet(CUser* user/*ecx*/, unsigned money/*edx*/);
        static void GemEquipmentAdd(CUser* user/*eax*/, int slot/*esi*/, int gem/*ecx*/);
        static void GemEquipmentRem(CUser* user/*eax*/, int slot/*esi*/, int gem/*ecx*/);
        static void GetGuildName(CUser* user/*ebx*/, char* output);
        static PartyType GetPartyType(CUser* user);
        static void InitEquipment(CUser* user/*ecx*/);
        static void InitEquipment(CUser* user/*ecx*/, bool reset);
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
        static void ItemGetMoney(CUser* user/*edx*/, unsigned money/*ecx*/);
        static void ItemRemove(CUser* user/*ecx*/, int bag, int slot/*ebx*/);
        static void ItemUse(CUser* user, int bag, int slot, unsigned targetId, int targetType);
        static void ItemUseNSend(CUser* user, int bag, int slot, bool moveMap);
        static void LevelChange(CUser* user, int prevLv, int currLv);
        static void LevelUp(CUser* user, bool event);
        static void LevelUpStatus(CUser* user);
        static bool QuestAddItem(CUser* user, int type, int typeId/*ecx*/, int count, int* outBag, int* outSlot/*edx*/, ItemInfo* outInfo);
        static CQuest* QuestFind(CUser* user/*edi*/, int questId);
        static void QuestRemove(CUser* user/*esi*/, CQuest* quest/*eax*/, bool success);
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
        static void SendShape(CUser* user/*ecx*/);
        static void SendSpeed(CUser* user/*ecx*/);
        static void SendUserShape(CUser* user);
        static void SetAttack(CUser* user/*esi*/);
        static void SetGameLogMain(CUser* user/*edi*/, void* packet/*esi*/);
        static void StatResetSkill(CUser* user/*eax*/, bool event);
        static void StatResetStatus(CUser* user/*edi*/, bool event);
        static void TauntMob(CUser* user, float dist, int aggro);
        static void UpdateKCStatus(CUser* user/*eax*/);
        static bool UseItemSkill(CUser* user/*edi*/, SkillInfo* info/*eax*/);
    };
    #pragma pack(pop)

    //static_assert(sizeof(CUser) == 0x62A0);
    static_assert(sizeof(CUser) == 0x62F4);
}
