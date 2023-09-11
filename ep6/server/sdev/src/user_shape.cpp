#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>

#include <shaiya/packets/0303.h>
#include <shaiya/include/CItem.h>
#include <shaiya/include/CUser.h>
#include <shaiya/include/CZone.h>
#include <shaiya/include/SConnection.h>
using namespace shaiya;

namespace user_shape
{
    constexpr int max_equipment_slot = 17;
    constexpr int shape_size_without_cloak = 118;
    constexpr int shape_size_with_cloak = 124;

    void init_clone_user(CUser* user, CUser* target)
    {
        memset(user->clone, 0, sizeof(CloneUser));

        user->clone->dead = target->stateType == StateType::Death ? true : false;
        user->clone->sitMode = target->sitMode;
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
        
        for (int slot = 0; slot < max_equipment_slot; ++slot)
        {
            if (target->inventory[0][slot])
            {
                user->clone->equipment[slot].type = target->inventory[0][slot]->type;
                user->clone->equipment[slot].typeId = target->inventory[0][slot]->typeId;
                user->clone->equipment[slot].enchantStep = CItem::GetEnchantStep(target->inventory[0][slot]);
            }
        }

        strncpy_s(user->clone->charName, target->charName, sizeof(user->clone->charName));

        if (target->inventory[0][EquipmentSlot::Cloak])
        {
            memcpy(&user->clone->cloakBadge, &target->inventory[0][EquipmentSlot::Cloak]->gems, sizeof(user->clone->cloakBadge));
            CUser::GetGuildName(target, user->clone->guildName);
            user->clone->packetLength = shape_size_with_cloak;
        }
        else
        {
            CUser::GetGuildName(target, user->clone->guildName);
            user->clone->packetLength = shape_size_without_cloak;
        }
    }

    void send_zone_shape(CUser* user, CUser* target)
    {
        UserShape shape{};
        shape.opcode = 0x303;
        shape.charId = user->id;

        if (user->shapeType == ShapeType::Disguise && user->clone)
        {
            shape.dead = user->clone->dead;
            shape.sitMode = user->clone->sitMode;
            shape.country = user->clone->country;
            shape.family = user->clone->family;
            shape.hair = user->clone->hair;
            shape.face = user->clone->face;
            shape.size = user->clone->size;
            shape.job = user->clone->job;
            shape.sex = user->clone->sex;
            shape.partyType = user->clone->partyType;
            shape.grow = user->clone->grow;
            shape.kills = user->clone->kills;

            memcpy(&shape.equipment, &user->clone->equipment, sizeof(shape.equipment));
            strncpy_s(shape.charName, user->clone->charName, sizeof(shape.charName));

            if (user->clone->packetLength == shape_size_with_cloak)
            {
                memcpy(&shape.cloakBadge, &user->clone->cloakBadge, sizeof(shape.cloakBadge));
                strncpy_s(shape.guildName, user->clone->guildName, sizeof(shape.guildName));
                SConnection::Send(target, &shape, shape_size_with_cloak);
            }
            else
            {
                memcpy(&shape.cloakBadge, user->clone->guildName, sizeof(user->clone->guildName));
                SConnection::Send(target, &shape, shape_size_without_cloak);
            }

            return;
        }

        shape.dead = user->stateType == StateType::Death ? true : false;
        shape.sitMode = user->sitMode;
        shape.country = user->country;
        shape.family = user->family;
        shape.hair = user->hair;
        shape.face = user->face;
        shape.size = user->size;
        shape.job = user->job;
        shape.sex = user->sex;
        shape.partyType = CUser::GetPartyType(user);
        shape.grow = user->grow;
        shape.kills = user->kills;

        for (int slot = 0; slot < max_equipment_slot; ++slot)
        {
            if (user->inventory[0][slot])
            {
                shape.equipment[slot].type = user->inventory[0][slot]->type;
                shape.equipment[slot].typeId = user->inventory[0][slot]->typeId;
                shape.equipment[slot].enchantStep = CItem::GetEnchantStep(user->inventory[0][slot]);
            }
        }

        strncpy_s(shape.charName, user->charName, sizeof(shape.charName));

        if (user->inventory[0][EquipmentSlot::Cloak])
        {
            memcpy(&shape.cloakBadge, &user->inventory[0][EquipmentSlot::Cloak]->gems, sizeof(shape.cloakBadge));
            CUser::GetGuildName(user, shape.guildName);
            SConnection::Send(target, &shape, shape_size_with_cloak);
        }
        else
        {
            CUser::GetGuildName(user, reinterpret_cast<char*>(&shape.cloakBadge));
            SConnection::Send(target, &shape, shape_size_without_cloak);
        }
    }

    void send_zone_view(CUser* user)
    {
        if (!user->zone)
            return;

        UserShape shape{};
        shape.opcode = 0x303;
        shape.charId = user->id;

        if (user->shapeType == ShapeType::Disguise && user->clone)
        {
            shape.dead = user->clone->dead;
            shape.sitMode = user->clone->sitMode;
            shape.country = user->clone->country;
            shape.family = user->clone->family;
            shape.hair = user->clone->hair;
            shape.face = user->clone->face;
            shape.size = user->clone->size;
            shape.job = user->clone->job;
            shape.sex = user->clone->sex;
            shape.partyType = user->clone->partyType;
            shape.grow = user->clone->grow;
            shape.kills = user->clone->kills;

            memcpy(&shape.equipment, &user->clone->equipment, sizeof(shape.equipment));
            strncpy_s(shape.charName, user->clone->charName, sizeof(shape.charName));

            if (user->clone->packetLength == shape_size_with_cloak)
            {
                memcpy(&shape.cloakBadge, &user->clone->cloakBadge, sizeof(shape.cloakBadge));
                strncpy_s(shape.guildName, user->clone->guildName, sizeof(shape.guildName));
                CZone::SendView(user->zone, &shape, shape_size_with_cloak, user->cellX, user->cellZ);
            }
            else
            {
                memcpy(&shape.cloakBadge, user->clone->guildName, sizeof(user->clone->guildName));
                CZone::SendView(user->zone, &shape, shape_size_without_cloak, user->cellX, user->cellZ);
            }

            return;
        }

        shape.dead = user->stateType == StateType::Death ? true : false;
        shape.sitMode = user->sitMode;
        shape.country = user->country;
        shape.family = user->family;
        shape.hair = user->hair;
        shape.face = user->face;
        shape.size = user->size;
        shape.job = user->job;
        shape.sex = user->sex;
        shape.partyType = CUser::GetPartyType(user);
        shape.grow = user->grow;
        shape.kills = user->kills;

        for (int slot = 0; slot < max_equipment_slot; ++slot)
        {
            if (user->inventory[0][slot])
            {
                shape.equipment[slot].type = user->inventory[0][slot]->type;
                shape.equipment[slot].typeId = user->inventory[0][slot]->typeId;
                shape.equipment[slot].enchantStep = CItem::GetEnchantStep(user->inventory[0][slot]);
            }
        }

        strncpy_s(shape.charName, user->charName, sizeof(shape.charName));

        if (user->inventory[0][EquipmentSlot::Cloak])
        {
            memcpy(&shape.cloakBadge, &user->inventory[0][EquipmentSlot::Cloak]->gems, sizeof(shape.cloakBadge));
            CUser::GetGuildName(user, shape.guildName);
            CZone::SendView(user->zone, &shape, shape_size_with_cloak, user->cellX, user->cellZ);
        }
        else
        {
            CUser::GetGuildName(user, reinterpret_cast<char*>(&shape.cloakBadge));
            CZone::SendView(user->zone, &shape, shape_size_without_cloak, user->cellX, user->cellZ);
        }
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
        call user_shape::send_zone_shape
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
        call user_shape::send_zone_view
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
}
