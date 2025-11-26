#include <ranges>
#include <util/util.h>
#include <shaiya/include/common/ItemSlot.h>
#include <shaiya/include/common/PartyTypes.h>
#include <shaiya/include/common/UserTypes.h>
#include <shaiya/include/network/game/outgoing/0300.h>
#include <shaiya/include/network/game/outgoing/0500.h>
#include "include/main.h"
#include "include/extensions/ranges.hpp"
#include "include/shaiya/CItem.h"
#include "include/shaiya/CloneUser.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/CZone.h"
#include "include/shaiya/NetworkHelper.h"
using namespace shaiya;

namespace user_shape
{
    void init_clone(CUser* user, CUser* target)
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

        auto count = user->clone->equipment.size();
        for (const auto& [slot, item] : ext::views::enumerate_n(
            std::as_const(target->inventory[0]), count))
        {
            if (!item)
                continue;

            user->clone->equipment[slot].type = item->type;
            user->clone->equipment[slot].typeId = item->typeId;
            user->clone->equipment[slot].enchantStep = CItem::GetEnchantStep(item);
        }

        user->clone->charName = target->charName;
        user->clone->packetLength = sizeof(GameGetInfoUserShapeOutgoing_EP6_4);

        auto& item = target->inventory[0][ItemSlot::Cloak];
        if (!item)
        {
            user->clone->packetLength -= sizeof(CloakInfo);
            CUser::GetGuildName(target, user->clone->guildName.data());
        }
        else
        {
            user->clone->cloakInfo = item->gems;
            CUser::GetGuildName(target, user->clone->guildName.data());
        }
    }

    /// <summary>
    /// Sends packet 0x303 (6.4) to the target.
    /// </summary>
    void send_user_0x303(CUser* user, CUser* target)
    {
        GameGetInfoUserShapeOutgoing_EP6_4 outgoing{};
        outgoing.objectId = user->id;

        if (user->shapeType == ShapeType::Disguise && user->clone)
        {
            outgoing.dead = user->clone->dead;
            outgoing.motion = user->clone->motion;
            outgoing.country = user->clone->country;
            outgoing.family = user->clone->family;
            outgoing.hair = user->clone->hair;
            outgoing.face = user->clone->face;
            outgoing.size = user->clone->size;
            outgoing.job = user->clone->job;
            outgoing.sex = user->clone->sex;
            outgoing.partyType = user->clone->partyType;
            outgoing.grow = user->clone->grow;
            outgoing.kills = user->clone->kills;
            outgoing.equipment = user->clone->equipment;
            outgoing.charName = user->clone->charName;

            if (user->clone->packetLength == sizeof(GameGetInfoUserShapeOutgoing_EP6_4))
            {
                outgoing.cloakInfo = user->clone->cloakInfo;
                outgoing.guildName = user->clone->guildName;
            }
            else
            {
                std::memcpy(outgoing.cloakInfo.data(),
                    user->clone->guildName.data(), user->clone->guildName.size());
            }

            NetworkHelper::Send(target, &outgoing, user->clone->packetLength);
        }
        else
        {
            outgoing.dead = user->status == UserStatus::Death;
            outgoing.motion = user->motion;
            outgoing.country = user->country;
            outgoing.family = user->family;
            outgoing.hair = user->hair;
            outgoing.face = user->face;
            outgoing.size = user->size;
            outgoing.job = user->job;
            outgoing.sex = user->sex;
            outgoing.partyType = CUser::GetPartyType(user);
            outgoing.grow = user->grow;
            outgoing.kills = user->kills;

            auto count = outgoing.equipment.size();
            for (const auto& [slot, item] : ext::views::enumerate_n(
                std::as_const(user->inventory[0]), count))
            {
                if (!item)
                    continue;

                outgoing.equipment[slot].type = item->type;
                outgoing.equipment[slot].typeId = item->typeId;
                outgoing.equipment[slot].enchantStep = CItem::GetEnchantStep(item);
            }

            outgoing.charName = user->charName;
            int length = sizeof(GameGetInfoUserShapeOutgoing_EP6_4);

            auto& item = user->inventory[0][ItemSlot::Cloak];
            if (!item)
            {
                length -= sizeof(CloakInfo);
                CUser::GetGuildName(user, reinterpret_cast<char*>(outgoing.cloakInfo.data()));
            }
            else
            {
                outgoing.cloakInfo = item->gems;
                CUser::GetGuildName(user, outgoing.guildName.data());
            }

            NetworkHelper::Send(target, &outgoing, length);
        }
    }

    /// <summary>
    /// Sends packet 0x303 (6.4) to the zone.
    /// </summary>
    void send_zone_0x303(CUser* user)
    {
        GameGetInfoUserShapeOutgoing_EP6_4 outgoing{};
        outgoing.objectId = user->id;

        if (user->shapeType == ShapeType::Disguise && user->clone)
        {
            outgoing.dead = user->clone->dead;
            outgoing.motion = user->clone->motion;
            outgoing.country = user->clone->country;
            outgoing.family = user->clone->family;
            outgoing.hair = user->clone->hair;
            outgoing.face = user->clone->face;
            outgoing.size = user->clone->size;
            outgoing.job = user->clone->job;
            outgoing.sex = user->clone->sex;
            outgoing.partyType = user->clone->partyType;
            outgoing.grow = user->clone->grow;
            outgoing.kills = user->clone->kills;
            outgoing.equipment = user->clone->equipment;
            outgoing.charName = user->clone->charName;

            if (user->clone->packetLength == sizeof(GameGetInfoUserShapeOutgoing_EP6_4))
            {
                outgoing.cloakInfo = user->clone->cloakInfo;
                outgoing.guildName = user->clone->guildName;
            }
            else
            {
                std::memcpy(outgoing.cloakInfo.data(), 
                    user->clone->guildName.data(), user->clone->guildName.size());
            }

            if (!user->zone)
                return;

            CZone::SendView(user->zone, &outgoing, user->clone->packetLength, user->cellX, user->cellZ);
        }
        else
        {
            outgoing.dead = user->status == UserStatus::Death;
            outgoing.motion = user->motion;
            outgoing.country = user->country;
            outgoing.family = user->family;
            outgoing.hair = user->hair;
            outgoing.face = user->face;
            outgoing.size = user->size;
            outgoing.job = user->job;
            outgoing.sex = user->sex;
            outgoing.partyType = CUser::GetPartyType(user);
            outgoing.grow = user->grow;
            outgoing.kills = user->kills;

            auto count = outgoing.equipment.size();
            for (const auto& [slot, item] : ext::views::enumerate_n(
                std::as_const(user->inventory[0]), count))
            {
                if (!item)
                    continue;

                outgoing.equipment[slot].type = item->type;
                outgoing.equipment[slot].typeId = item->typeId;
                outgoing.equipment[slot].enchantStep = CItem::GetEnchantStep(item);
            }

            outgoing.charName = user->charName;
            int length = sizeof(GameGetInfoUserShapeOutgoing_EP6_4);

            auto& item = user->inventory[0][ItemSlot::Cloak];
            if (!item)
            {
                length -= sizeof(CloakInfo);
                CUser::GetGuildName(user, reinterpret_cast<char*>(outgoing.cloakInfo.data()));
            }
            else
            {
                outgoing.cloakInfo = item->gems;
                CUser::GetGuildName(user, outgoing.guildName.data());
            }

            if (!user->zone)
                return;

            CZone::SendView(user->zone, &outgoing, length, user->cellX, user->cellZ);
        }
    }

    /// <summary>
    /// Sends packet 0x51D (6.4) to the zone.
    /// </summary>
    void send_zone_0x51D(CUser* user, GameCharShapeOutgoing_EP5* packet)
    {
        GameCharShapeOutgoing_EP6_4 outgoing{};
        outgoing.objectId = user->id;
        outgoing.shapeType = packet->shapeType;
        auto& vehicle = user->inventory[0][ItemSlot::Vehicle];
        outgoing.vehicleType = !vehicle ? 0 : vehicle->type;
        outgoing.vehicleTypeId = !vehicle ? 0 : vehicle->typeId;

        if (!user->zone)
            return;

        CZone::SendView(user->zone, &outgoing, sizeof(GameCharShapeOutgoing_EP6_4), user->cellX, user->cellZ);
    }

    /// <summary>
    /// Sends packet 0x51D (6.4) to the target.
    /// </summary>
    void send_user_0x51D(CUser* target, CUser* user, ShapeType shapeType)
    {
        GameCharShapeOutgoing_EP6_4 outgoing{};
        outgoing.objectId = user->id;
        outgoing.shapeType = shapeType;
        auto& vehicle = user->inventory[0][ItemSlot::Vehicle];
        outgoing.vehicleType = !vehicle ? 0 : vehicle->type;
        outgoing.vehicleTypeId = !vehicle ? 0 : vehicle->typeId;
        NetworkHelper::Send(target, &outgoing, sizeof(GameCharShapeOutgoing_EP6_4));
    }
}

unsigned u0x426CA0 = 0x426CA0;
void __declspec(naked) naked_0x426948()
{
    __asm
    {
        pushad
        
        push ebp // target
        push ebx // user
        call user_shape::send_user_0x303
        add esp,0x8

        popad

        jmp u0x426CA0
    }
}

unsigned u0x491EBF = 0x491EBF;
void __declspec(naked) naked_0x491B13()
{
    __asm
    {
        push esi
        push edi

        pushad

        push ebp // user
        call user_shape::send_zone_0x303
        add esp,0x4
        
        popad

        jmp u0x491EBF
    }
}

unsigned u0x45A246 = 0x45A246;
void __declspec(naked) naked_0x45A365()
{
    __asm
    {
        pushad

        push esi // target
        push edi // user
        call user_shape::init_clone
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
        call user_shape::send_zone_0x51D
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
        call user_shape::send_user_0x51D
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
    // CZone::SendUserShape
    util::detour((void*)0x426948, naked_0x426948, 7);
    // CUser::SendUserShape
    util::detour((void*)0x491B13, naked_0x491B13, 7);
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
