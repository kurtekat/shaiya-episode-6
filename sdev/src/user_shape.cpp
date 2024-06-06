#include <ranges>
#include <shaiya/include/common/SConnection.h>
#include <shaiya/include/network/game/outgoing/0300.h>
#include <shaiya/include/network/game/outgoing/0500.h>
#include <shaiya/include/item/Gems.h>
#include <shaiya/include/user/ShapeType.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/CZone.h"
using namespace shaiya;

namespace user_shape
{
    void init_clone_user(CUser* user, CUser* target)
    {
        if (!user->clone)
            return;

        std::memset(user->clone, 0, sizeof(CloneUser));

        user->clone->dead = target->status == UserStatus::Death ? true : false;
        user->clone->sitting = target->sitting;
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

        for (const auto& [slot, item] : std::views::enumerate(
            std::as_const(target->inventory[0])))
        {
            if (!item)
                continue;

            if (std::cmp_greater_equal(slot, user->clone->equipment.size()))
                break;

            user->clone->equipment[slot].type = item->type;
            user->clone->equipment[slot].typeId = item->typeId;
            user->clone->equipment[slot].enchantStep = CItem::GetEnchantStep(item);
        }

        user->clone->charName = target->charName;

        auto& item = target->inventory[0][EquipmentSlot::Cloak];
        if (!item)
        {
            CUser::GetGuildName(target, user->clone->guildName.data());
            user->clone->packetLength = sizeof(GetInfoUserShapeOutgoing) - sizeof(CloakBadge);
        }
        else
        {
            user->clone->cloakBadge = item->gems;
            CUser::GetGuildName(target, user->clone->guildName.data());
            user->clone->packetLength = sizeof(GetInfoUserShapeOutgoing);
        }
    }

    void send_user_shape(CUser* user, CUser* target)
    {
        GetInfoUserShapeOutgoing outgoing{};
        outgoing.charId = user->id;

        if (user->shapeType == ShapeType::Disguise && user->clone)
        {
            outgoing.dead = user->clone->dead;
            outgoing.sitting = user->clone->sitting;
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

            std::memcpy(&outgoing.equipment, &user->clone->equipment, sizeof(outgoing.equipment));
            outgoing.charName = user->clone->charName;

            if (user->clone->packetLength == sizeof(GetInfoUserShapeOutgoing))
            {
                outgoing.cloakBadge = user->clone->cloakBadge;
                outgoing.guildName = user->clone->guildName;
                SConnection::Send(&target->connection, &outgoing, sizeof(GetInfoUserShapeOutgoing));
            }
            else
            {
                std::memcpy(&outgoing.cloakBadge, &user->clone->guildName, user->clone->guildName.size());

                int length = sizeof(GetInfoUserShapeOutgoing) - sizeof(CloakBadge);
                SConnection::Send(&target->connection, &outgoing, length);
            }

            return;
        }

        outgoing.dead = user->status == UserStatus::Death ? true : false;
        outgoing.sitting = user->sitting;
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

        for (const auto& [slot, item] : std::views::enumerate(
            std::as_const(user->inventory[0])))
        {
            if (!item)
                continue;

            if (std::cmp_greater_equal(slot, outgoing.equipment.size()))
                break;

            outgoing.equipment[slot].type = item->type;
            outgoing.equipment[slot].typeId = item->typeId;
            outgoing.equipment[slot].enchantStep = CItem::GetEnchantStep(item);
        }

        outgoing.charName = user->charName;

        auto& item = user->inventory[0][EquipmentSlot::Cloak];
        if (!item)
        {
            CUser::GetGuildName(user, reinterpret_cast<char*>(&outgoing.cloakBadge));

            int length = sizeof(GetInfoUserShapeOutgoing) - sizeof(CloakBadge);
            SConnection::Send(&target->connection, &outgoing, length);
        }
        else
        {
            outgoing.cloakBadge = item->gems;
            CUser::GetGuildName(user, outgoing.guildName.data());
            SConnection::Send(&target->connection, &outgoing, sizeof(GetInfoUserShapeOutgoing));
        }
    }

    void send_zone_shape(CUser* user)
    {
        if (!user->zone)
            return;

        GetInfoUserShapeOutgoing outgoing{};
        outgoing.charId = user->id;

        if (user->shapeType == ShapeType::Disguise && user->clone)
        {
            outgoing.dead = user->clone->dead;
            outgoing.sitting = user->clone->sitting;
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

            std::memcpy(&outgoing.equipment, &user->clone->equipment, sizeof(outgoing.equipment));
            outgoing.charName = user->clone->charName;

            if (user->clone->packetLength == sizeof(GetInfoUserShapeOutgoing))
            {
                outgoing.cloakBadge = user->clone->cloakBadge;
                outgoing.guildName = user->clone->guildName;
                CZone::SendView(user->zone, &outgoing, sizeof(GetInfoUserShapeOutgoing), user->cellX, user->cellZ);
            }
            else
            {
                std::memcpy(&outgoing.cloakBadge, &user->clone->guildName, user->clone->guildName.size());

                int length = sizeof(GetInfoUserShapeOutgoing) - sizeof(CloakBadge);
                CZone::SendView(user->zone, &outgoing, length, user->cellX, user->cellZ);
            }

            return;
        }

        outgoing.dead = user->status == UserStatus::Death ? true : false;
        outgoing.sitting = user->sitting;
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

        for (const auto& [slot, item] : std::views::enumerate(
            std::as_const(user->inventory[0])))
        {
            if (!item)
                continue;

            if (std::cmp_greater_equal(slot, outgoing.equipment.size()))
                break;

            outgoing.equipment[slot].type = item->type;
            outgoing.equipment[slot].typeId = item->typeId;
            outgoing.equipment[slot].enchantStep = CItem::GetEnchantStep(item);
        }

        outgoing.charName = user->charName;

        auto& item = user->inventory[0][EquipmentSlot::Cloak];
        if (!item)
        {
            CUser::GetGuildName(user, reinterpret_cast<char*>(&outgoing.cloakBadge));

            int length = sizeof(GetInfoUserShapeOutgoing) - sizeof(CloakBadge);
            CZone::SendView(user->zone, &outgoing, length, user->cellX, user->cellZ);
        }
        else
        {
            outgoing.cloakBadge = item->gems;
            CUser::GetGuildName(user, outgoing.guildName.data());
            CZone::SendView(user->zone, &outgoing, sizeof(GetInfoUserShapeOutgoing), user->cellX, user->cellZ);
        }
    }

    void send_zone_shape_type(CUser* user, Packet buffer)
    {
        UserShapeTypeOutgoing outgoing{};
        outgoing.charId = user->id;
        outgoing.shapeType = util::deserialize<ShapeType>(buffer, 6);
        
        auto& vehicle = user->inventory[0][EquipmentSlot::Vehicle];
        outgoing.vehicleType = !vehicle ? 0 : vehicle->type;
        outgoing.vehicleTypeId = !vehicle ? 0 : vehicle->typeId;

        if (!user->zone)
            return;

        CZone::SendView(user->zone, &outgoing, sizeof(UserShapeTypeOutgoing), user->cellX, user->cellZ);
    }

    void send_user_shape_type(CUser* target, CUser* user, ShapeType shapeType)
    {
        UserShapeTypeOutgoing outgoing{};
        outgoing.charId = user->id;
        outgoing.shapeType = shapeType;

        auto& vehicle = user->inventory[0][EquipmentSlot::Vehicle];
        outgoing.vehicleType = !vehicle ? 0 : vehicle->type;
        outgoing.vehicleTypeId = !vehicle ? 0 : vehicle->typeId;

        SConnection::Send(&target->connection, &outgoing, sizeof(UserShapeTypeOutgoing));
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
        call user_shape::send_user_shape
        add esp,0x8

        popad

        jmp u0x426CA0
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

unsigned u0x491EBF = 0x491EBF;
void __declspec(naked) naked_0x491B13()
{
    __asm
    {
        push esi
        push edi

        pushad

        push ebp // user
        call user_shape::send_zone_shape
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
        call user_shape::init_clone_user
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
        call user_shape::send_zone_shape_type
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
        call user_shape::send_user_shape_type
        add esp,0xC
        
        popad

        jmp u0x42A57E
    }
}

unsigned u0x4263B8 = 0x4263B8;
void __declspec(naked) naked_0x4263AD()
{
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

void hook::user_shape()
{
    // CZone::SendUserShape
    util::detour((void*)0x426948, naked_0x426948, 7);
    // CObjectMgr::CreateCloneUser
    util::detour((void*)0x411B1F, naked_0x411B1F, 7);
    // CUser::SendUserShape
    util::detour((void*)0x491B13, naked_0x491B13, 7);
    // CUser::CheckTargetUser case 2
    util::detour((void*)0x45A365, naked_0x45A365, 7);

#ifdef SHAIYA_EP6_4_PT
    // CUser::SendShape
    util::detour((void*)0x491490, naked_0x491490, 6);
    // CCell::SendCellInfoEnter
    util::detour((void*)0x42A56C, naked_0x42A56C, 6);
    // CZone::SendMoveUser
    util::detour((void*)0x4263AD, naked_0x4263AD, 6);
#endif
}
