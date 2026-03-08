#include <util/util.h>
#include <shaiya/include/common/ItemEquipment.h>
#include <shaiya/include/common/ShapeType.h>
#include <shaiya/include/network/game/outgoing/0300.h>
#include "include/main.h"
#include "include/shaiya/CItem.h"
#include "include/shaiya/CloneUser.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/CZone.h"
#include "include/shaiya/SConnection.h"
using namespace shaiya;

/// <summary>
/// Sends packet 0x303 (6.4) to the target.
/// </summary>
void hook_0x426948(CUser* user, CUser* target)
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

        SConnection::Send(target, &outgoing, user->clone->packetLength);
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

        for (int slot = 0; slot < 17; ++slot)
        {
            auto& item = user->inventory[0][slot];
            if (!item)
                continue;

            outgoing.equipment[slot].type = item->type;
            outgoing.equipment[slot].typeId = item->typeId;
            outgoing.equipment[slot].enchantStep = CItem::GetEnchantStep(item);
        }

        outgoing.charName = user->charName;
        int length = sizeof(GameGetInfoUserShapeOutgoing_EP6_4);

        auto& cloak = user->inventory[0][7];
        if (!cloak)
        {
            length -= sizeof(CloakInfo);
            CUser::GetGuildName(user, reinterpret_cast<char*>(outgoing.cloakInfo.data()));
        }
        else
        {
            outgoing.cloakInfo = cloak->gems;
            CUser::GetGuildName(user, outgoing.guildName.data());
        }

        SConnection::Send(target, &outgoing, length);
    }
}

/// <summary>
/// Sends packet 0x303 (6.4) to the zone.
/// </summary>
void hook_0x491B13(CUser* user)
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

        for (int slot = 0; slot < 17; ++slot)
        {
            auto& item = user->inventory[0][slot];
            if (!item)
                continue;

            outgoing.equipment[slot].type = item->type;
            outgoing.equipment[slot].typeId = item->typeId;
            outgoing.equipment[slot].enchantStep = CItem::GetEnchantStep(item);
        }

        outgoing.charName = user->charName;
        int length = sizeof(GameGetInfoUserShapeOutgoing_EP6_4);

        auto& cloak = user->inventory[0][7];
        if (!cloak)
        {
            length -= sizeof(CloakInfo);
            CUser::GetGuildName(user, reinterpret_cast<char*>(outgoing.cloakInfo.data()));
        }
        else
        {
            outgoing.cloakInfo = cloak->gems;
            CUser::GetGuildName(user, outgoing.guildName.data());
        }

        if (!user->zone)
            return;

        CZone::SendView(user->zone, &outgoing, length, user->cellX, user->cellZ);
    }
}

/// <summary>
/// Sends packet 0x307 (6.4) to the user.
/// </summary>
void hook_0x477D4F(CUser* user, CUser* target)
{
    GameGetInfoUserItemsOutgoing<GetInfoItemUnit_EP5, 17> outgoing{};
    outgoing.itemCount = 0;

    for (int slot = 0; slot < 17; ++slot)
    {
        auto& item = target->inventory[0][slot];
        if (!item)
            continue;

        // This condition can be removed if the client 
        // inspection window supports 17 slots
        if (slot < ItemEquipment::Wings)
        {
            GetInfoItemUnit_EP5 item0307{};
            item0307.slot = slot;
            item0307.type = item->type;
            item0307.typeId = item->typeId;

            if (slot < ItemEquipment::Vehicle)
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

unsigned u0x426CA0 = 0x426CA0;
void __declspec(naked) naked_0x426948()
{
    __asm
    {
        pushad
        
        push ebp // target
        push ebx // user
        call hook_0x426948
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
        call hook_0x491B13
        add esp,0x4
        
        popad

        jmp u0x491EBF
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
        call hook_0x477D4F
        add esp,0x8

        popad

        jmp u0x477E02
    }
}

void hook::packet_get_info()
{
    // CZone::SendUserShape
    util::detour((void*)0x426948, naked_0x426948, 7);
    // CUser::SendUserShape
    util::detour((void*)0x491B13, naked_0x491B13, 7);
    // CUser::PacketGetInfo case 0x307
    util::detour((void*)0x477D4F, naked_0x477D4F, 7);
}
