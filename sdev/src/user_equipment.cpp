#include <util/util.h>
#include <shaiya/include/common/ItemEquipment.h>
#include <shaiya/include/common/ItemList.h>
#include <shaiya/include/common/ItemType.h>
#include "include/main.h"
#include "include/shaiya/CItem.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/ItemInfo.h"
#include "include/shaiya/SConnection.h"
#include "include/shaiya/Synergy.h"
using namespace shaiya;

/// <summary>
/// Enables additional equipment slots.
/// </summary>
bool hook_0x468385(CUser* user, CItem* item, ItemInfo* itemInfo, int slot)
{
    auto itemType = static_cast<ItemType>(itemInfo->type);
    auto realType = itemInfo->realType;

    switch (slot)
    {
    case ItemEquipment::Helmet:
        return realType == RealType::Helmet;
    case ItemEquipment::UpperArmor:
        return realType == RealType::UpperArmor;
    case ItemEquipment::LowerArmor:
        return realType == RealType::LowerArmor;
    case ItemEquipment::Gloves:
        return realType == RealType::Gloves;
    case ItemEquipment::Boots:
        return realType == RealType::Boots;
    case ItemEquipment::Weapon:
    {
        if (CItem::IsWeapon(item))
        {
            if (!user->inventory[0][6])
                return true;

            if (CItem::IsOneHandWeapon(item))
                return true;
        }

        return false;
    }
    case ItemEquipment::Shield:
    {
        if (realType == RealType::Shield)
        {
            auto& weapon = user->inventory[0][5];
            if (!weapon)
                return true;

            if (CItem::IsOneHandWeapon(weapon))
                return true;
        }

        return false;
    }
    case ItemEquipment::Cloak:
        return realType == RealType::Cloak;
    case ItemEquipment::Necklace:
        return realType == RealType::Necklace;
    case ItemEquipment::Ring1:
    case ItemEquipment::Ring2:
        return realType == RealType::Ring;
    case ItemEquipment::Bracelet1:
    case ItemEquipment::Bracelet2:
        return realType == RealType::Bracelet;
    case ItemEquipment::Vehicle:
        return itemType == ItemType::Vehicle;
    case ItemEquipment::Pet:
        return itemType == ItemType::Pet;
    case ItemEquipment::Costume:
        return itemType == ItemType::Costume;
    case ItemEquipment::Wings:
        return itemType == ItemType::Wings;
    default:
        break;
    }

    return false;
}

void hook_0x4614E3(CUser* user)
{
    // Clear the synergy vector because InitEquipment 
    // removes the effects
    auto it = g_itemSetSynergies.find(user->id);
    if (it != g_itemSetSynergies.end())
        it->second.clear();

    user->initStatusFlag = true;

    for (int slot = 0; slot < 17; ++slot)
    {
        auto& item = user->inventory[0][slot];
        if (!item)
            continue;

        if (slot < ItemEquipment::Vehicle)
            user->itemQualityEx[slot] = item->quality;

        CUser::ItemEquipmentAdd(user, item, slot);
    }

    user->initStatusFlag = false;
    CUser::SetAttack(user);
}

void hook_0x46166E(CUser* user)
{
    auto it = g_itemSetSynergies.find(user->id);
    if (it != g_itemSetSynergies.end())
        Synergy::subSynergies(user, it->second);

    std::vector<ItemSetSynergy> synergies;
    Synergy::getSynergies(user, synergies);

    Synergy::addSynergies(user, synergies);
    g_itemSetSynergies[user->id] = synergies;
}

void hook_0x461D43(CUser* user)
{
    auto it = g_itemSetSynergies.find(user->id);
    if (it != g_itemSetSynergies.end())
        Synergy::subSynergies(user, it->second);

    std::vector<ItemSetSynergy> synergies;
    Synergy::getSynergies(user, synergies);

    Synergy::addSynergies(user, synergies);
    g_itemSetSynergies[user->id] = synergies;
}

unsigned u0x46846B = 0x46846B;
unsigned u0x468535 = 0x468535;
void __declspec(naked) naked_0x468385()
{
    __asm
    {
        pushad

        push eax // slot
        push esi // itemInfo
        push ebx // item
        push edi // user
        call hook_0x468385
        add esp,0x10
        test al,al

        popad

        je _0x468535
        jmp u0x46846B

        _0x468535:
        jmp u0x468535
    }
}

unsigned u0x46153E = 0x46153E;
void __declspec(naked) naked_0x4614E3()
{
    __asm
    {
        pushad

        push esi // user
        call hook_0x4614E3
        add esp,0x4

        popad

        jmp u0x46153E
    }
}

unsigned u0x461675 = 0x461675;
void __declspec(naked) naked_0x46166E()
{
    __asm
    {
        pushad

        push edi // user
        call hook_0x46166E
        add esp,0x4

        popad

        // original
        cmp byte ptr [edi+0x5855],0x0
        jmp u0x461675
    }
}

unsigned u0x461D4A = 0x461D4A;
void __declspec(naked) naked_0x461D43()
{
    __asm
    {
        pushad

        push edi // user
        call hook_0x461D43
        add esp,0x4

        popad

        // original
        cmp byte ptr [edi+0x5855],0x0
        jmp u0x461D4A
    }
}

void hook::user_equipment()
{
    // CUser::EnableEquipment (switch)
    util::detour((void*)0x468385, naked_0x468385, 9);
    // CUser::InitEquipment
    util::detour((void*)0x4614E3, naked_0x4614E3, 6);
    // CUser::ItemEquipmentAdd
    util::detour((void*)0x46166E, naked_0x46166E, 7);
    // CUser::ItemEquipmentRem
    util::detour((void*)0x461D43, naked_0x461D43, 7);

    // CUser::InitEquipment (overload)
    util::write_memory((void*)0x4615B3, 17, 1);
    // CUser::ItemBagToBag
    util::write_memory((void*)0x46862D, 17, 1);
    util::write_memory((void*)0x468722, 17, 1);
    util::write_memory((void*)0x4688B0, 17, 1);
    util::write_memory((void*)0x468955, 17, 1);
    util::write_memory((void*)0x468A2B, 17, 1);
    util::write_memory((void*)0x468B5D, 17, 1);
    // CUser::ClearEquipment
    util::write_memory((void*)0x46BCCF, 17, 1);
    // CUser::PacketAdminCmdD (0xF901)
    // The client does not support more than 13 items (thanks, xarel)
    //util::write_memory((void*)0x482896, 17, 1);

    // Change 0x199 to 0x62A0 (&itemQualityLv)
    int x62A0 = 0x62A0;
    // CUser::ItemEquipmentAdd
    util::write_memory((void*)0x46166A, &x62A0, 4);
    util::write_memory((void*)0x4617FB, &x62A0, 4);
    util::write_memory((void*)0x46194C, &x62A0, 4);
    util::write_memory((void*)0x461962, &x62A0, 4);
    // CUser::ItemEquipmentRem
    util::write_memory((void*)0x461ED4, &x62A0, 4);
    util::write_memory((void*)0x461EEA, &x62A0, 4);
    util::write_memory((void*)0x462662, &x62A0, 4);
    // CUser::ItemEquipmentAttackAdd
    util::write_memory((void*)0x462DD9, &x62A0, 4);
    util::write_memory((void*)0x462DEF, &x62A0, 4);
    util::write_memory((void*)0x462E51, &x62A0, 4);
    util::write_memory((void*)0x462E67, &x62A0, 4);
    util::write_memory((void*)0x462E8C, &x62A0, 4);
    util::write_memory((void*)0x462EA2, &x62A0, 4);
    // CUser::QualityDec
    util::write_memory((void*)0x4682DE, &x62A0, 4);
    util::write_memory((void*)0x468305, &x62A0, 4);
    // CUser::ItemGemRemoveAll
    util::write_memory((void*)0x4703CB, &x62A0, 4);
    util::write_memory((void*)0x4703E1, &x62A0, 4);
    util::write_memory((void*)0x470428, &x62A0, 4);
    util::write_memory((void*)0x471438, &x62A0, 4);
    util::write_memory((void*)0x471450, &x62A0, 4);
    util::write_memory((void*)0x471497, &x62A0, 4);
    util::write_memory((void*)0x471E3A, &x62A0, 4);
    util::write_memory((void*)0x471E5F, &x62A0, 4);
    util::write_memory((void*)0x4720AC, &x62A0, 4);
    util::write_memory((void*)0x4720E7, &x62A0, 4);
    util::write_memory((void*)0x47395E, &x62A0, 4);
    util::write_memory((void*)0x47398F, &x62A0, 4);

    // Change 0x19E to 0x62A5 (weapon quality)
    int x62A5 = 0x62A5;
    // CUser::ItemEquipmentRem
    util::write_memory((void*)0x4621F0, &x62A5, 4);
    util::write_memory((void*)0x462205, &x62A5, 4);
    // CUser::ItemUse
    util::write_memory((void*)0x4732C0, &x62A5, 4);
    util::write_memory((void*)0x4732ED, &x62A5, 4);

    // Change 0x1A6 to 0x62B8 (&itemQuality)
    int x62B8 = 0x62B8;
    // CUser::ItemDropByUserDeath
    util::write_memory((void*)0x46754C, &x62B8, 4);
    util::write_memory((void*)0x467587, &x62B8, 4);
    // CUser::ItemDropByMobDeath
    util::write_memory((void*)0x46798C, &x62B8, 4);
    util::write_memory((void*)0x4679C7, &x62B8, 4);
    // CUser::ItemBagToBag
    util::write_memory((void*)0x468665, &x62B8, 4);
    util::write_memory((void*)0x4686B6, &x62B8, 4);
    util::write_memory((void*)0x4687CB, &x62B8, 4);
    util::write_memory((void*)0x468813, &x62B8, 4);
    util::write_memory((void*)0x468996, &x62B8, 4);
    util::write_memory((void*)0x468A6A, &x62B8, 4);
    util::write_memory((void*)0x468ABA, &x62B8, 4);
    // CUser::ItemDrop
    util::write_memory((void*)0x469C64, &x62B8, 4);
    util::write_memory((void*)0x469CA4, &x62B8, 4);
    // CUser::ItemRemove
    util::write_memory((void*)0x46C2DC, &x62B8, 4);
    util::write_memory((void*)0x46C317, &x62B8, 4);
    // CUser::ItemRemoveFree
    util::write_memory((void*)0x46C50C, &x62B8, 4);
    util::write_memory((void*)0x46C547, &x62B8, 4);
    // CUser::ItemLapisianAdd
    util::write_memory((void*)0x46D3D8, &x62B8, 4);
    util::write_memory((void*)0x46D413, &x62B8, 4);
    // CUser::ItemRemake
    util::write_memory((void*)0x46DB52, &x62B8, 4);
    util::write_memory((void*)0x46DB99, &x62B8, 4);
    // CUser::ItemGemAdd
    util::write_memory((void*)0x46EDE7, &x62B8, 4);
    util::write_memory((void*)0x46EE22, &x62B8, 4);
    // CUser::ItemGemRemoveAll
    util::write_memory((void*)0x470A32, &x62B8, 4);
    util::write_memory((void*)0x470A78, &x62B8, 4);
    // CUser::ItemGemRemovePos
    util::write_memory((void*)0x4718B1, &x62B8, 4);
    util::write_memory((void*)0x4718F1, &x62B8, 4);
    // CUser::ItemRepair
    util::write_memory((void*)0x471DC5, &x62B8, 4);
    util::write_memory((void*)0x472092, &x62B8, 4);
    // CUser::ItemUse
    util::write_memory((void*)0x473912, &x62B8, 4);
    // CUser::SendDBAgentCharGetInfo
    util::write_memory((void*)0x47AE7B, &x62B8, 4);
}
