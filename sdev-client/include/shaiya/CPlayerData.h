#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/PartyTypes.h>
#include <shaiya/include/common/Sex.h>
#include <shaiya/include/common/UserTypes.h>
#include "common.h"
#include "BillingItemInfo.h"
#include "CItem.h"
#include "CMap.h"
#include "CQuickPotionSlot.h"
#include "CUnionPartyInfo.h"
#include "CVector.h"
#include "ExcItem.h"
#include "TargetType.h"
#include "WindowType.h"

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
    using Bank = Array<BillingItemInfo, 240>;
    using StoredPointItems = Bank;

    #pragma pack(push, 1)
    // 004F1980 ctor
    struct CPlayerData
    {
        uint32_t clientVersion;               //0x90D1D0  0x00
        AuthStatus authStatus;                //0x90D1D4  0x04
        PAD(3);
        bool32_t isAdmin;                     //0x90D1D8  0x08
        uint32_t money;                       //0x90D1DC  0x0C
        uint32_t bankMoney;                   //0x90D1E0  0x10
        uint32_t level;                       //0x90D1E4  0x14
        int32_t maxHealth;                    //0x90D1E8  0x18
        int32_t maxMana;                      //0x90D1EC  0x1C
        int32_t maxStamina;                   //0x90D1F0  0x20
        uint32_t exp;                         //0x90D1F4  0x24
        uint32_t reqExpToLvDown;              //0x90D1F8  0x28
        uint32_t reqExpToLvUp;                //0x90D1FC  0x2C
        uint16_t strength;                    //0x90D200  0x30
        uint16_t intelligence;                //0x90D202  0x32
        uint16_t dexterity;                   //0x90D204  0x34
        uint16_t wisdom;                      //0x90D206  0x36
        uint16_t reaction;                    //0x90D208  0x38
        uint16_t luck;                        //0x90D20A  0x3A
        PAD(160);
        uint16_t statusPoints;                //0x90D2AC  0xDC
        uint16_t skillPoints;                 //0x90D2AE  0xDE
        int32_t abilityStrength;              //0x90D2B0  0xE0
        int32_t abilityReaction;              //0x90D2B4  0xE4
        int32_t abilityIntelligence;          //0x90D2B8  0xE8
        int32_t abilityWisdom;                //0x90D2BC  0xEC
        int32_t abilityDexterity;             //0x90D2C0  0xF0
        int32_t abilityLuck;                  //0x90D2C4  0xF4
        int32_t minAttackPower;               //0x90D2C8  0xF8
        int32_t maxAttackPower;               //0x90D2CC  0xFC
        int32_t minMagicPower;                //0x90D2D0  0x100
        int32_t maxMagicPower;                //0x90D2D4  0x104
        int32_t defense;                      //0x90D2D8  0x108
        int32_t resistance;                   //0x90D2DC  0x10C
        PAD(4096);                            //0x90D2E0  0x110
        uint16_t mapId;                       //0x90E2E0  0x1110
        PAD(2);
        D3DVECTOR rebirthPos;                 //0x90E2E4  0x1114
        uint16_t direction;                   //0x90E2F0  0x1120
        PAD(2);
        uint32_t charId;                      //0x90E2F4  0x1124
        Inventory inventory;                  //0x90E2F8  0x1128
        Array<CItem, 256> bag250;             //0x910038  0x2E68
        Array<uint16_t, 21> weaponStep;       //0x913438  0x6268
        PAD(2);
        TargetType targetType;                //0x913460  0x6294
        Country country;                      //0x913468  0x6298
        Grow grow;                            //0x913469  0x6299
        PAD(6);
        uint8_t hair;                         //0x913470  0x62A0
        uint8_t face;                         //0x913471  0x62A1
        uint8_t size;                         //0x913472  0x62A2
        Job job;                              //0x913473  0x62A3
        PAD(4096);                            //0x913474  0x62A4
        Sex sex;                              //0x914474  0x72A4
        PAD(3);
        int32_t health;                       //0x914478  0x72A8
        int32_t mana;                         //0x91447C  0x72AC
        int32_t stamina;                      //0x914480  0x72B0
        uint8_t helmetType;                   //0x914484  0x72B4
        uint8_t upperType;                    //0x914485  0x72B5
        uint8_t lowerType;                    //0x914486  0x72B6
        uint8_t handsType;                    //0x914487  0x72B7
        uint8_t bootsType;                    //0x914488  0x72B8
        uint8_t weaponType;                   //0x914489  0x72B9
        uint8_t shieldType;                   //0x91448A  0x72BA
        uint8_t cloakType;                    //0x91448B  0x72BB
        uint8_t necklaceType;                 //0x91448C  0x72BC
        uint8_t ring1Type;                    //0x91448D  0x72BD
        uint8_t ring2Type;                    //0x91448E  0x72BE
        uint8_t bracelet1Type;                //0x91448F  0x72BF
        uint8_t bracelet2Type;                //0x914490  0x72C0
        uint8_t vehicleType;                  //0x914491  0x72C1
        uint8_t petType;                      //0x914492  0x72C2
        uint8_t costumeType;                  //0x914493  0x72C3
        uint8_t wingsType;                    //0x914494  0x72C4
        uint8_t helmetTypeId;                 //0x914495  0x72C5
        uint8_t upperTypeId;                  //0x914496  0x72C6
        uint8_t lowerTypeId;                  //0x914497  0x72C7
        uint8_t handsTypeId;                  //0x914498  0x72C8
        uint8_t bootsTypeId;                  //0x914499  0x72C9
        uint8_t weaponTypeId;                 //0x91449A  0x72CA
        uint8_t shieldTypeId;                 //0x91449B  0x72CB
        uint8_t cloakTypeId;                  //0x91449C  0x72CC
        uint8_t necklaceTypeId;               //0x91449D  0x72CD
        uint8_t ring1TypeId;                  //0x91449E  0x72CE
        uint8_t ring2TypeId;                  //0x91449F  0x72CF
        uint8_t bracelet1TypeId;              //0x9144A0  0x72D0
        uint8_t bracelet2TypeId;              //0x9144A1  0x72D1
        uint8_t vehicleTypeId;                //0x9144A2  0x72D2
        uint8_t petTypeId;                    //0x9144A3  0x72D3
        uint8_t costumeTypeId;                //0x9144A4  0x72D4
        uint8_t wingsTypeId;                  //0x9144A5  0x72D5
        PAD(40);
        String<21> charName;                  //0x9144CE  0x72FE
        PAD(1);
        WindowType windowType;                //0x9144E4  0x7314
        uint32_t npcId1;                      //0x9144E8  0x7318
        uint32_t npcId2;                      //0x9144EC  0x731C
        uint32_t npcIcon;                     //0x9144F0  0x7320
        Array<CItem, 256> npcShopItems;       //0x9144F4  0x7324
        uint8_t npcShopItemCount;             //0x9178F4  0xA724
        PAD(3);
        Warehouse warehouse;                  //0x9178F8  0xA728
        PAD(4);
        Array<CItem, 8> exchangeItems;        //0x91A9BC  0xD7EC
        Array<CItem, 8> exchangeUserItems;    //0x91AB5C  0xD98C
        Array<ExcItem, 8> exchangeItems2;     //0x91ACFC  0xDB2C
        bool32_t exchangeAccepted;            //0x91AD14  0xDB44
        bool32_t exchangeUserAccepted;        //0x91AD18  0xDB48
        bool32_t exchangeConfirmed;           //0x91AD1C  0xDB4C
        bool32_t exchangeUserConfirmed;       //0x91AD20  0xDB50
        uint32_t exchangeMoney;               //0x91AD24  0xDB54
        uint32_t exchangeUserMoney;           //0x91AD28  0xDB58
        uint32_t exchangeUserId;              //0x91AD2C  0xDB5C
        bool32_t questCompleted;              //0x91AD30  0xDB60
        uint8_t questMessageIndex;            //0x91AD34  0xDB64
        PAD(1);
        uint16_t questId;                     //0x91AD36  0xDB66
        uint8_t questResultMessageIndex;      //0x91AD38  0xDB68
        PAD(3);
        // effect 39,44,45,50,99
        uint8_t itemEffectBag;                //0x91AD3C  0xDB6C
        uint8_t itemEffectSlot;               //0x91AD3D  0xDB6D
        uint8_t townMoveScrollBag;            //0x91AD3E  0xDB6E
        uint8_t townMoveScrollSlot;           //0x91AD3F  0xDB6F
        uint32_t npcTypeId;                   //0x91AD40  0xDB70
        uint32_t npcType;                     //0x91AD44  0xDB74
        PAD(26802528);
        CVector<SkillData> skillData;               //0x22AA6A8  0x199D518
        CVector<QuestData> questData;               //0x22AA6C0  0x199D530
        // 0x22AA6D8  0x199D548
        CVector<QuestFinishData> questFinishData;
        CMap<uint32_t, SetSkillData> setSkillData;  //0x22AA6F0  0x199D560
        CVector<PartyData> partyData;               //0x22AA704  0x199D574
        CMap<uint32_t, PartyData> partyData2;       //0x22AA71C  0x199D58C
        CUnionPartyInfo unionInfo;                  //0x22AA730  0x199D5A0
        // 0x22AA74C  0x199D5BC
        PAD(28);
        CVector<GuildUserData> guildUserData;       //0x22AA768  0x199D598
        // 0x22AA780  0x199D5B0
        CVector<GuildJoinUserData> guildJoinUserData;
        CVector<FriendData> friendData;             //0x22AA798  0x199D5C8
        CVector<BlockData> blockData;               //0x22AA7B0  0x199D5E0
        CVector<FindPartyData> findPartyData;       //0x22AA7C8  0x199D5F8
        CMap<uint32_t, ObeliskData> obeliskData;    //0x22AA7E0  0x199D610
        uint32_t partyBossId;                       //0x22AA7F4  0x199D624
        bool32_t isPartyUser;                       //0x22AA7F8  0x199D628
        bool32_t isUnionUser;                       //0x22AA7FC  0x199D62C
        PAD(20);
        uint8_t attackSpeed;                        //0x22AA814  0x199D644
        uint8_t moveSpeed;                          //0x22AA815  0x199D645
        Country country2;                           //0x22AA816  0x199D646
        Grow maxGrow;                               //0x22AA817  0x199D647
        Array<CQuickPotionSlot, 50> quickSlots;     //0x22AA818  0x199D648
        uint8_t quickSlot1Bag;                      //0x22AAB38  0x199D968
        uint8_t quickSlot2Bag;                      //0x22AAB39  0x199D969
        PAD(2);
        Array<CQuickPotionSlot, 24> revolver;       //0x22AAB3C  0x199D96C
        // 0x22AACBC  0x199DAEC
        PAD(20);
        CQuickPotionSlot quickPotionZ;              //0x22AACD0  0x199DB00
        CQuickPotionSlot quickPotionX;              //0x22AACE0  0x199DB10
        // 0x22AACF0  0x199DB20
        PAD(1);
        uint8_t interpretationLv;                   //0x22AACF1  0x199DB21
        uint8_t bagUpgradeLv;                       //0x22AACF2  0x199DB22
        PAD(329);
        uint32_t kills;                             //0x22AAE3C  0x199DC6C
        uint32_t deaths;                            //0x22AAE40  0x199DC70
        PAD(2414);
        uint8_t guildAuthLv;                        //0x22AB7B2  0x199E5E2
        PAD(1);
        char* guildName;                            //0x22AB7B4  0x199E5E4
        Array<char, 128> textBuffer;                //0x22AB7B8  0x199E5E8
        // 0x22AB838  0x199E668
        PAD(36);
        uint32_t points;                            //0x22AB85C  0x199E68C
        PAD(34);
        Bank bank;                                  //0x22AB882  0x199E6B2
        StoredPointItems storedPointItems;          //0x22ABB52  0x199E982
        // 0x22ABE22  0x199EC52
        PAD(1970);
        uint32_t npcId3;                            //0x22AC5D4  0x199F404
        PAD(12548);
        CMap<uint32_t, GuildData2> guildData2;      //0x22AF6DC  0x19A250C
        // 0x22AF6F0  0x19A2520
        PAD(24);
        CVector<GuildNpcData> guildNpcData;         //0x22AF708  0x19A2538
        // 0x22AF720  0x19A2550
        PAD(2042);
        SYSTEMTIME serverTime;                      //0x22AFF1A  0x19A2D4A
        // 0x22AFF2A  0x19A2D5A
        PAD(6);
        LARGE_INTEGER unknownSeconds;               //0x22AFF30  0x19A2D60
        LARGE_INTEGER serverTimeOffsetSeconds;      //0x22AFF38  0x19A2D68
        // 0x22AFF40  0x19A2D70
        PAD(712);
        // 0x19A3038

        static int GetItemRealType(int itemType);
        static GuildUserData* GetGuildUserData(unsigned charId);
    };
    #pragma pack(pop)

    static_assert(sizeof(CPlayerData) == 0x19A3038);
    static auto g_pPlayerData = (CPlayerData*)0x90D1D0;
}
