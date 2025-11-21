#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>
#include <shaiya/include/common/MakeType.h>
#include "CObject.h"
#include "SNode.h"
#include "SVector.h"

namespace shaiya
{
    struct CZone;
    struct ItemInfo;

    enum struct ItemDropType : uint8_t
    {
        Mob = 1,
        User,
        Death
    };

    #pragma pack(push, 1)
    struct CItem : SNode, CObject
    {
        ItemInfo* info;              //0x30
        PAD(4);
        uint64_t uniqueId;           //0x38
        uint8_t type;                //0x40
        uint8_t typeId;              //0x41
        uint8_t count;               //0x42
        PAD(1);
        uint16_t quality;            //0x44
        Gems gems;                   //0x46
        CraftName craftName;         //0x4C
        PAD(3);
        time32_t makeTime;           //0x64
        MakeType makeType;           //0x68
        PAD(3);
        tick32_t removeTime;         //0x6C
        uint32_t userId;             //0x70
        uint32_t partyId;            //0x74
        ItemDropType dropType;       //0x78
        PAD(3);
        // e.g., mobId
        uint32_t dropId;             //0x7C
        uint32_t dropMoney;          //0x80
        uint16_t craftStrength;      //0x84
        uint16_t craftDexterity;     //0x86
        uint16_t craftReaction;      //0x88
        uint16_t craftIntelligence;  //0x8A
        uint16_t craftWisdom;        //0x8C
        uint16_t craftLuck;          //0x8E
        // value * 100
        uint16_t craftHealth;        //0x90
        // value * 100
        uint16_t craftMana;          //0x92
        // value * 100
        uint16_t craftStamina;       //0x94
        uint16_t craftAttackPower;   //0x96
        uint16_t craftAbsorption;    //0x98
        PAD(2);
        // cash shop
        uint32_t purchaseNumber;     //0x9C
        // 0xA0

        static char GetEnchantStep(CItem* item/*edx*/);
        static int GetGemCount(CItem* item/*ecx*/);
        static int GetGemSlot(CItem* item/*ecx*/);
        static void InitCraftExpansion(CItem* item/*eax*/);
        /*itemInfo->itemRealType == 22 or 23 or 25*/
        static bool IsAccessory(CItem* item/*eax*/);
        /*itemInfo->itemRealType >= 1 and <= 25*/
        static bool IsEquipment(CItem* item/*eax*/);
        static bool IsEquipSex(CItem* item/*eax*/, int sex/*ecx*/);
        /*itemInfo->type == 43*/
        static bool IsEtin(CItem* item/*eax*/);
        /*itemInfo->itemRealType == 27*/
        static bool IsQuest(CItem* item/*eax*/);
        /*itemInfo->itemRealType == 1 or 3 or 7 or 9*/
        static bool IsOneHandWeapon(CItem* item/*eax*/);
        /*itemInfo->itemRealType == 19*/
        static bool IsShield(CItem* item/*eax*/);
        /*itemInfo->itemRealType >= 1 and <= 15*/
        static bool IsWeapon(CItem* item/*eax*/);
        static void ReGenerationCraftExpansion(CItem* item/*esi*/, bool compose);
    };
    #pragma pack(pop)

    static_assert(sizeof(CItem) == 0xA0);
}
