#pragma once
#include <shaiya/common.h>
#include <shaiya/include/CGameData.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CraftName
    {
        char strength[2];
        char dexterity[2];
        char reaction[2];
        char intelligence[2];
        char wisdom[2];
        char luck[2];
        char health[2];
        char mana[2];
        char stamina[2];
        char enchantStep[2];
        char nullByte;
    };

    enum struct MakeType : char
    {
        B = 66,
        C,
        D,
        Q = 81,
        S = 83,
        X = 88
    };

    struct CItem
    {
        PAD(48);
        // 0x30
        CGameData::ItemInfo* itemInfo;
        PAD(4);
        UINT64 uniqueId;           //0x38
        UINT8 type;                //0x40
        UINT8 typeId;              //0x41
        UINT8 count;               //0x42
        PAD(1);
        UINT16 quality;            //0x44
        // or CloakBadge
        UINT8 gems[6];             //0x46
        CraftName craftName;       //0x4C
        PAD(3);
        TickCount makeTime;        //0x64
        MakeType makeType;         //0x68
        PAD(27);
        UINT16 craftStrength;      //0x84
        UINT16 craftDexterity;     //0x86
        UINT16 craftReaction;      //0x88
        UINT16 craftIntelligence;  //0x8A
        UINT16 craftWisdom;        //0x8C
        UINT16 craftLuck;          //0x8E
        // value * 100
        UINT16 craftHealth;        //0x90
        // value * 100
        UINT16 craftMana;          //0x92
        // value * 100
        UINT16 craftStamina;       //0x94
        UINT16 craftAttackPower;   //0x96
        UINT16 craftAbsorption;    //0x98
        PAD(14);
        // 0xA8

        static char GetEnchantStep(CItem* item/*edx*/);
        /*itemInfo->itemRType == 22 or 23 or 25*/
        static bool IsAccessory(CItem* item/*eax*/);
        /*itemInfo->itemRType >= 1 and <= 25*/
        static bool IsEquipment(CItem* item/*eax*/);
        /*itemInfo->type == 43*/
        static bool IsEtin(CItem* item/*eax*/);
        /*itemInfo->itemRType == 27*/
        static bool IsQuest(CItem* item/*eax*/);
        /*itemInfo->itemRType == 1 or 3 or 7 or 9*/
        static bool IsOneHandWeapon(CItem* item/*eax*/);
        /*itemInfo->itemRType == 19*/
        static bool IsShield(CItem* item/*eax*/);
        /*itemInfo->itemRType >= 1 and <= 15*/
        static bool IsWeapon(CItem* item/*eax*/);
        static void ReGenerationCraftExpansion(CItem* item/*esi*/, BOOL compose);
    };
    #pragma pack(pop)
}
