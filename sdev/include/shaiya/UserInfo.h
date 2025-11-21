#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/Sex.h>
#include "BillingItemInfo.h"
#include "Quick.h"
#include "SSyncList.h"

namespace shaiya
{
    struct CItem;
    struct CQuest;
    struct CSkill;

    using Inventory = Array<Array<CItem*, 24>, 6>;
    using Warehouse = Array<CItem*, 240>;
    using Bank = Array<BillingItemInfo, 240>;

    template<size_t N>
    using ItemQuality = std::array<uint16_t, N>;

    template<size_t N>
    using ItemQualityLv = std::array<uint8_t, N>;

    #pragma pack(push, 1)
    struct UserInfo
    {
        uint32_t charId;                    //0x128
        uint8_t slot;                       //0x12C
        Country country;                    //0x12D
        Family family;                      //0x12E
        Grow grow;                          //0x12F
        Grow maxGrow;                       //0x130
        uint8_t hair;                       //0x131
        uint8_t face;                       //0x132
        uint8_t size;                       //0x133
        Job job;                            //0x134
        Sex sex;                            //0x135
        uint16_t level;                     //0x136
        uint16_t statusPoints;              //0x138
        uint16_t skillPoints;               //0x13A
        uint32_t exp;                       //0x13C
        uint32_t money;                     //0x140
        uint32_t bankMoney;                 //0x144
        uint32_t kills;                     //0x148
        uint32_t deaths;                    //0x14C
        uint32_t wins;                      //0x150
        uint32_t losses;                    //0x154
        uint32_t killLv;                    //0x158
        uint32_t deathLv;                   //0x15C
        uint16_t mapId;                     //0x160
        uint16_t direction;                 //0x162
        uint16_t honor;                     //0x164
        int16_t vg;                         //0x166
        uint8_t cg;                         //0x168
        uint8_t og;                         //0x169
        uint8_t ig;                         //0x16A
        PAD(1);
        uint16_t strength;                  //0x16C
        uint16_t dexterity;                 //0x16E
        uint16_t intelligence;              //0x170
        uint16_t wisdom;                    //0x172
        uint16_t reaction;                  //0x174
        uint16_t luck;                      //0x176
        int32_t maxHealth;                  //0x178
        int32_t maxMana;                    //0x17C
        int32_t maxStamina;                 //0x180
        String<21> charName;                //0x184
        ItemQualityLv<13> itemQualityLv;    //0x199
        ItemQuality<13> itemQuality;        //0x1A6
        Inventory inventory;                //0x1C0
        Warehouse warehouse;                //0x400
        Bank bank;                          //0x7C0
        SSyncList<CSkill> applySkills;      //0xA90
        int32_t skillCount;                 //0xABC
        Array<CSkill*, 256> skills;         //0xAC0
        int32_t quickSlotCount;             //0xEC0
        Array<Quick, 128> quickSlots;       //0xEC4
        SSyncList<CQuest> completedQuests;  //0x11C4
        SSyncList<CQuest> quests;           //0x11F0
        // 0x121C
    };
    #pragma pack(pop)

    static_assert(sizeof(UserInfo) == 0x10F4);
}
