#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>
#include <include/shaiya/packets/0300.h>
#include <include/shaiya/include/CGameData.h>
#include <include/shaiya/include/CItem.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/SConnection.h>
#include <include/shaiya/include/ServerTime.h>
#include <include/shaiya/include/Synergy.h>
using namespace shaiya;

namespace user_equipment
{
    constexpr int max_equipment_slot = item_list_size;

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

    void send(CUser* user, EquipmentSlot slot)
    {
        switch (slot)
        {
        case EquipmentSlot::Pet:
        case EquipmentSlot::Costume:
        case EquipmentSlot::Wings:
            CUser::SendEquipment(user, slot);
            break;
        default:
            break;
        }
    }

    void init(CUser* user)
    {
        user->isInitEquipment = true;

        for (int slot = 0; slot < max_equipment_slot; ++slot)
        {
            auto& item = user->inventory[0][slot];
            if (!item)
                continue;

            if (slot < EquipmentSlot::Vehicle)
                user->itemQuality[slot] = item->quality;

            CUser::ItemEquipmentAdd(user, item, slot);
        }

        user->isInitEquipment = false;
        CUser::SetAttack(user);
    }

    void send_inspect(CUser* user, CUser* target)
    {
        constexpr int packet_size_without_list = 3;

        GetInfoInspectOutgoing packet{};
        packet.itemCount = 0;

        for (int slot = 0; slot < EquipmentSlot::Wings; ++slot)
        {
            auto& item = target->inventory[0][slot];
            if (!item)
                continue;

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

unsigned u0x4686C9 = 0x4686C9;
void __declspec(naked) naked_0x4686C4()
{
    __asm
    {
        pushad
            
        push ebx
        push esi
        call user_equipment::send
        add esp,0x8

        popad

        // original
        mov ecx,0x703
        jmp u0x4686C9
    }
}

unsigned u0x4689D4 = 0x4689D4;
void __declspec(naked) naked_0x4689CF()
{
    __asm
    {
        pushad
            
        push ebx
        push esi
        call user_equipment::send
        add esp,0x8

        popad

        // original
        mov edx,0x703
        jmp u0x4689D4
    }
}

unsigned u0x468AFF = 0x468AFF;
void __declspec(naked) naked_0x468AFA()
{
    __asm
    {
        pushad
            
        push ebx
        push esi
        call user_equipment::send
        add esp,0x8

        popad

        // original
        mov eax,0x703
        jmp u0x468AFF
    }
}

unsigned u0x468A6E = 0x468A6E;
unsigned u0x468AC0 = 0x468AC0;
void __declspec(naked) naked_0x468A66()
{
    __asm
    {
        // slot
        cmp ebx,0x8
        jge _0x468AC0

        // original
        mov cx,[esi+ebx*2+0x1A6]
        jmp u0x468A6E

        _0x468AC0:
        jmp u0x468AC0
    }
}

unsigned u0x468669 = 0x468669;
unsigned u0x4686BA = 0x4686BA;
void __declspec(naked) naked_0x468661()
{
    __asm
    {
        // slot
        cmp ebx,0x8
        jge _0x4686BA

        // original
        mov di,[esi+ebx*2+0x1A6]
        jmp u0x468669

        _0x4686BA:
        jmp u0x4686BA
    }
}

unsigned u0x468817 = 0x468817;
unsigned u0x4687CF = 0x4687CF;
void __declspec(naked) naked_0x4687C7()
{
    __asm
    {
        // slot
        cmp ebx,0x8
        jge _0x468817

        // original
        mov dx,[esi+ebx*2+0x1A6]
        jmp u0x4687CF

        _0x468817:
        jmp u0x468817
    }
}

unsigned u0x46899A = 0x46899A;
void __declspec(naked) naked_0x468992()
{
    __asm
    {
        // slot
        cmp ebx,0x8
        jge _0x46899A

        // original
        mov [esi+ebx*2+0x1A6],cx

        _0x46899A:
        jmp u0x46899A
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

void hook::user_equipment()
{
    // CUser::EnableEquipment default case (slot)
    util::detour((void*)0x46846F, naked_0x46846F, 5);
    // CUser::ItemBagToBag
    util::detour((void*)0x4686C4, naked_0x4686C4, 5);
    util::detour((void*)0x4689CF, naked_0x4689CF, 5);
    util::detour((void*)0x468AFA, naked_0x468AFA, 5);
    util::detour((void*)0x468A66, naked_0x468A66, 8);
    util::detour((void*)0x468661, naked_0x468661, 8);
    util::detour((void*)0x4687C7, naked_0x4687C7, 8);
    util::detour((void*)0x468992, naked_0x468992, 8);
    // CUser::InitEquipment
    util::detour((void*)0x4614E3, naked_0x4614E3, 6);
    // CUser::PacketGetInfo case 0x307
    util::detour((void*)0x477D4F, naked_0x477D4F, 7);

    #ifdef SHAIYA_EP6_ITEM_SET
    // CUser::ItemEquipmentAdd
    util::detour((void*)0x461640, naked_0x461640, 6);
    // CUser::ItemEquipmentRem
    util::detour((void*)0x461D10, naked_0x461D10, 6);
    #endif

    // CUser::InitEquipment (overload)
    util::write_memory((void*)0x4615B3, item_list_size, 1);
    // CUser::ItemBagToBag
    util::write_memory((void*)0x46862D, item_list_size, 1);
    util::write_memory((void*)0x468722, item_list_size, 1);
    util::write_memory((void*)0x468955, item_list_size, 1);
    // CUser::ClearEquipment
    util::write_memory((void*)0x46BCCF, item_list_size, 1);
    // CUser::PacketAdminCmdD
    util::write_memory((void*)0x482896, item_list_size, 1);
}
