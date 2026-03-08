#include <util/util.h>
#include <shaiya/include/common/ShapeType.h>
#include <shaiya/include/network/game/outgoing/0300.h>
#include <shaiya/include/network/game/outgoing/0500.h>
#include "include/main.h"
#include "include/shaiya/CItem.h"
#include "include/shaiya/CloneUser.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/CZone.h"
#include "include/shaiya/SConnection.h"
using namespace shaiya;

void hook_0x45A365(CUser* user, CUser* target)
{
    if (!user->clone)
        return;

    user->clone->dead = target->status == UserStatus::Death;
    user->clone->motion = target->motion;
    user->clone->country = target->country;
    user->clone->family = target->family;
    user->clone->hair = target->hair;
    user->clone->face = target->face;
    user->clone->size = target->size;
    user->clone->job = target->job;
    user->clone->sex = target->sex;
    user->clone->partyType = CUser::GetPartyType(target);
    user->clone->grow = target->grow;
    user->clone->kills = target->kills;

    user->clone->equipment = {};
    user->clone->charName = {};
    user->clone->cloakInfo = {};
    user->clone->guildName = {};

    for (int slot = 0; slot < 17; ++slot)
    {
        auto& item = target->inventory[0][slot];
        if (!item)
            continue;

        user->clone->equipment[slot].type = item->type;
        user->clone->equipment[slot].typeId = item->typeId;
        user->clone->equipment[slot].enchantStep = CItem::GetEnchantStep(item);
    }

    user->clone->charName = target->charName;
    user->clone->packetLength = sizeof(GameGetInfoUserShapeOutgoing_EP6_4);

    auto& cloak = target->inventory[0][7];
    if (!cloak)
    {
        user->clone->packetLength -= sizeof(CloakInfo);
        CUser::GetGuildName(target, user->clone->guildName.data());
    }
    else
    {
        user->clone->cloakInfo = cloak->gems;
        CUser::GetGuildName(target, user->clone->guildName.data());
    }
}

/// <summary>
/// Sends packet 0x51D (6.4) to the zone.
/// </summary>
void hook_0x491490(CUser* user, GameCharShapeOutgoing_EP5* packet)
{
    GameCharShapeOutgoing_EP6_4 outgoing{};
    outgoing.objectId = user->id;
    outgoing.shapeType = packet->shapeType;
    auto& vehicle = user->inventory[0][13];
    outgoing.vehicleType = !vehicle ? 0 : vehicle->type;
    outgoing.vehicleTypeId = !vehicle ? 0 : vehicle->typeId;

    if (!user->zone)
        return;

    CZone::SendView(user->zone, &outgoing, sizeof(GameCharShapeOutgoing_EP6_4), user->cellX, user->cellZ);
}

/// <summary>
/// Sends packet 0x51D (6.4) to the target.
/// </summary>
void hook_0x42A56C(CUser* target, CUser* user, ShapeType shapeType)
{
    GameCharShapeOutgoing_EP6_4 outgoing{};
    outgoing.objectId = user->id;
    outgoing.shapeType = shapeType;
    auto& vehicle = user->inventory[0][13];
    outgoing.vehicleType = !vehicle ? 0 : vehicle->type;
    outgoing.vehicleTypeId = !vehicle ? 0 : vehicle->typeId;
    SConnection::Send(target, &outgoing, sizeof(GameCharShapeOutgoing_EP6_4));
}

unsigned u0x45A246 = 0x45A246;
void __declspec(naked) naked_0x45A365()
{
    __asm
    {
        pushad

        push esi // target
        push edi // user
        call hook_0x45A365
        add esp,0x8
        
        popad

        jmp u0x45A246
    }
}

unsigned u0x4914A9 = 0x4914A9;
void __declspec(naked) naked_0x491490()
{
    __asm
    {
        pushad

        lea eax,[esp+0x20]

        push eax // packet
        push ecx // user
        call hook_0x491490
        add esp,0x8
        
        popad

        jmp u0x4914A9
    }
}

unsigned u0x42A57E = 0x42A57E;
void __declspec(naked) naked_0x42A56C()
{
    __asm
    {
        pushad

        push eax // shapeType
        push esi // user
        push ebx // target
        call hook_0x42A56C
        add esp,0xC
        
        popad

        jmp u0x42A57E
    }
}

unsigned u0x4263B8 = 0x4263B8;
void __declspec(naked) naked_0x4263AD()
{
    // edi = CUser*
    __asm
    {
        // shapeType
        mov byte ptr[esp+0x3E],al

        xor eax,eax
        mov [esp+0x3F],eax
        mov [esp+0x43],eax

        // user->inventory[0][13]
        mov eax,[edi+0x1F4]
        test eax,eax
        je without_vehicle

        // vehicle->type
        movzx ecx,byte ptr[eax+0x40]
        mov [esp+0x3F],ecx

        // vehicle->typeId
        movzx ecx,byte ptr[eax+0x41]
        mov [esp+0x43],ecx

        without_vehicle:

        lea ecx,[esp+0x38]
        push 0xF // length
        push ecx // packet

        jmp u0x4263B8
    }
}

unsigned u0x411B26 = 0x411B26;
unsigned u0x51B26B = 0x51B26B;
void __declspec(naked) naked_0x411B1F()
{
    __asm
    {
        push 0x80 // size
        call u0x51B26B // malloc
        jmp u0x411B26
    }
}

void hook::user_shape()
{
    // CUser::CheckTargetUser case 2
    util::detour((void*)0x45A365, naked_0x45A365, 7);
    // CUser::SendShape
    util::detour((void*)0x491490, naked_0x491490, 6);
    // CCell::SendCellInfoEnter
    util::detour((void*)0x42A56C, naked_0x42A56C, 6);
    // CZone::SendMoveUser
    util::detour((void*)0x4263AD, naked_0x4263AD, 6);
    // CObjectMgr::CreateCloneUser
    util::detour((void*)0x411B1F, naked_0x411B1F, 7);
}
