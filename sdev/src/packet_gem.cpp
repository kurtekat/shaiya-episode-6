//#define SHAIYA_EP6_4_PT_ENABLE_0806_HANDLER
#include <random>
#include <ranges>
#include <string>
#include <tuple>
#include <shaiya/include/common/ItemEffect.h>
#include <shaiya/include/common/ItemType.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CGameData.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/Helpers.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/Synthesis.h"
#include "include/shaiya/include/network/game/incoming/0800.h"
#include "include/shaiya/include/network/game/outgoing/0200.h"
#include "include/shaiya/include/network/game/outgoing/0800.h"
#include "include/shaiya/include/network/dbAgent/incoming/0700.h"
#include "include/shaiya/include/network/gameLog/incoming/0400.h"
using namespace shaiya;

namespace packet_gem
{
    bool remove_safety_charm(CUser* user, ItemLapisianAddIncoming* incoming)
    {
        if (!incoming->safetyCharm)
            return false;

        return Helpers::ItemRemove(user, ItemEffect::SafetyCharm, 1);
    }

    bool enable_perfect_enchant(CItem* lapisian, CItem* item)
    {
        constexpr int max_enchant_step = 20;
        constexpr int armor_difference = 50;

        auto enchantStep = CItem::GetEnchantStep(item);
        auto isWeapon = CItem::IsWeapon(item);

        if (!isWeapon && enchantStep > armor_difference)
            enchantStep -= armor_difference;

        if (enchantStep >= max_enchant_step)
            return false;

        auto successRate = lapisian->itemInfo->reqRec;
        if (successRate != 10000)
            return false;

        auto lapisianLv = lapisian->itemInfo->attackTime;
        if (!lapisianLv || lapisianLv > max_enchant_step)
            return false;

        // Hot Time Lapisia +1
        if (enchantStep < 10 && lapisian->itemInfo->itemId == 95005)
            return true;

        auto lapisianStep = lapisian->itemInfo->range;
        auto lapisianType = static_cast<uint8_t>(lapisian->itemInfo->country);

        if (isWeapon)
        {
            // Weapon Lapisia +1
            if (enchantStep < 10 && lapisian->itemInfo->itemId == 95004)
                return true;
            else if (enchantStep == lapisianStep && lapisianType == 0)
                return true;
        }
        else
        {
            // Armor Lapisia +1
            if (enchantStep < 10 && lapisian->itemInfo->itemId == 95009)
                return true;
            else if (enchantStep == lapisianStep && lapisianType == 1)
                return true;    
        }

        return false;
    }

    /// <summary>
    /// Handles incoming 0x80D packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void item_rune_combine_handler(CUser* user, ItemRuneCombineIncoming* incoming)
    {
        if (!incoming->runeBag || incoming->runeBag > user->bagsUnlocked || incoming->runeSlot >= max_inventory_slot)
            return;

        auto& rune = user->inventory[incoming->runeBag][incoming->runeSlot];
        if (!rune)
            return;

        if (!incoming->vialBag || incoming->vialBag > user->bagsUnlocked || incoming->vialSlot >= max_inventory_slot)
            return;

        auto& vial = user->inventory[incoming->vialBag][incoming->vialSlot];
        if (!vial)
            return;

        ItemRuneCombineOutgoing failure{};
        failure.result = ItemRuneCombineResult::Failure;

        if (rune->count < 2 || rune->itemInfo->effect != ItemEffect::ItemCompose)
        {
            Helpers::Send(user, &failure, 3);
            return;
        }

        ItemInfo* itemInfo = nullptr;

        switch (vial->itemInfo->effect)
        {
        case ItemEffect::ItemRemakeStr:
            itemInfo = CGameData::GetItemInfo(101, 1);
            break;
        case ItemEffect::ItemRemakeDex:
            itemInfo = CGameData::GetItemInfo(101, 2);
            break;
        case ItemEffect::ItemRemakeInt:
            itemInfo = CGameData::GetItemInfo(101, 3);
            break;
        case ItemEffect::ItemRemakeWis:
            itemInfo = CGameData::GetItemInfo(101, 4);
            break;
        case ItemEffect::ItemRemakeRec:
            itemInfo = CGameData::GetItemInfo(101, 5);
            break;
        case ItemEffect::ItemRemakeLuc:
            itemInfo = CGameData::GetItemInfo(101, 6);
            break;
        default:
            break;
        }

        if (!itemInfo)
        {
            Helpers::Send(user, &failure, 3);
            return;
        }
        
        int bag{}, slot{};
        if (!Helpers::ItemCreate(user, itemInfo, 1, bag, slot))
        {
            Helpers::Send(user, &failure, 3);
            return;
        }

        ItemRuneCombineOutgoing success(ItemRuneCombineResult::Success, bag, slot, itemInfo->type, itemInfo->typeId, 1);
        Helpers::Send(user, &success, sizeof(ItemRuneCombineOutgoing));

        Helpers::ItemRemove(user, incoming->runeBag, incoming->runeSlot, 2);
        Helpers::ItemRemove(user, incoming->vialBag, incoming->vialSlot, 1);
    }

    /// <summary>
    /// Handles incoming 0x80E packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void item_lapisian_combine_handler(CUser* user, ItemLapisianCombineIncoming* incoming)
    {
        if (!incoming->cubeBag || incoming->cubeBag > user->bagsUnlocked || incoming->cubeSlot >= max_inventory_slot)
            return;

        auto& cube = user->inventory[incoming->cubeBag][incoming->cubeSlot];
        if (!cube)
            return;

        // no effect :/
        if (cube->itemInfo->itemId != 101101)
            return;

        if (incoming->lapisianType != std::to_underlying(ItemType::Lapisian))
            return;

        auto itemInfo = CGameData::GetItemInfo(incoming->lapisianType, incoming->lapisianTypeId);
        if (!itemInfo)
            return;

        auto successRate = itemInfo->reqRec;
        if (successRate != 10000)
            return;

        auto lapisianLv = itemInfo->attackTime;
        if (lapisianLv < 6 || lapisianLv > 19)
            return;

        int requiredCount = itemInfo->reqLuc;
        if (!requiredCount)
            return;

        auto createType = incoming->lapisianType;
        auto createTypeId = incoming->lapisianTypeId + 1;

        auto createInfo = CGameData::GetItemInfo(createType, createTypeId);
        if (!createInfo)
            return;

        CUser::ItemUseNSend(user, incoming->cubeBag, incoming->cubeSlot, false);

        // Failure result values are unclear. The client executes the same code 
        // as long as the value is non-zero and not greater than 3.

        ItemLapisianCombineOutgoing failure{};
        failure.result = ItemLapisianCombineResult::Unknown1;

        for (int i = 0; i < requiredCount; ++i)
        {
            if (!Helpers::ItemRemove(user, itemInfo->itemId, 1))
            {
                Helpers::Send(user, &failure, 3);
                return;
            }
        }

        int bag{}, slot{};
        if (!Helpers::ItemCreate(user, createInfo, 1, bag, slot))
        {
            Helpers::Send(user, &failure, 3);
            return;
        }

        ItemLapisianCombineOutgoing success(ItemLapisianCombineResult::Success, bag, slot, createInfo->type, createInfo->typeId, 1);
        Helpers::Send(user, &success, sizeof(ItemLapisianCombineOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x806 packets. Supports vanilla recreation runes.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void item_compose_handler(CUser* user, ItemComposeIncoming* incoming)
    {
        constexpr uint16_t max_bonus = 99;

        if (!incoming->runeBag || incoming->runeBag > user->bagsUnlocked || incoming->runeSlot >= max_inventory_slot)
            return;

        auto& rune = user->inventory[incoming->runeBag][incoming->runeSlot];
        if (!rune)
            return;

        if (incoming->itemBag > user->bagsUnlocked || incoming->itemSlot >= max_inventory_slot)
            return;

        auto& item = user->inventory[incoming->itemBag][incoming->itemSlot];
        if (!item)
            return;

        ItemComposeOutgoing outgoing{};
        outgoing.result = ItemComposeResult::Failure;

        if (!item->itemInfo->composeCount)
        {
            Helpers::Send(user, &outgoing, 3);
            return;
        }

        if (!item->itemInfo->reqWis || item->itemInfo->reqWis > max_bonus)
        {
            Helpers::Send(user, &outgoing, 3);
            return;
        }

        // optional
        //if (item->makeType == MakeType::QuestResult)
        //{
        //    Helpers::Send(user, &outgoing, 3);
        //    return;
        //}

        auto oldItemUid = item->uniqueId;
        auto oldItemId = item->itemInfo->itemId;
        auto oldCraftName = item->craftName;

        auto maxBonus = item->itemInfo->reqWis;

        switch (rune->itemInfo->effect)
        {
        case ItemEffect::ItemComposeStr:
        case ItemEffect::ItemComposeDex:
        case ItemEffect::ItemComposeInt:
        case ItemEffect::ItemComposeWis:
        case ItemEffect::ItemComposeRec:
        case ItemEffect::ItemComposeLuc:
        {
            maxBonus *= 2;
            maxBonus = (maxBonus > max_bonus) ? max_bonus : maxBonus;
            break;
        }
        default:
            break;
        }

        std::random_device seed;
        std::mt19937 eng(seed());

        std::uniform_int_distribution<uint16_t> uni(1, maxBonus);
        auto bonus = uni(eng);
        auto text = std::to_string(bonus);

        if (bonus < 10)
            text.insert(text.begin(), 1, '0');

        auto maxHealth = user->maxHealth;
        auto maxMana = user->maxHealth;
        auto maxStamina = user->maxHealth;

        switch (rune->itemInfo->effect)
        {
        case ItemEffect::ItemCompose:
            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);
                CItem::ReGenerationCraftExpansion(item, true);
                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            CItem::ReGenerationCraftExpansion(item, true);

            break;
        case ItemEffect::ItemComposeStr:
            if (!item->craftStrength)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftStrength = bonus;
                item->craftName[0] = text[0];
                item->craftName[1] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            item->craftStrength = bonus;
            item->craftName[0] = text[0];
            item->craftName[1] = text[1];

            break;
        case ItemEffect::ItemComposeDex:
            if (!item->craftDexterity)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftDexterity = bonus;
                item->craftName[2] = text[0];
                item->craftName[3] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            item->craftDexterity = bonus;
            item->craftName[2] = text[0];
            item->craftName[3] = text[1];

            break;
        case ItemEffect::ItemComposeInt:
            if (!item->craftIntelligence)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftIntelligence = bonus;
                item->craftName[6] = text[0];
                item->craftName[7] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            item->craftIntelligence = bonus;
            item->craftName[6] = text[0];
            item->craftName[7] = text[1];

            break;
        case ItemEffect::ItemComposeWis:
            if (!item->craftWisdom)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftWisdom = bonus;
                item->craftName[8] = text[0];
                item->craftName[9] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            item->craftWisdom = bonus;
            item->craftName[8] = text[0];
            item->craftName[9] = text[1];

            break;
        case ItemEffect::ItemComposeRec:
            if (!item->craftReaction)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftReaction = bonus;
                item->craftName[4] = text[0];
                item->craftName[5] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            item->craftReaction = bonus;
            item->craftName[4] = text[0];
            item->craftName[5] = text[1];

            break;
        case ItemEffect::ItemComposeLuc:
            if (!item->craftLuck)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftLuck = bonus;
                item->craftName[10] = text[0];
                item->craftName[11] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            item->craftLuck = bonus;
            item->craftName[10] = text[0];
            item->craftName[11] = text[1];

            break;
        default:
            Helpers::Send(user, &outgoing, 3);
            return;
        }

        if (!incoming->itemBag)
        {
            if (!user->ignoreMaxHpMpSpSpeed)
            {
                if (maxHealth != user->maxHealth)
                    CUser::SendMaxHP(user);

                if (maxMana != user->maxMana)
                    CUser::SendMaxMP(user);

                if (maxStamina != user->maxStamina)
                    CUser::SendMaxSP(user);
            }

            CUser::SetAttack(user);
        }

        outgoing.result = ItemComposeResult::Success;
        outgoing.bag = incoming->itemBag;
        outgoing.slot = incoming->itemSlot;
        outgoing.craftName = item->craftName;
        Helpers::Send(user, &outgoing, sizeof(ItemComposeOutgoing));

        DBAgentItemCraftNameIncoming packet(user->userId, incoming->itemBag, incoming->itemSlot, item->craftName);
        Helpers::SendDBAgent(&packet, sizeof(DBAgentItemCraftNameIncoming));

        GameLogItemComposeIncoming gameLog(user, item, oldItemUid, oldItemId, oldCraftName);
        Helpers::SendGameLog(&gameLog, sizeof(GameLogItemComposeIncoming));

        CUser::ItemUseNSend(user, incoming->runeBag, incoming->runeSlot, false);
    }

    /// <summary>
    /// Handles incoming 0x830 packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void item_synthesis_list_handler(CUser* user, ItemSynthesisListIncoming* incoming)
    {
        constexpr auto gold_per_percentage = 100'000'000;

        if (!incoming->squareBag || incoming->squareBag > user->bagsUnlocked || incoming->squareSlot >= max_inventory_slot)
            return;

        auto& square = user->inventory[incoming->squareBag][incoming->squareSlot];
        if (!square)
            return;

        if (square->itemInfo->effect != ItemEffect::ChaoticSquare)
            return;

        auto synthesis = g_synthesis.find(square->itemInfo->itemId);
        if (synthesis == g_synthesis.end())
            return;

        user->recallItemBag = incoming->squareBag;
        user->recallItemSlot = incoming->squareSlot;

        CUser::CancelActionExc(user);
        MyShop::Ended(&user->myShop);

        ItemSynthesisListOutgoing outgoing{};
        outgoing.goldPerPercentage = gold_per_percentage;

        auto itemList = std::ranges::views::zip(
            outgoing.createType,
            outgoing.createTypeId
        );

        int index = 0;
        for (const auto& synthesis : synthesis->second)
        {
            std::get<0>(itemList[index]) = synthesis.createType;
            std::get<1>(itemList[index]) = synthesis.createTypeId;

            ++index;

            if (std::cmp_less(index, itemList.size()))
                continue;
            else
            {
                Helpers::Send(user, &outgoing, sizeof(ItemSynthesisListOutgoing));

                std::fill(itemList.begin(), itemList.end(), std::tuple(0, 0));
                index = 0;
            }
        }

        if (!index)
            return;

        Helpers::Send(user, &outgoing, sizeof(ItemSynthesisListOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x831 packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void item_synthesis_material_handler(CUser* user, ItemSynthesisMaterialIncoming* incoming)
    {
        auto& square = user->inventory[user->recallItemBag][user->recallItemSlot];
        if (!square)
            return;

        if (square->itemInfo->effect != ItemEffect::ChaoticSquare)
            return;

        auto it = g_synthesis.find(square->itemInfo->itemId);
        if (it == g_synthesis.end())
            return;

        if (incoming->index >= it->second.size())
            return;

        auto& synthesis = it->second[incoming->index];
        if (incoming->createType != synthesis.createType || incoming->createTypeId != synthesis.createTypeId)
            return;

        ItemSynthesisMaterialOutgoing outgoing{};
        outgoing.successRate = synthesis.successRate;
        outgoing.materialType = synthesis.materialType;
        outgoing.createType = synthesis.createType;
        outgoing.materialTypeId = synthesis.materialTypeId;
        outgoing.createTypeId = synthesis.createTypeId;
        outgoing.materialCount = synthesis.materialCount;
        outgoing.createCount = synthesis.createCount;
        Helpers::Send(user, &outgoing, sizeof(ItemSynthesisMaterialOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x832 packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void item_synthesis_handler(CUser* user, ItemSynthesisIncoming* incoming)
    {
        constexpr auto gold_per_percentage = 100'000'000;
        constexpr auto max_gold_per_percentage = gold_per_percentage * 5;
        constexpr auto min_success_rate = 100;
        constexpr auto max_success_rate = 10000;

        if (!incoming->squareBag || incoming->squareBag > user->bagsUnlocked || incoming->squareSlot >= max_inventory_slot)
            return;

        auto& square = user->inventory[incoming->squareBag][incoming->squareSlot];
        if (!square)
            return;

        if (square->itemInfo->effect != ItemEffect::ChaoticSquare)
            return;

        auto it = g_synthesis.find(square->itemInfo->itemId);
        if (it == g_synthesis.end())
            return;

        if (incoming->index >= it->second.size())
            return;

        auto& synthesis = it->second[incoming->index];
        auto createInfo = CGameData::GetItemInfo(synthesis.createType, synthesis.createTypeId);
        if (!createInfo)
            return;

        if (incoming->money > user->money)
            return;

        auto money = incoming->money;
        if (money > max_gold_per_percentage)
            money = max_gold_per_percentage;

        auto successRate = synthesis.successRate;
        if (money >= gold_per_percentage && gold_per_percentage > 0)
            successRate += (money / gold_per_percentage) * 100;

        if (incoming->hammerBag != 0)
        {
            if (incoming->hammerBag > user->bagsUnlocked || incoming->hammerSlot >= max_inventory_slot)
                return;

            auto& hammer = user->inventory[incoming->hammerBag][incoming->hammerSlot];
            if (!hammer)
                return;

            if (hammer->itemInfo->effect != ItemEffect::CraftingHammer)
                return;

            successRate += hammer->itemInfo->reqVg * 100;
            CUser::ItemUseNSend(user, incoming->hammerBag, incoming->hammerSlot, false);
        }

        CUser::ItemUseNSend(user, incoming->squareBag, incoming->squareSlot, false);

        user->money -= money;
        CUser::SendDBMoney(user);

        int randomRate = 0;
        if (successRate < max_success_rate)
        {
            std::random_device seed;
            std::mt19937 eng(seed());

            std::uniform_int_distribution<int> uni(min_success_rate, max_success_rate);
            randomRate = uni(eng);
        }

        const auto& materials = std::ranges::views::zip(
            std::as_const(synthesis.materialType),
            std::as_const(synthesis.materialTypeId),
            std::as_const(synthesis.materialCount)
        );

        ItemSynthesisOutgoing outgoing{};
        outgoing.result = ItemSynthesisResult::Failure;

        for (const auto& [type, typeId, count] : materials)
        {
            auto itemInfo = CGameData::GetItemInfo(type, typeId);
            if (!itemInfo)
                continue;

            if (!Helpers::ItemRemove(user, itemInfo->itemId, count))
            {
                Helpers::Send(user, &outgoing, sizeof(ItemSynthesisOutgoing));
                return;
            }
        }

        if (randomRate <= successRate)
        {
            if (CUser::ItemCreate(user, createInfo, synthesis.createCount))
                outgoing.result = ItemSynthesisResult::Success;
        }

        Helpers::Send(user, &outgoing, sizeof(ItemSynthesisOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x833 packets. This feature will not be implemented.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void item_free_synthesis_handler(CUser* user, ItemFreeSynthesisIncoming* incoming)
    {
    }

    /// <summary>
    /// Handles incoming 0x811 packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void item_ability_transfer_handler(CUser* user, ItemAbilityTransferIncoming* incoming)
    {
        constexpr auto min_success_rate = 30;
        constexpr auto max_success_rate = 100;

        if (!incoming->cubeBag || incoming->cubeBag > user->bagsUnlocked || incoming->cubeSlot >= max_inventory_slot)
            return;

        auto& cube = user->inventory[incoming->cubeBag][incoming->cubeSlot];
        if (!cube)
            return;

        if (cube->itemInfo->effect != ItemEffect::ItemAbilityTransfer)
            return;

        if (incoming->fromBag > user->bagsUnlocked || incoming->fromSlot >= max_inventory_slot)
            return;

        auto& from = user->inventory[incoming->fromBag][incoming->fromSlot];
        if (!from)
            return;

        if (incoming->toBag > user->bagsUnlocked || incoming->toSlot >= max_inventory_slot)
            return;

        auto& to = user->inventory[incoming->toBag][incoming->toSlot];
        if (!to)
            return;

        if (to->itemInfo->realType != from->itemInfo->realType)
            return;

        if (to->itemInfo->reqLevel < from->itemInfo->reqLevel)
            return;

        if (to->itemInfo->slotCount < from->itemInfo->slotCount)
            return;

        if (to->itemInfo->composeCount < from->itemInfo->composeCount)
            return;

        if (to->itemInfo->reqWis < from->itemInfo->reqWis)
            return;

        int successRate = min_success_rate;
        if (incoming->catalystSlot != 255)
        {
            if (!incoming->catalystBag || incoming->catalystBag > user->bagsUnlocked || incoming->catalystSlot >= max_inventory_slot)
                return;

            auto& catalyst = user->inventory[incoming->catalystBag][incoming->catalystSlot];
            if (!catalyst)
                return;

            if (catalyst->itemInfo->effect != ItemEffect::Catalyst)
                return;

            successRate += catalyst->itemInfo->reqVg;
            CUser::ItemUseNSend(user, incoming->catalystBag, incoming->catalystSlot, false);
        }

        CUser::ItemUseNSend(user, incoming->cubeBag, incoming->cubeSlot, false);

        int randomRate = 0;
        if (successRate < max_success_rate)
        {
            std::random_device seed;
            std::mt19937 eng(seed());

            std::uniform_int_distribution<int> uni(1, max_success_rate);
            randomRate = uni(eng);
        }

        auto toOldItemUid = to->uniqueId;
        auto toOldItemId = to->itemInfo->itemId;
        auto toOldCraftName = to->craftName;

        auto fromOldItemUid = from->uniqueId;
        auto fromOldItemId = from->itemInfo->itemId;
        auto fromOldCraftName = from->craftName;

        auto result = ItemAbilityTransferResult::Failure;
        ItemAbilityTransferOutgoing outgoing(result, incoming->fromBag, incoming->fromSlot, incoming->toBag, incoming->toSlot);

        if (randomRate <= successRate)
        {
            outgoing.result = ItemAbilityTransferResult::Success;

            auto maxHealth = user->maxHealth;
            auto maxMana = user->maxHealth;
            auto maxStamina = user->maxHealth;

            if (!incoming->toBag)
            {
                CUser::ItemEquipmentOptionRem(user, to);

                to->gems = from->gems;
                to->craftName = from->craftName;
                to->craftStrength = from->craftStrength;
                to->craftDexterity = from->craftDexterity;
                to->craftReaction = from->craftReaction;
                to->craftIntelligence = from->craftIntelligence;
                to->craftWisdom = from->craftWisdom;
                to->craftLuck = from->craftLuck;
                to->craftHealth = from->craftHealth;
                to->craftMana = from->craftMana;
                to->craftStamina = from->craftStamina;
                to->craftAttackPower = from->craftAttackPower;
                to->craftAbsorption = from->craftAbsorption;

                CUser::ItemEquipmentOptionAdd(user, to);
            }
            else
            {
                to->gems = from->gems;
                to->craftName = from->craftName;
                to->craftStrength = from->craftStrength;
                to->craftDexterity = from->craftDexterity;
                to->craftReaction = from->craftReaction;
                to->craftIntelligence = from->craftIntelligence;
                to->craftWisdom = from->craftWisdom;
                to->craftLuck = from->craftLuck;
                to->craftHealth = from->craftHealth;
                to->craftMana = from->craftMana;
                to->craftStamina = from->craftStamina;
                to->craftAttackPower = from->craftAttackPower;
                to->craftAbsorption = from->craftAbsorption;
            }
            
            if (!incoming->fromBag)
            {
                CUser::ItemEquipmentOptionRem(user, from);

                from->gems.fill(0);
                CItem::InitCraftExpansion(from);
                from->craftStrength = 0;
                from->craftDexterity = 0;
                from->craftReaction = 0;
                from->craftIntelligence = 0;
                from->craftWisdom = 0;
                from->craftLuck = 0;
                from->craftHealth = 0;
                from->craftMana = 0;
                from->craftStamina = 0;
                from->craftAttackPower = 0;
                from->craftAbsorption = 0;

                CUser::ItemEquipmentOptionAdd(user, from);
            }
            else
            {
                from->gems.fill(0);
                CItem::InitCraftExpansion(from);
                from->craftStrength = 0;
                from->craftDexterity = 0;
                from->craftReaction = 0;
                from->craftIntelligence = 0;
                from->craftWisdom = 0;
                from->craftLuck = 0;
                from->craftHealth = 0;
                from->craftMana = 0;
                from->craftStamina = 0;
                from->craftAttackPower = 0;
                from->craftAbsorption = 0;
            }

            if (!incoming->toBag || !incoming->fromBag)
            {
                if (!user->ignoreMaxHpMpSpSpeed)
                {
                    if (maxHealth != user->maxHealth)
                        CUser::SendMaxHP(user);

                    if (maxMana != user->maxMana)
                        CUser::SendMaxMP(user);

                    if (maxStamina != user->maxStamina)
                        CUser::SendMaxSP(user);
                }

                CUser::SetAttack(user);
            }

            DBAgentItemCraftNameIncoming packet1(user->userId, incoming->toBag, incoming->toSlot, to->craftName);
            Helpers::SendDBAgent(&packet1, sizeof(DBAgentItemCraftNameIncoming));

            DBAgentItemGemsIncoming packet2(user->userId, incoming->toBag, incoming->toSlot, to->gems, user->money);
            Helpers::SendDBAgent(&packet2, sizeof(DBAgentItemGemsIncoming));

            GameLogItemComposeIncoming gameLog1(user, to, toOldItemUid, toOldItemId, toOldCraftName);
            Helpers::SendGameLog(&gameLog1, sizeof(GameLogItemComposeIncoming));

            DBAgentItemCraftNameIncoming packet3(user->userId, incoming->fromBag, incoming->fromSlot, from->craftName);
            Helpers::SendDBAgent(&packet3, sizeof(DBAgentItemCraftNameIncoming));

            DBAgentItemGemsIncoming packet4(user->userId, incoming->fromBag, incoming->fromSlot, from->gems, user->money);
            Helpers::SendDBAgent(&packet4, sizeof(DBAgentItemGemsIncoming));

            GameLogItemComposeIncoming gameLog2(user, from, fromOldItemUid, fromOldItemId, fromOldCraftName);
            Helpers::SendGameLog(&gameLog2, sizeof(GameLogItemComposeIncoming));
        }

        Helpers::Send(user, &outgoing, sizeof(ItemAbilityTransferOutgoing));
    }

    void extended_handler(CUser* user, uint8_t* packet)
    {
        auto opcode = util::deserialize<uint16_t>(packet, 0);

        switch (opcode)
        {
        case 0x80D:
        {
            auto incoming = reinterpret_cast<ItemRuneCombineIncoming*>(packet);
            item_rune_combine_handler(user, incoming);
            break;
        }
        case 0x80E:
        {
            auto incoming = reinterpret_cast<ItemLapisianCombineIncoming*>(packet);
            item_lapisian_combine_handler(user, incoming);
            break;
        }
        case 0x811:
        {
            auto incoming = reinterpret_cast<ItemAbilityTransferIncoming*>(packet);
            item_ability_transfer_handler(user, incoming);
            break;
        }
        case 0x830:
        {
            auto incoming = reinterpret_cast<ItemSynthesisListIncoming*>(packet);
            item_synthesis_list_handler(user, incoming);
            break;
        }
        case 0x831:
        {
            auto incoming = reinterpret_cast<ItemSynthesisMaterialIncoming*>(packet);
            item_synthesis_material_handler(user, incoming);
            break;
        }
        case 0x832:
        {
            auto incoming = reinterpret_cast<ItemSynthesisIncoming*>(packet);
            item_synthesis_handler(user, incoming);
            break;
        }
        case 0x833:
        {
            auto incoming = reinterpret_cast<ItemFreeSynthesisIncoming*>(packet);
            item_free_synthesis_handler(user, incoming);
            break;
        }
        default:
            SConnection::Close(&user->connection.connection, 9, 0);
            break;
        }
    }
}

unsigned u0x47A04B = 0x47A04B;
void __declspec(naked) naked_0x47A040()
{
    __asm
    {
        pushad

        push esi // packet
        push edi // user
        call packet_gem::extended_handler
        add esp,0x8

        popad

        jmp u0x47A04B
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
        call packet_gem::enable_perfect_enchant
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

unsigned u0x4D2960 = 0x4D2960;
unsigned u0x46CDB5 = 0x46CDB5;
void __declspec(naked) naked_0x46CDB0()
{
    __asm
    {
        // original
        call u0x4D2960

        pushad

        push ebx // packet
        push ebp // user
        call packet_gem::remove_safety_charm
        add esp,0x8

        popad

        jmp u0x46CDB5
    }
}

unsigned u0x46D598 = 0x46D598;
unsigned u0x46D3C4 = 0x46D3C4;
void __declspec(naked) naked_0x46D3BC()
{
    __asm
    {
        pushad

        push ebx // packet
        push ebp // user
        call packet_gem::remove_safety_charm
        add esp,0x8
        test al,al

        popad

        jne _0x46D598

        // original
        movzx eax,byte ptr[ebx+0x7]
        movzx ebx,byte ptr[ebx+0x8]
        jmp u0x46D3C4

        _0x46D598:
        jmp u0x46D598
    }
}

void hook::packet_gem()
{
    // CUser::PacketGem (default case)
    util::detour((void*)0x47A040, naked_0x47A040, 6);
    // CUser::ItemLapisianAdd
    util::detour((void*)0x46CCF0, naked_0x46CCF0, 5);
    // CUser::ItemLapisianAdd (success)
    util::detour((void*)0x46CDB0, naked_0x46CDB0, 5);
    // CUser::ItemLapisianAdd (failure)
    util::detour((void*)0x46D3BC, naked_0x46D3BC, 8);

#ifdef SHAIYA_EP6_4_PT_ENABLE_0806_HANDLER
    // CUser::PacketGem case 0x806
    util::detour((void*)0x47A003, naked_0x47A003, 9);
#endif
}
