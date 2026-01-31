#include <array>
#include <util/util.h>
#include <shaiya/include/common/ItemList.h>
#include <shaiya/include/common/ItemSlot.h>
#include <shaiya/include/common/ItemType.h>
#include <shaiya/include/network/game/outgoing/0300.h>
#include "include/main.h"
#include "include/shaiya/CItem.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/ItemInfo.h"
#include "include/shaiya/SConnection.h"
#include "include/shaiya/Synergy.h"
using namespace shaiya;

namespace user_equipment
{
    bool enable_slot(CUser* user, CItem* item, ItemInfo* itemInfo, int slot)
    {
        auto itemType = static_cast<ItemType>(itemInfo->type);
        auto realType = itemInfo->realType;

        switch (slot)
        {
        case ItemSlot::Helmet:
            return realType == RealType::Helmet;
        case ItemSlot::UpperArmor:
            return realType == RealType::UpperArmor;
        case ItemSlot::LowerArmor:
            return realType == RealType::LowerArmor;
        case ItemSlot::Gloves:
            return realType == RealType::Gloves;
        case ItemSlot::Boots:
            return realType == RealType::Boots;
        case ItemSlot::Weapon:
        {
            if (CItem::IsWeapon(item))
            {
                if (!user->inventory[0][ItemSlot::Shield])
                    return true;

                if (CItem::IsOneHandWeapon(item))
                    return true;
            }

            return false;
        }
        case ItemSlot::Shield:
        {
            if (realType == RealType::Shield)
            {
                auto& item = user->inventory[0][ItemSlot::Weapon];
                if (!item)
                    return true;

                if (CItem::IsOneHandWeapon(item))
                    return true;
            }

            return false;
        }
        case ItemSlot::Cloak:
            return realType == RealType::Cloak;
        case ItemSlot::Necklace:
            return realType == RealType::Necklace;
        case ItemSlot::Ring1:
        case ItemSlot::Ring2:
            return realType == RealType::Ring;
        case ItemSlot::Bracelet1:
        case ItemSlot::Bracelet2:
            return realType == RealType::Bracelet;
        case ItemSlot::Vehicle:
            return itemType == ItemType::Vehicle;
        case ItemSlot::Pet:
            return itemType == ItemType::Pet;
        case ItemSlot::Costume:
            return itemType == ItemType::Costume;
        case ItemSlot::Wings:
            return itemType == ItemType::Wings;
        default:
            break;
        }

        return false;
    }

    void init(CUser* user)
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

            if (slot < ItemSlot::Vehicle)
                user->itemQualityEx[slot] = item->quality;

            CUser::ItemEquipmentAdd(user, item, slot);
        }

        user->initStatusFlag = false;
        CUser::SetAttack(user);
    }

    /// <summary>
    /// Sends packet 0x307 (6.4) to the user.
    /// </summary>
    void send_0x307(CUser* user, CUser* target)
    {
        GameGetInfoUserItemsOutgoing<GetInfoItemUnit_EP5, 17> outgoing{};
        outgoing.itemCount = 0;

        for (int slot = 0; slot < 17; ++slot)
        {
            auto& item = target->inventory[0][slot];
            if (!item)
                continue;

            if (slot < ItemSlot::Wings)
            {
                GetInfoItemUnit_EP5 item0307{};
                item0307.slot = slot;
                item0307.type = item->type;
                item0307.typeId = item->typeId;

                if (slot < ItemSlot::Vehicle)
                    item0307.quality = item->quality;

                item0307.gems = item->gems;
                item0307.craftName = item->craftName;

                outgoing.itemList[outgoing.itemCount] = item0307;
                ++outgoing.itemCount;
            }
        }

        int length = outgoing.baseLength + (outgoing.itemCount * sizeof(GetInfoItemUnit_EP5));
        SConnection::Send(user, &outgoing, length);
    }

    void synergy_hook(CUser* user)
    {
        auto it = g_itemSetSynergies.find(user->id);
        if (it != g_itemSetSynergies.end())
            Synergy::subSynergies(user, it->second);

        std::vector<ItemSetSynergy> synergies;
        Synergy::getSynergies(user, synergies);

        Synergy::addSynergies(user, synergies);
        g_itemSetSynergies[user->id] = synergies;
    }
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
        call user_equipment::enable_slot
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
        call user_equipment::init
        add esp,0x4

        popad

        jmp u0x46153E
    }
}

unsigned u0x477E02 = 0x477E02;
void __declspec(naked) naked_0x477D4F()
{
    __asm
    {
        pushad

        push eax // target
        push edi // user
        call user_equipment::send_0x307
        add esp,0x8

        popad

        jmp u0x477E02
    }
}

unsigned u0x461675 = 0x461675;
void __declspec(naked) naked_0x46166E()
{
    __asm
    {
        pushad

        push edi // user
        call user_equipment::synergy_hook
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
        call user_equipment::synergy_hook
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
    // CUser::PacketGetInfo case 0x307
    util::detour((void*)0x477D4F, naked_0x477D4F, 7);
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

    // user->itemQualityLv[0] (0x199 to 0x62A0)
    std::array<uint8_t, 2> a00{ 0xA0, 0x62 };
    
    // CUser::ItemEquipmentAdd
    util::write_memory((void*)0x46166A, &a00, 2);
    util::write_memory((void*)0x4617FB, &a00, 2);
    util::write_memory((void*)0x46194C, &a00, 2);
    util::write_memory((void*)0x461962, &a00, 2);
    // CUser::ItemEquipmentRem
    util::write_memory((void*)0x461ED4, &a00, 2);
    util::write_memory((void*)0x461EEA, &a00, 2);
    util::write_memory((void*)0x462662, &a00, 2);
    // CUser::ItemEquipmentAttackAdd
    util::write_memory((void*)0x462DD9, &a00, 2);
    util::write_memory((void*)0x462DEF, &a00, 2);
    util::write_memory((void*)0x462E51, &a00, 2);
    util::write_memory((void*)0x462E67, &a00, 2);
    util::write_memory((void*)0x462E8C, &a00, 2);
    util::write_memory((void*)0x462EA2, &a00, 2);
    // CUser::QualityDec
    util::write_memory((void*)0x4682DE, &a00, 2);
    util::write_memory((void*)0x468305, &a00, 2);
    // CUser::ItemGeMRemoveAll
    util::write_memory((void*)0x4703CB, &a00, 2);
    util::write_memory((void*)0x4703E1, &a00, 2);
    util::write_memory((void*)0x470428, &a00, 2);
    util::write_memory((void*)0x471438, &a00, 2);
    util::write_memory((void*)0x471450, &a00, 2);
    util::write_memory((void*)0x471497, &a00, 2);
    util::write_memory((void*)0x471E3A, &a00, 2);
    util::write_memory((void*)0x471E5F, &a00, 2);
    util::write_memory((void*)0x4720AC, &a00, 2);
    util::write_memory((void*)0x4720E7, &a00, 2);
    util::write_memory((void*)0x47395E, &a00, 2);
    util::write_memory((void*)0x47398F, &a00, 2);

    // user->itemQuality[0] (0x1A6 to 0x62B8)
    std::array<uint8_t, 2> a01{ 0xB8, 0x62 };

    // CUser::ItemDropByUserDeath
    util::write_memory((void*)0x46754C, &a01, 2);
    util::write_memory((void*)0x467587, &a01, 2);
    // CUser::ItemDropByMobDeath
    util::write_memory((void*)0x46798C, &a01, 2);
    util::write_memory((void*)0x4679C7, &a01, 2);
    // CUser::ItemBagToBag
    util::write_memory((void*)0x468665, &a01, 2);
    util::write_memory((void*)0x4686B6, &a01, 2);
    util::write_memory((void*)0x4687CB, &a01, 2);
    util::write_memory((void*)0x468813, &a01, 2);
    util::write_memory((void*)0x468996, &a01, 2);
    util::write_memory((void*)0x468A6A, &a01, 2);
    util::write_memory((void*)0x468ABA, &a01, 2);
    // CUser::ItemDrop
    util::write_memory((void*)0x469C64, &a01, 2);
    util::write_memory((void*)0x469CA4, &a01, 2);
    // CUser::ItemRemove
    util::write_memory((void*)0x46C2DC, &a01, 2);
    util::write_memory((void*)0x46C317, &a01, 2);
    // CUser::ItemRemoveFree
    util::write_memory((void*)0x46C50C, &a01, 2);
    util::write_memory((void*)0x46C547, &a01, 2);
    // CUser::ItemLapisianAdd
    util::write_memory((void*)0x46D3D8, &a01, 2);
    util::write_memory((void*)0x46D413, &a01, 2);
    // CUser::ItemRemake
    util::write_memory((void*)0x46DB52, &a01, 2);
    util::write_memory((void*)0x46DB99, &a01, 2);
    // CUser::ItemGemAdd
    util::write_memory((void*)0x46EDE7, &a01, 2);
    util::write_memory((void*)0x46EE22, &a01, 2);
    // CUser::ItemGemRemoveAll
    util::write_memory((void*)0x470A32, &a01, 2);
    util::write_memory((void*)0x470A78, &a01, 2);
    // CUser::ItemGemRemovePos
    util::write_memory((void*)0x4718B1, &a01, 2);
    util::write_memory((void*)0x4718F1, &a01, 2);
    // CUser::ItemRepair
    util::write_memory((void*)0x471DC5, &a01, 2);
    util::write_memory((void*)0x472092, &a01, 2);
    // CUser::ItemUse
    util::write_memory((void*)0x473912, &a01, 2);
    // CUser::SendDBAgentCharGetInfo
    util::write_memory((void*)0x47AE7B, &a01, 2);

    // user->itemQualityLv[5] (0x19E to 0x62A5)
    std::array<uint8_t, 2> a02{ 0xA5, 0x62 };

    util::write_memory((void*)0x4621F0, &a02, 2);
    util::write_memory((void*)0x462205, &a02, 2);
    util::write_memory((void*)0x4732C0, &a02, 2);
    util::write_memory((void*)0x4732ED, &a02, 2);
}
