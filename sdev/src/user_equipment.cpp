#include <array>
#include <ranges>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/shaiya/packets/0300.h>
#include <include/shaiya/include/CGameData.h>
#include <include/shaiya/include/CItem.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/SConnection.h>
#include <include/shaiya/include/Synergy.h>
#include <util/include/util.h>
using namespace shaiya;

namespace user_equipment
{
    bool enable_slot(CGameData::ItemInfo* itemInfo, EquipmentSlot slot)
    {
        switch (static_cast<CGameData::ItemType>(itemInfo->type))
        {
        case CGameData::ItemType::Pet:
            return slot == EquipmentSlot::Pet;
        case CGameData::ItemType::Wings:
            return slot == EquipmentSlot::Wings;
        case CGameData::ItemType::Costume:
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
        constexpr int packet_size_without_list = 3;

        GetInfoInspectOutgoing packet{};
        packet.itemCount = 0;

        for (const auto& [slot, item] : std::views::enumerate(
            std::as_const(target->inventory[0])))
        {
            if (!item)
                continue;

            if (std::size_t(slot) >= packet.itemList.size())
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
                packet.itemList[packet.itemCount] = item0307;

                ++packet.itemCount;
            }
        }

        int length = packet_size_without_list + (packet.itemCount * sizeof(Item0307));
        SConnection::Send(&user->connection, &packet, length);
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

        push edi
        call Synergy::applySynergies
        add esp,0x4

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

        push edx
        call Synergy::applySynergies
        add esp,0x4

        popad

        push ebp
        mov ebp,esp
        and esp,-0x8
        jmp u0x461D16
    }
}

unsigned u0x46EE2B = 0x46EE2B;
void __declspec(naked) naked_0x46EE26()
{
    __asm
    {
        mov eax,[esp+0x14]
        lea edx,[eax+eax*0x2]
        lea ecx,[ebx+edx*0x8]

        xor eax,eax
        mov [ebp+ecx*0x4+0x1C0],eax

        // original
        push ebx
        mov ecx,esi
        mov edx,ebp

        jmp u0x46EE2B
    }
}

unsigned u0x46D41C = 0x46D41C;
void __declspec(naked) naked_0x46D417()
{
    __asm
    {
        mov eax,[esp+0x18]
        lea edx,[eax+eax*0x2]
        lea ecx,[ebx+edx*0x8]

        xor eax,eax
        mov [ebp+ecx*0x4+0x1C0],eax

        // original
        push ebx
        mov ecx,esi
        mov edx,ebp

        jmp u0x46D41C
    }
}

unsigned u0x470A81 = 0x470A81;
void __declspec(naked) naked_0x470A7C()
{
    __asm
    {
        mov eax,[esp+0x1C]
        mov ecx,[esp+0x18]
        lea edx,[eax+eax*0x2]
        lea edx,[ecx+edx*0x8]

        xor eax,eax
        mov [edi+edx*0x4+0x1C0],eax

        // original
        mov eax,[esp+0x18]
        push eax
        mov ecx,ebp
        mov edx,edi

        jmp u0x470A81
    }
}

unsigned u0x4718ED = 0x4718ED;
void __declspec(naked) naked_0x4718E8()
{
    __asm
    {
        mov eax,[esp+0x18]
        lea ecx,[eax+eax*0x2]
        lea edx,[ebx+ecx*0x8]

        xor eax,eax
        mov [edi+edx*0x4+0x1C0],eax

        // original
        push ebx
        mov ecx,ebp
        mov edx,edi

        jmp u0x4718ED
    }
}

void hook::user_equipment()
{
    // CUser::EnableEquipment default case (slot)
    util::detour((void*)0x46846F, naked_0x46846F, 5);
    // CUser::InitEquipment
    util::detour((void*)0x4614E3, naked_0x4614E3, 6);
    // CUser::PacketGetInfo case 0x307
    util::detour((void*)0x477D4F, naked_0x477D4F, 7);
    // CUser::ItemEquipmentAdd
    util::detour((void*)0x461640, naked_0x461640, 6);
    // CUser::ItemEquipmentRem
    util::detour((void*)0x461D10, naked_0x461D10, 6);
    // CUser::ItemGemAdd
    util::detour((void*)0x46EE26, naked_0x46EE26, 5);
    // CUser::ItemLapisianAdd
    util::detour((void*)0x46D417, naked_0x46D417, 5);
    // CUser::ItemGemRemoveAll
    util::detour((void*)0x470A7C, naked_0x470A7C, 5);
    // CUser::ItemGemRemovePos
    util::detour((void*)0x4718E8, naked_0x4718E8, 5);

    // CUser::InitEquipment (overload)
    util::write_memory((void*)0x4615B3, max_inventory_slot, 1);
    // CUser::ItemBagToBag
    util::write_memory((void*)0x46862D, max_inventory_slot, 1);
    util::write_memory((void*)0x468722, max_inventory_slot, 1);
    util::write_memory((void*)0x4688B0, max_inventory_slot, 1);
    util::write_memory((void*)0x468955, max_inventory_slot, 1);
    util::write_memory((void*)0x468A2B, max_inventory_slot, 1);
    util::write_memory((void*)0x468B5D, max_inventory_slot, 1);
    // CUser::ClearEquipment
    util::write_memory((void*)0x46BCCF, max_inventory_slot, 1);
    // CUser::PacketAdminCmdD
    util::write_memory((void*)0x482896, max_inventory_slot, 1);

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

    // change 0x1A6 (user->itemQuality) to 0x5D0C
    std::array<std::uint8_t, 2> a01{ 0x0C, 0x5D };

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
}
