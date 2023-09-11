#include <map>
#include <random>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>

#include <shaiya/packets/0717.h>
#include <shaiya/packets/0806.h>
#include <shaiya/packets/0807.h>
#include <shaiya/packets/080D.h>
#include <shaiya/include/CGameData.h>
#include <shaiya/include/CItem.h>
#include <shaiya/include/CUser.h>
#include <shaiya/include/CZone.h>
#include <shaiya/include/SConnection.h>
#include <shaiya/include/SConnectionTServerReconnect.h>
using namespace shaiya;

namespace packet_gem
{
    typedef unsigned char EnchantStep;
    typedef unsigned int ItemId;

    // max is 99
    constexpr int req_wis_out_of_range = 100;
    constexpr int max_item_slot = 24;
    constexpr ItemId weapon_lapisian_plus = 95004;
    constexpr ItemId hot_time_lapisian = 95005;
    constexpr ItemId armor_lapisian_plus = 95009;

    const std::map<ItemId, EnchantStep> perfect_weapon_lapisian
    {
        {95022,0},
        {95023,1},
        {95024,2},
        {95025,3},
        {95026,4},
        {95027,5},
        {95028,6},
        {95029,7},
        {95030,8},
        {95031,9},
        {95032,10},
        {95033,11},
        {95034,12},
        {95035,13},
        {95036,14},
        {95037,15},
        {95038,16},
        {95039,17},
        {95040,18},
        {95041,19}
    };

    const std::map<ItemId, EnchantStep> perfect_armor_lapisian
    {
        {95042,0},
        {95043,1},
        {95044,2},
        {95045,3},
        {95046,4},
        {95047,5},
        {95048,6},
        {95049,7},
        {95050,8},
        {95051,9},
        {95052,10},
        {95053,11},
        {95054,12},
        {95055,13},
        {95056,14},
        {95057,15},
        {95058,16},
        {95059,17},
        {95060,18},
        {95061,19}
    };

    int find_available_slot(CUser* user, int bag)
    {
        for (int slot = 0; slot < max_item_slot; ++slot)
            if (!user->inventory[bag][slot])
                return slot;

        return -1;
    }

    bool is_perfect_lapisian(CItem* lapisian, CItem* upgradeItem)
    {
        auto enchant_step = CItem::GetEnchantStep(upgradeItem);
        auto item_id = lapisian->itemInfo->itemId;

        if (CItem::IsWeapon(upgradeItem))
        {
            if (enchant_step < 10)
                if (item_id == weapon_lapisian_plus || item_id == hot_time_lapisian)
                    return true;

            auto it = perfect_weapon_lapisian.find(lapisian->itemInfo->itemId);
            if (it != perfect_weapon_lapisian.end())
                if (it->second == CItem::GetEnchantStep(upgradeItem))
                    return true;
        }
        else
        {
            if (enchant_step < 10)
                if (item_id == armor_lapisian_plus || item_id == hot_time_lapisian)
                    return true;

            auto it = perfect_armor_lapisian.find(lapisian->itemInfo->itemId);
            if (it != perfect_armor_lapisian.end())
                if (it->second == CItem::GetEnchantStep(upgradeItem))
                    return true;
        }

        return false;
    }

    void rune_combine_handler(CUser* user, Packet packet)
    {
        if (!user->zone)
            return;

        auto npc_id = util::read_bytes<std::uint32_t>(packet, 6);
        if (!CZone::FindNpc(user->zone, npc_id))
            return;

        auto rune_bag_number = util::read_bytes<std::uint8_t>(packet, 2);
        auto rune_slot_number = util::read_bytes<std::uint8_t>(packet, 3);

        if (rune_bag_number > user->bagsUnlocked || rune_slot_number >= max_item_slot)
            return;

        auto rune = user->inventory[rune_bag_number][rune_slot_number];
        if (!rune)
            return;

        if (rune->count < 2 || rune->itemInfo->effect != CGameData::ItemEffect::ItemCompose)
        {
            RuneCombineResponse response{ 0x80D, RuneCombineResult::Failure };
            SConnection::Send(user, &response, 3);
            return;
        }

        auto vial_bag_number = util::read_bytes<std::uint8_t>(packet, 4);
        auto vial_slot_number = util::read_bytes<std::uint8_t>(packet, 5);

        if (vial_bag_number > user->bagsUnlocked || vial_slot_number >= max_item_slot)
            return;

        auto vial = user->inventory[vial_bag_number][vial_slot_number];
        if (!vial)
            return;

        CGameData::ItemInfo* info = nullptr;

        switch (vial->itemInfo->effect)
        {
        case CGameData::ItemEffect::ItemRemakeStr:
            info = CGameData::GetItemInfo(101, 1);
            break;
        case CGameData::ItemEffect::ItemRemakeDex:
            info = CGameData::GetItemInfo(101, 2);
            break;
        case CGameData::ItemEffect::ItemRemakeInt:
            info = CGameData::GetItemInfo(101, 3);
            break;
        case CGameData::ItemEffect::ItemRemakeWis:
            info = CGameData::GetItemInfo(101, 4);
            break;
        case CGameData::ItemEffect::ItemRemakeRec:
            info = CGameData::GetItemInfo(101, 5);
            break;
        case CGameData::ItemEffect::ItemRemakeLuc:
            info = CGameData::GetItemInfo(101, 6);
            break;
        default:
            RuneCombineResponse response{ 0x80D, RuneCombineResult::Failure };
            SConnection::Send(user, &response, 3);
            return;
        }

        if (info)
        {
            RuneCombineResponse response{ 0x80D, RuneCombineResult::Success, 1, 0, info->type, info->typeId };
            response.count = 1;

            while (response.bag <= user->bagsUnlocked)
            {
                response.slot = find_available_slot(user, response.bag);

                if (response.slot != -1)
                {
                    if (!CUser::ItemCreate(user, info, response.count))
                        break;

                    CUser::ItemUseNSend(user, rune_bag_number, rune_slot_number, false);
                    CUser::ItemUseNSend(user, rune_bag_number, rune_slot_number, false);
                    CUser::ItemUseNSend(user, vial_bag_number, vial_slot_number, false);

                    SConnection::Send(user, &response, sizeof(RuneCombineResponse));
                    break;
                }

                ++response.bag;
            }
        }
    }

    void item_compose_handler(CUser* user, Packet packet)
    {
        auto rune_bag_number = util::read_bytes<std::uint8_t>(packet, 2);
        auto rune_slot_number = util::read_bytes<std::uint8_t>(packet, 3);

        if (rune_bag_number > user->bagsUnlocked || rune_slot_number >= max_item_slot)
            return;

        auto rune = user->inventory[rune_bag_number][rune_slot_number];
        if (!rune)
            return;

        auto item_bag_number = util::read_bytes<std::uint8_t>(packet, 4);
        auto item_slot_number = util::read_bytes<std::uint8_t>(packet, 5);

        if (item_bag_number > user->bagsUnlocked || item_slot_number >= max_item_slot)
            return;

        auto item = user->inventory[item_bag_number][item_slot_number];
        if (!item)
            return;

        if (item->itemInfo->realType > CGameData::ItemRealType::Bracelet)
        {
            ItemComposeResponse response{ 0x806, ItemComposeResult::Failure };
            SConnection::Send(user, &response, 3);
            return;
        }

        if (!item->itemInfo->maxOjCount)
        {
            ItemComposeResponse response{ 0x806, ItemComposeResult::Failure };
            SConnection::Send(user, &response, 3);
            return;
        }

        if (item->itemInfo->reqWis <= 0 || item->itemInfo->reqWis >= req_wis_out_of_range)
        {
            ItemComposeResponse response{ 0x806, ItemComposeResult::Failure };
            SConnection::Send(user, &response, 3);
            return;
        }

        // optional
        if (item->makeType == MakeType::Q)
        {
            ItemComposeResponse response{ 0x806, ItemComposeResult::Failure };
            SConnection::Send(user, &response, 3);
            return;
        }

        std::random_device seed;
        std::mt19937 eng(seed());

        std::uniform_int_distribution<int> uni(1, item->itemInfo->reqWis);
        std::uint8_t bonus = uni(eng);
        std::string text = std::to_string(bonus);

        if (bonus < 10)
            text.insert(text.begin(), 1, '0');

        auto max_health = user->maxHealth;
        auto max_mana = user->maxHealth;
        auto max_stamina = user->maxHealth;

        switch (rune->itemInfo->effect)
        {
        case CGameData::ItemEffect::ItemCompose:
            if (!item_bag_number)
            {
                CUser::ItemEquipmentOptionRem(user, item);
                CItem::ReGenerationCraftExpansion(item, true);
                CUser::ItemEquipmentOptionAdd(user, item);

                if (!user->isInitEquipment)
                {
                    if (max_health != user->maxHealth)
                        CUser::SendMaxHP(user);

                    if (max_mana != user->maxMana)
                        CUser::SendMaxMP(user);

                    if (max_stamina != user->maxStamina)
                        CUser::SendMaxSP(user);
                }

                CUser::SetAttack(user);
                break;
            }

            CItem::ReGenerationCraftExpansion(item, true);

            break;
        case CGameData::ItemEffect::ItemComposeStr:
            if (!item->craftStrength)
                return;

            if (!item_bag_number)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftStrength = bonus;
                item->craftName.strength[0] = text[0];
                item->craftName.strength[1] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);

                if (!user->isInitEquipment)
                {
                    if (max_health != user->maxHealth)
                        CUser::SendMaxHP(user);

                    if (max_mana != user->maxMana)
                        CUser::SendMaxMP(user);

                    if (max_stamina != user->maxStamina)
                        CUser::SendMaxSP(user);
                }

                CUser::SetAttack(user);
                break;
            }

            item->craftStrength = bonus;
            item->craftName.strength[0] = text[0];
            item->craftName.strength[1] = text[1];

            break;
        case CGameData::ItemEffect::ItemComposeDex:
            if (!item->craftDexterity)
                return;

            if (!item_bag_number)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftDexterity = bonus;
                item->craftName.dexterity[0] = text[0];
                item->craftName.dexterity[1] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);

                if (!user->isInitEquipment)
                {
                    if (max_health != user->maxHealth)
                        CUser::SendMaxHP(user);

                    if (max_mana != user->maxMana)
                        CUser::SendMaxMP(user);

                    if (max_stamina != user->maxStamina)
                        CUser::SendMaxSP(user);
                }

                CUser::SetAttack(user);
                break;
            }

            item->craftDexterity = bonus;
            item->craftName.dexterity[0] = text[0];
            item->craftName.dexterity[1] = text[1];

            break;
        case CGameData::ItemEffect::ItemComposeInt:
            if (!item->craftIntelligence)
                return;

            if (!item_bag_number)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftIntelligence = bonus;
                item->craftName.intelligence[0] = text[0];
                item->craftName.intelligence[1] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);

                if (!user->isInitEquipment)
                {
                    if (max_health != user->maxHealth)
                        CUser::SendMaxHP(user);

                    if (max_mana != user->maxMana)
                        CUser::SendMaxMP(user);

                    if (max_stamina != user->maxStamina)
                        CUser::SendMaxSP(user);
                }

                CUser::SetAttack(user);
                break;
            }

            item->craftIntelligence = bonus;
            item->craftName.intelligence[0] = text[0];
            item->craftName.intelligence[1] = text[1];

            break;
        case CGameData::ItemEffect::ItemComposeWis:
            if (!item->craftWisdom)
                return;

            if (!item_bag_number)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftWisdom = bonus;
                item->craftName.wisdom[0] = text[0];
                item->craftName.wisdom[1] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);

                if (!user->isInitEquipment)
                {
                    if (max_health != user->maxHealth)
                        CUser::SendMaxHP(user);

                    if (max_mana != user->maxMana)
                        CUser::SendMaxMP(user);

                    if (max_stamina != user->maxStamina)
                        CUser::SendMaxSP(user);
                }

                CUser::SetAttack(user);
                break;
            }

            item->craftWisdom = bonus;
            item->craftName.wisdom[0] = text[0];
            item->craftName.wisdom[1] = text[1];

            break;
        case CGameData::ItemEffect::ItemComposeRec:
            if (!item->craftReaction)
                return;

            if (!item_bag_number)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftReaction = bonus;
                item->craftName.reaction[0] = text[0];
                item->craftName.reaction[1] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);

                if (!user->isInitEquipment)
                {
                    if (max_health != user->maxHealth)
                        CUser::SendMaxHP(user);

                    if (max_mana != user->maxMana)
                        CUser::SendMaxMP(user);

                    if (max_stamina != user->maxStamina)
                        CUser::SendMaxSP(user);
                }

                CUser::SetAttack(user);
                break;
            }

            item->craftReaction = bonus;
            item->craftName.reaction[0] = text[0];
            item->craftName.reaction[1] = text[1];

            break;
        case CGameData::ItemEffect::ItemComposeLuc:
            if (!item->craftLuck)
                return;

            if (!item_bag_number)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftLuck = bonus;
                item->craftName.luck[0] = text[0];
                item->craftName.luck[1] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);

                if (!user->isInitEquipment)
                {
                    if (max_health != user->maxHealth)
                        CUser::SendMaxHP(user);

                    if (max_mana != user->maxMana)
                        CUser::SendMaxMP(user);

                    if (max_stamina != user->maxStamina)
                        CUser::SendMaxSP(user);
                }

                CUser::SetAttack(user);
                break;
            }

            item->craftLuck = bonus;
            item->craftName.luck[0] = text[0];
            item->craftName.luck[1] = text[1];

            break;
        default:
            ItemComposeResponse response{ 0x806, ItemComposeResult::Failure };
            SConnection::Send(user, &response, 3);
            return;
        }

        ItemComposeResponse response{ 0x806, ItemComposeResult::Success, item_bag_number, item_slot_number };
        std::memcpy(response.craftName, &item->craftName, sizeof(CraftName));
        SConnection::Send(user, &response, sizeof(ItemComposeResponse));

        DBItemCraftName item_craft_name{ 0x717, user->userId, item_bag_number, item_slot_number };
        std::memcpy(item_craft_name.craftName, &item->craftName, sizeof(CraftName));
        SConnectionTServerReconnect::Send(&item_craft_name, sizeof(DBItemCraftName));

        CUser::ItemUseNSend(user, rune_bag_number, rune_slot_number, false);
    }
}

unsigned u0x479FBC = 0x479FBC;
void __declspec(naked) naked_0x479FB4()
{
    __asm
    {
        movzx eax,word ptr[esi]
        cmp eax,0x80D
        je case_0x80D

        // original
        add eax,-0x801
        jmp u0x479FBC

        case_0x80D:
        pushad

        push esi // packet
        push edi // user
        call packet_gem::rune_combine_handler
        add esp,0x8
        
        popad

        pop edi
        pop esi
        pop ecx
        retn
    }
}

unsigned u0x47A00C = 0x47A00C;
void __declspec(naked) naked_0x47A003()
{
    __asm
    {
        pushad

        push esi // packet
        push edi // user
        call packet_gem::item_compose_handler
        add esp,0x8
        
        popad

        jmp u0x47A00C
    }
}

unsigned u0x47AAE0 = 0x47AAE0;
unsigned u0x46CCF5 = 0x46CCF5;
unsigned u0x46CD83 = 0x46CD83;
void __declspec(naked) naked_0x46CCF0()
{
    __asm
    {
        // original
        call u0x47AAE0

        pushad

        mov eax,[esp+0x3C]
        push eax // item
        push esi // lapisian
        call packet_gem::is_perfect_lapisian
        add esp,0x8
        test al,al
        
        popad

        jne add_enchant_step
        jmp u0x46CCF5

        add_enchant_step:
        // isWeapon
        movzx ecx,byte ptr[esp+0x18]
        // enchant step
        movzx edx,byte ptr[esp+0x13]
        lea edx,[ecx+edx*2]
        jmp u0x46CD83
    }
}

void hook::packet_gem()
{
    // CUser::PacketGem
    util::detour((void*)0x479FB4, naked_0x479FB4, 8);
    // CUser::PacketGem case 0x806
    util::detour((void*)0x47A003, naked_0x47A003, 9);
    // CUser::ItemLapisianAdd
    util::detour((void*)0x46CCF0, naked_0x46CCF0, 5);
}
