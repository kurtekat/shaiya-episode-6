#pragma once
#include <shaiya/include/common/AuthStatus.h>
#include <shaiya/include/common/BillingItem.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/NpcType.h>
#include <shaiya/include/common/PartyType.h>
#include <shaiya/include/common/Sex.h>
#include "include/shaiya/common.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CMap.h"
#include "include/shaiya/include/CVector.h"

namespace shaiya
{
    struct BlockData;
    struct FindPartyData;
    struct FriendData;
    struct GuildData2;
    struct GuildJoinUserData;
    struct GuildNpcData;
    struct GuildUserData;
    struct ObeliskData;
    struct PartyData;
    struct QuestData;
    struct QuestFinishData;
    struct SetSkillData;
    struct SkillData;

    using Inventory = Array<Array<CItem, 24>, 6>;
    using Warehouse = Array<CItem, 240>;
    using Bank = Array<BillingItem, 240>;
    using StoredPointItems = Bank;

    enum struct WindowType : UINT32
    {
        None,
        Teleportation = 17,
        CashShop,
        GiftBox,
        AppearanceChange,
        SexChange,
        Talk = 100,
        Merchant,
        Blacksmith,
        Warehouse,
        LinkAndExtract,
        Priest,
        GamblingHouse,
        GateKeeper,
        VetManager,
        BadgeMerchant,
        BankTeller,
        GuildMaster,
        AuctionBoard = 117,
        ProBlacksmith = 120,
        Recreation,
        Creation,
        RuneCombination = 126,
    };

    #pragma pack(push, 1)
    struct ExcItem
    {
        UINT8 srcBag;
        UINT8 srcSlot;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct QuickSlot
    {
        UINT8 srcBag;
        PAD(1);
        UINT16 srcSlot;
        PAD(4);
        // quick z and x
        UINT32 itemType;
        UINT32 itemTypeId;
        // 0x10
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct RaidParty
    {
        RaidPartyType partyType;  //0x00  0x22AA730
        UINT32 group;             //0x04  0x22AA734
        UINT32 leaderId;          //0x08  0x22AA738
        UINT32 subLeaderId;       //0x0C  0x22AA73C
        UINT32 itemDivSeq;        //0x10  0x22AA740
        BOOL isAutoJoin;          //0x14  0x22AA744
        UINT32 slot;              //0x18  0x22AA748
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 004F1980 ctor
    struct CPlayerData
    {
        UINT32 clientVersion;               //0x90D1D0  0x00
        AuthStatus authStatus;              //0x90D1D4  0x04
        PAD(3);
        BOOL isAdmin;                       //0x90D1D8  0x08
        UINT32 money;                       //0x90D1DC  0x0C
        UINT32 bankMoney;                   //0x90D1E0  0x10
        UINT32 level;                       //0x90D1E4  0x14
        UINT32 maxHealth;                   //0x90D1E8  0x18
        UINT32 maxMana;                     //0x90D1EC  0x1C
        UINT32 maxStamina;                  //0x90D1F0  0x20
        UINT32 exp;                         //0x90D1F4  0x24
        UINT32 reqExpToLvDown;              //0x90D1F8  0x28
        UINT32 reqExpToLvUp;                //0x90D1FC  0x2C
        UINT16 strength;                    //0x90D200  0x30
        UINT16 intelligence;                //0x90D202  0x32
        UINT16 dexterity;                   //0x90D204  0x34
        UINT16 wisdom;                      //0x90D206  0x36
        UINT16 reaction;                    //0x90D208  0x38
        UINT16 luck;                        //0x90D20A  0x3A
        PAD(160);
        UINT16 statPoint;                   //0x90D2AC  0xDC
        UINT16 skillPoint;                  //0x90D2AE  0xDE
        UINT32 abilityStrength;             //0x90D2B0  0xE0
        UINT32 abilityReaction;             //0x90D2B4  0xE4
        UINT32 abilityIntelligence;         //0x90D2B8  0xE8
        UINT32 abilityWisdom;               //0x90D2BC  0xEC
        UINT32 abilityDexterity;            //0x90D2C0  0xF0
        UINT32 abilityLuck;                 //0x90D2C4  0xF4
        UINT32 minAttackPower;              //0x90D2C8  0xF8
        UINT32 addAttackPower;              //0x90D2CC  0xFC
        UINT32 minMagicPower;               //0x90D2D0  0x100
        UINT32 addMagicPower;               //0x90D2D4  0x104
        UINT32 defense;                     //0x90D2D8  0x108
        UINT32 resistance;                  //0x90D2DC  0x10C
        CharArray<4096> c110;               //0x90D2E0  0x110
        UINT16 mapId;                       //0x90E2E0  0x1110
        PAD(2);
        D3DVECTOR rebirthPos;               //0x90E2E4  0x1114
        UINT16 direction;                   //0x90E2F0  0x1120
        PAD(2);
        ULONG charId;                       //0x90E2F4  0x1124
        Inventory inventory;                //0x90E2F8  0x1128
        Array<CItem, 256> bag250;           //0x910038  0x2E68
        Array<UINT16, 21> weaponStep;       //0x913438  0x6268
        PAD(2);
        TargetType targetType;              //0x913460  0x6294
        Country country;                    //0x913468  0x6298
        Grow grow;                          //0x913469  0x6299
        PAD(6);
        UINT8 hair;                         //0x913470  0x62A0
        UINT8 face;                         //0x913471  0x62A1
        UINT8 size;                         //0x913472  0x62A2
        Job job;                            //0x913473  0x62A3
        CharArray<4096> c62A4;              //0x913474  0x62A4
        Sex sex;                            //0x914474  0x72A4
        PAD(3);
        UINT32 health;                      //0x914478  0x72A8
        UINT32 mana;                        //0x91447C  0x72AC
        UINT32 stamina;                     //0x914480  0x72B0
        UINT8 helmetType;                   //0x914484  0x72B4
        UINT8 upperType;                    //0x914485  0x72B5
        UINT8 lowerType;                    //0x914486  0x72B6
        UINT8 handsType;                    //0x914487  0x72B7
        UINT8 bootsType;                    //0x914488  0x72B8
        UINT8 weaponType;                   //0x914489  0x72B9
        UINT8 shieldType;                   //0x91448A  0x72BA
        UINT8 cloakType;                    //0x91448B  0x72BB
        UINT8 necklaceType;                 //0x91448C  0x72BC
        UINT8 ring1Type;                    //0x91448D  0x72BD
        UINT8 ring2Type;                    //0x91448E  0x72BE
        UINT8 bracelet1Type;                //0x91448F  0x72BF
        UINT8 bracelet2Type;                //0x914490  0x72C0
        UINT8 vehicleType;                  //0x914491  0x72C1
        UINT8 petType;                      //0x914492  0x72C2
        UINT8 costumeType;                  //0x914493  0x72C3
        UINT8 wingsType;                    //0x914494  0x72C4
        UINT8 helmetTypeId;                 //0x914495  0x72C5
        UINT8 upperTypeId;                  //0x914496  0x72C6
        UINT8 lowerTypeId;                  //0x914497  0x72C7
        UINT8 handsTypeId;                  //0x914498  0x72C8
        UINT8 bootsTypeId;                  //0x914499  0x72C9
        UINT8 weaponTypeId;                 //0x91449A  0x72CA
        UINT8 shieldTypeId;                 //0x91449B  0x72CB
        UINT8 cloakTypeId;                  //0x91449C  0x72CC
        UINT8 necklaceTypeId;               //0x91449D  0x72CD
        UINT8 ring1TypeId;                  //0x91449E  0x72CE
        UINT8 ring2TypeId;                  //0x91449F  0x72CF
        UINT8 bracelet1TypeId;              //0x9144A0  0x72D0
        UINT8 bracelet2TypeId;              //0x9144A1  0x72D1
        UINT8 vehicleTypeId;                //0x9144A2  0x72D2
        UINT8 petTypeId;                    //0x9144A3  0x72D3
        UINT8 costumeTypeId;                //0x9144A4  0x72D4
        UINT8 wingsTypeId;                  //0x9144A5  0x72D5
        PAD(40);
        CharArray<21> charName;             //0x9144CE  0x72FE
        PAD(1);
        WindowType windowType;              //0x9144E4  0x7314
        ULONG npcId1;                       //0x9144E8  0x7318
        ULONG npcId2;                       //0x9144EC  0x731C
        UINT32 npcIcon;                     //0x9144F0  0x7320
        Array<CItem, 256> npcShopItems;     //0x9144F4  0x7324
        UINT8 npcShopItemCount;             //0x9178F4  0xA724
        PAD(3);
        Warehouse warehouse;                //0x9178F8  0xA728
        PAD(4);
        Array<CItem, 8> exchangeItems;      //0x91A9BC  0xD7EC
        Array<CItem, 8> exchangeUserItems;  //0x91AB5C  0xD98C
        Array<ExcItem, 8> exchangeItems2;   //0x91ACFC  0xDB2C
        BOOL exchangeAccepted;              //0x91AD14  0xDB44
        BOOL exchangeUserAccepted;          //0x91AD18  0xDB48
        BOOL exchangeConfirmed;             //0x91AD1C  0xDB4C
        BOOL exchangeUserConfirmed;         //0x91AD20  0xDB50
        UINT32 exchangeMoney;               //0x91AD24  0xDB54
        UINT32 exchangeUserMoney;           //0x91AD28  0xDB58
        ULONG exchangeUserId;               //0x91AD2C  0xDB5C
        BOOL questCompleted;                //0x91AD30  0xDB60
        UINT8 questMessageIndex;            //0x91AD34  0xDB64
        PAD(1);
        UINT16 questId;                     //0x91AD36  0xDB66
        UINT8 questResultMessageIndex;      //0x91AD38  0xDB68
        PAD(3);
        // effect 39,44,45,50,99
        UINT8 itemEffectBag;                //0x91AD3C  0xDB6C
        UINT8 itemEffectSlot;               //0x91AD3D  0xDB6D
        UINT8 townMoveScrollBag;            //0x91AD3E  0xDB6E
        UINT8 townMoveScrollSlot;           //0x91AD3F  0xDB6F
        UINT32 npcTypeId;                   //0x91AD40  0xDB70
        NpcType32 npcType;                  //0x91AD44  0xDB74
        PAD(26802528);
        CVector<SkillData> skillData;            //0x22AA6A8  0x199D518
        CVector<QuestData> questData;            //0x22AA6C0  0x199D530
        // 0x22AA6D8  0x199D548
        CVector<QuestFinishData> questFinishData;
        CMap<ULONG, SetSkillData> setSkillData;  //0x22AA6F0  0x199D560
        CVector<PartyData> partyData;            //0x22AA704  0x199D574
        CMap<ULONG, PartyData> partyData2;       //0x22AA71C  0x199D58C
        RaidParty raidParty;                     //0x22AA730  0x199D5A0
        // 0x22AA74C  0x199D5BC
        PAD(28);
        CVector<GuildUserData> guildUserData;    //0x22AA768  0x199D598
        // 0x22AA780  0x199D5B0
        CVector<GuildJoinUserData> guildJoinUserData;
        CVector<FriendData> friendData;          //0x22AA798  0x199D5C8
        CVector<BlockData> blockData;            //0x22AA7B0  0x199D5E0
        CVector<FindPartyData> findPartyData;    //0x22AA7C8  0x199D5F8
        CMap<ULONG, ObeliskData> obeliskData;    //0x22AA7E0  0x199D610
        ULONG partyLeaderId;                     //0x22AA7F4  0x199D624
        BOOL isPartyMember;                      //0x22AA7F8  0x199D628
        BOOL isUnionMember;                      //0x22AA7FC  0x199D62C
        PAD(20);
        UINT8 attackSpeed;                       //0x22AA814  0x199D644
        UINT8 moveSpeed;                         //0x22AA815  0x199D645
        Country country2;                        //0x22AA816  0x199D646
        Grow maxGrow;                            //0x22AA817  0x199D647
        Array<QuickSlot, 50> quickSlots;         //0x22AA818  0x199D648
        UINT8 quickSlot1Bag;                     //0x22AAB38  0x199D968
        UINT8 quickSlot2Bag;                     //0x22AAB39  0x199D969
        PAD(2);
        Array<QuickSlot, 24> revolver;           //0x22AAB3C  0x199D96C
        // 0x22AACBC  0x199DAEC
        PAD(20);
        QuickSlot quickPotionZ;                  //0x22AACD0  0x199DB00
        QuickSlot quickPotionX;                  //0x22AACE0  0x199DB10
        // 0x22AACF0  0x199DB20
        PAD(1);
        UINT8 interpretationLv;                  //0x22AACF1  0x199DB21
        UINT8 backpackUpgradeLv;                 //0x22AACF2  0x199DB22
        PAD(329);
        UINT32 kills;                            //0x22AAE3C  0x199DC6C
        UINT32 deaths;                           //0x22AAE40  0x199DC70
        PAD(2414);
        UINT8 guildAuthLv;                       //0x22AB7B2  0x199E5E2
        PAD(1);
        char* guildName;                         //0x22AB7B4  0x199E5E4
        CharArray<128> textBuffer;               //0x22AB7B8  0x199E5E8
        // 0x22AB838  0x199E668
        PAD(36);
        UINT32 points;                           //0x22AB85C  0x199E68C
        PAD(34);
        Bank bank;                               //0x22AB882  0x199E6B2
        StoredPointItems storedPointItems;       //0x22ABB52  0x199E982
        // 0x22ABE22  0x199EC52
        PAD(1970);
        ULONG npcId3;                            //0x22AC5D4  0x199F404
        PAD(12548);
        CMap<ULONG, GuildData2> guildData2;      //0x22AF6DC  0x19A250C
        // 0x22AF6F0  0x19A2520
        PAD(24);
        CVector<GuildNpcData> guildNpcData;      //0x22AF708  0x19A2538
        // 0x22AF720  0x19A2550
        PAD(2792);
        // 0x19A3038

        static GuildUserData* GetGuildUserData(ULONG charId);
    };
    #pragma pack(pop)

    static_assert(sizeof(CPlayerData) == 0x19A3038);
    static auto g_pPlayerData = (CPlayerData*)0x90D1D0;
}
