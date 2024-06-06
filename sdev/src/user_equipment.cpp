#include <array>
#include <ranges>
#include <shaiya/include/common/SConnection.h>
#include <shaiya/include/item/ItemType.h>
#include <shaiya/include/network/game/outgoing/0300.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/Synergy.h"
using namespace shaiya;

namespace user_equipment
{
    bool enable_slot(ItemInfo* itemInfo, EquipmentSlot slot)
    {
        switch (static_cast<ItemType>(itemInfo->type))
        {
        case ItemType::Pet:
            return slot == EquipmentSlot::Pet;
        case ItemType::Wings:
            return slot == EquipmentSlot::Wings;
        case ItemType::Costume:
            return slot == EquipmentSlot::Costume;
        default:
            break;
        }

        return true;
    }

    void init(CUser* user)
    {
        user->initEquipment = true;

        for (const auto& [slot, item] : std::views::enumerate(
            std::as_const(user->inventory[0])))
        {
            if (!item)
                continue;

            if (slot < EquipmentSlot::Vehicle)
                user->itemQualityEx[slot] = item->quality;

            CUser::ItemEquipmentAdd(user, item, slot);
        }

        user->initEquipment = false;
        CUser::SetAttack(user);
    }

    void send_inspect(CUser* user, CUser* target)
    {
        GetInfoInspectOutgoing outgoing{};
        outgoing.itemCount = 0;

        for (const auto& [slot, item] : std::views::enumerate(
            std::as_const(target->inventory[0])))
        {
            if (!item)
                continue;

            if (std::cmp_greater_equal(slot, outgoing.itemList.size()))
                break;

            if (slot < EquipmentSlot::Wings)
            {
                Item0307 item0307{};
                item0307.slot = slot;
                item0307.type = item->type;
                item0307.typeId = item->typeId;

                if (slot < EquipmentSlot::Vehicle)
                    item0307.quality = item->quality;

                item0307.gems = item->gems;
                item0307.craftName = item->craftName;
                outgoing.itemList[outgoing.itemCount] = item0307;

                ++outgoing.itemCount;
            }
        }

        int length = outgoing.size_without_list() + (outgoing.itemCount * sizeof(Item0307));
        SConnection::Send(&user->connection, &outgoing, length);
    }
}

unsigned u0x468474 = 0x468474;
void __declspec(naked) naked_0x46846F()
{
    __asm
    {
        pushad

        push eax
        push esi
        call user_equipment::enable_slot
        add esp,0x8
        test al,al

        popad

        je wrong_slot

        // original
        mov eax,0x1
        jmp u0x468474

        wrong_slot:
        xor al,al
        pop esi
        retn
    }
}

unsigned u0x46153E = 0x46153E;
void __declspec(naked) naked_0x4614E3()
{
    __asm
    {
        pushad

        push esi
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
        call user_equipment::send_inspect
        add esp,0x8

        popad

        jmp u0x477E02
    }
}

unsigned u0x461646 = 0x461646;
void __declspec(naked) naked_0x461640()
{
    __asm
    {
        pushad

        push 0x0 // itemRemove
        push eax // item
        push edi // user
        call Synergy::applySynergies
        add esp,0xC

        popad

        sub esp,0x1C
        push ebx
        mov ebx,eax
        jmp u0x461646
    }
}

unsigned u0x461D16 = 0x461D16;
void __declspec(naked) naked_0x461D10()
{
    __asm
    {
        pushad

        push 0x1 // itemRemove
        push ecx // item
        push edx // user
        call Synergy::applySynergies
        add esp,0xC

        popad

        push ebp
        mov ebp,esp
        and esp,-0x8
        jmp u0x461D16
    }
}

// CUser::InitEquipment
unsigned u0x461010 = 0x461010;
unsigned u0x48F9C5 = 0x48F9C5;
void __declspec(naked) naked_0x48F9BE()
{
    __asm
    {
        pushad

        push edi
        call Synergy::removeSynergies
        add esp,0x4

        popad

        // original
        mov eax,edi
        call u0x461010

        jmp u0x48F9C5
    }
}

unsigned u0x48FCDA = 0x48FCDA;
void __declspec(naked) naked_0x48FCD3()
{
    __asm
    {
        pushad

        push esi
        call Synergy::removeSynergies
        add esp,0x4

        popad

        // original
        mov eax,esi
        call u0x461010

        jmp u0x48FCDA
    }
}

void hook::user_equipment()
{
    // CUser::ItemEquipmentAdd
    util::detour((void*)0x461640, naked_0x461640, 6);
    // CUser::ItemEquipmentRem
    util::detour((void*)0x461D10, naked_0x461D10, 6);
    // CUser::StatResetStatus
    util::detour((void*)0x48F9BE, naked_0x48F9BE, 7);
    // CUser::StatResetSkill
    util::detour((void*)0x48FCD3, naked_0x48FCD3, 7);

#ifdef SHAIYA_EP6_4_PT
    // CUser::EnableEquipment default case (slot)
    util::detour((void*)0x46846F, naked_0x46846F, 5);
    // CUser::InitEquipment
    util::detour((void*)0x4614E3, naked_0x4614E3, 6);
    // CUser::PacketGetInfo case 0x307
    util::detour((void*)0x477D4F, naked_0x477D4F, 7);

    // CUser::InitEquipment (overload)
    util::write_memory((void*)0x4615B3, max_equipment_slot, 1);
    // CUser::ItemBagToBag
    util::write_memory((void*)0x46862D, max_equipment_slot, 1);
    util::write_memory((void*)0x468722, max_equipment_slot, 1);
    util::write_memory((void*)0x4688B0, max_equipment_slot, 1);
    util::write_memory((void*)0x468955, max_equipment_slot, 1);
    util::write_memory((void*)0x468A2B, max_equipment_slot, 1);
    util::write_memory((void*)0x468B5D, max_equipment_slot, 1);
    // CUser::ClearEquipment
    util::write_memory((void*)0x46BCCF, max_equipment_slot, 1);
    // CUser::PacketAdminCmdD
    util::write_memory((void*)0x482896, max_equipment_slot, 1);

    // change 0x199 (user->itemQualityLv) to 0x5DA8
    std::array<std::uint8_t, 2> a00{ 0xA8, 0x5D };
    
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

    // change 0x1A6 (user->itemQuality) to 0x5DC0
    std::array<std::uint8_t, 2> a01{ 0xC0, 0x5D };

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
#endif
}
