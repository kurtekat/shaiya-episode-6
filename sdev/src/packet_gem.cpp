//#define SHAIYA_EP6_4_ENABLE_0806_HANDLER
#include <random>
#include <ranges>
#include <string>
#include <tuple>
#include <shaiya/include/common/ItemTypes.h>
#include <util/util.h>
#include "include/main.h"
#include "include/shaiya/include/CGameData.h"
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/ItemHelper.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/ItemRemake.h"
#include "include/shaiya/include/NetworkHelper.h"
#include "include/shaiya/include/Synthesis.h"
#include "include/shaiya/include/UserHelper.h"
#include "include/shaiya/include/network/game/incoming/0800.h"
#include "include/shaiya/include/network/game/outgoing/0200.h"
#include "include/shaiya/include/network/game/outgoing/0800.h"
#include "include/shaiya/include/network/dbAgent/incoming/0700.h"
#include "include/shaiya/include/network/gameLog/incoming/0400.h"
using namespace shaiya;

namespace packet_gem
{
    /// <summary>
    /// Adds support for enchant safety charms.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    /// <returns></returns>
    bool remove_safety_charm(CUser* user, ItemLapisianAddIncoming_EP6_4* incoming)
    {
        if (!incoming->safetyCharm)
            return false;

        return UserHelper::ItemRemove(user, ItemEffect::SafetyCharm, 1);
    }

    /// <summary>
    /// Adds support for perfect lapisian.
    /// </summary>
    /// <param name="lapisian"></param>
    /// <param name="item"></param>
    /// <returns></returns>
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
        auto lapisianType = uint8_t(lapisian->itemInfo->country);

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
    /// Handles incoming 0x80B packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void item_lapis_combine_handler(CUser* user, ItemLapisCombineIncoming_EP6_4* incoming)
    {
        if (!incoming->lapisBag1 || incoming->lapisBag1 > user->bagsUnlocked || incoming->lapisSlot1 >= max_inventory_slot)
            return;

        auto& lapis1 = user->inventory[incoming->lapisBag1][incoming->lapisSlot1];
        if (!lapis1)
            return;

        if (lapis1->type != std::to_underlying(ItemType::Lapis))
            return;

        if (lapis1->itemInfo->reqIg == 30 || lapis1->itemInfo->reqIg == 99)
            return;

        if (!incoming->lapisBag2 || incoming->lapisBag2 > user->bagsUnlocked || incoming->lapisSlot2 >= max_inventory_slot)
            return;

        auto& lapis2 = user->inventory[incoming->lapisBag2][incoming->lapisSlot2];
        if (!lapis2)
            return;

        if (lapis2->type != std::to_underlying(ItemType::Lapis))
            return;

        if (lapis2->itemInfo->reqIg == 30 || lapis2->itemInfo->reqIg == 99)
            return;

        if (!incoming->lapisBag3 || incoming->lapisBag3 > user->bagsUnlocked || incoming->lapisSlot3 >= max_inventory_slot)
            return;

        auto& lapis3 = user->inventory[incoming->lapisBag3][incoming->lapisSlot3];
        if (!lapis3)
            return;

        if (lapis3->type != std::to_underlying(ItemType::Lapis))
            return;

        if (lapis3->itemInfo->reqIg == 30 || lapis3->itemInfo->reqIg == 99)
            return;

        if (!incoming->essenceBag || incoming->essenceBag > user->bagsUnlocked || incoming->essenceSlot >= max_inventory_slot)
            return;

        auto& essence = user->inventory[incoming->essenceBag][incoming->essenceSlot];
        if (!essence)
            return;

        // Requires 1 per lapis Lv5 or higher

        int requiredCount = 0;
        if (lapis1->itemInfo->reqIg >= 36)
            ++requiredCount;

        if (lapis2->itemInfo->reqIg >= 36)
            ++requiredCount;

        if (lapis3->itemInfo->reqIg >= 36)
            ++requiredCount;

        if (incoming->essenceCount < requiredCount)
            return;

        ItemLapisCombineOutgoing failure{};
        failure.result = ItemLapisCombineResult::Failure;

        if (essence->count < requiredCount || essence->itemInfo->effect != ItemEffect::CrowleyEssence)
        {
            NetworkHelper::Send(user, &failure, sizeof(ItemLapisCombineOutgoing));
            return;
        }

        auto itemId1 = lapis1->itemInfo->itemId;
        auto itemId2 = lapis2->itemInfo->itemId;
        auto itemId3 = lapis3->itemInfo->itemId;

        auto remake = std::find_if(g_itemRemake.begin(), g_itemRemake.end(), [&itemId1, &itemId2, &itemId3](const auto& remake) {
            return remake.itemId1 == itemId1 && remake.itemId2 == itemId2 && remake.itemId3 == itemId3;
            });

        if (remake == g_itemRemake.end())
        {
            NetworkHelper::Send(user, &failure, sizeof(ItemLapisCombineOutgoing));
            return;
        }

        auto itemInfo = CGameData::GetItemInfo(remake->createType, remake->createTypeId);
        if (!itemInfo)
        {
            NetworkHelper::Send(user, &failure, sizeof(ItemLapisCombineOutgoing));
            return;
        }

        int bag{}, slot{};
        if (!UserHelper::ItemCreate(user, itemInfo, 1, bag, slot))
        {
            NetworkHelper::Send(user, &failure, sizeof(ItemLapisCombineOutgoing));
            return;
        }

        UserHelper::ItemRemove(user, incoming->lapisBag1, incoming->lapisSlot1, 1);
        UserHelper::ItemRemove(user, incoming->lapisBag2, incoming->lapisSlot2, 1);
        UserHelper::ItemRemove(user, incoming->lapisBag3, incoming->lapisSlot3, 1);
        UserHelper::ItemRemove(user, incoming->essenceBag, incoming->essenceSlot, requiredCount);

        ItemLapisCombineOutgoing success(ItemLapisCombineResult::Success, bag, slot, itemInfo->type, itemInfo->typeId, 1);
        NetworkHelper::Send(user, &success, sizeof(ItemLapisCombineOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x80C packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void item_lapisian_combine_handler(CUser* user, ItemLapisianCombineIncoming_EP6_4* incoming)
    {
        if (!incoming->lapisianBag1 || incoming->lapisianBag1 > user->bagsUnlocked || incoming->lapisianSlot1 >= max_inventory_slot)
            return;

        auto& lapisian1 = user->inventory[incoming->lapisianBag1][incoming->lapisianSlot1];
        if (!lapisian1)
            return;

        if (lapisian1->type != std::to_underlying(ItemType::Lapisian))
            return;

        if (!incoming->lapisianBag2 || incoming->lapisianBag2 > user->bagsUnlocked || incoming->lapisianSlot2 >= max_inventory_slot)
            return;

        auto& lapisian2 = user->inventory[incoming->lapisianBag2][incoming->lapisianSlot2];
        if (!lapisian2)
            return;

        if (lapisian2->type != std::to_underlying(ItemType::Lapisian))
            return;

        if (!incoming->lapisianBag3 || incoming->lapisianBag3 > user->bagsUnlocked || incoming->lapisianSlot3 >= max_inventory_slot)
            return;

        auto& lapisian3 = user->inventory[incoming->lapisianBag3][incoming->lapisianSlot3];
        if (!lapisian3)
            return;

        if (lapisian3->type != std::to_underlying(ItemType::Lapisian))
            return;

        if (!incoming->liquidBag || incoming->liquidBag > user->bagsUnlocked || incoming->liquidSlot >= max_inventory_slot)
            return;

        auto& liquid = user->inventory[incoming->liquidBag][incoming->liquidSlot];
        if (!liquid)
            return;

        // Allows up to 3, but seems to require 1 no matter what

        int requiredCount = 1;
        if (incoming->liquidCount < requiredCount)
            return;

        ItemLapisianCombineOutgoing failure{};
        failure.result = ItemLapisianCombineResult::Failure;

        if (liquid->count < requiredCount || liquid->itemInfo->effect != ItemEffect::CrowleyLiquid)
        {
            NetworkHelper::Send(user, &failure, sizeof(ItemLapisianCombineOutgoing));
            return;
        }

        auto itemId1 = lapisian1->itemInfo->itemId;
        auto itemId2 = lapisian2->itemInfo->itemId;
        auto itemId3 = lapisian3->itemInfo->itemId;

        auto remake = std::find_if(g_itemRemake.begin(), g_itemRemake.end(), [&itemId1, &itemId2, &itemId3](const auto& remake) {
            return remake.itemId1 == itemId1 && remake.itemId2 == itemId2 && remake.itemId3 == itemId3;
            });

        if (remake == g_itemRemake.end())
        {
            NetworkHelper::Send(user, &failure, sizeof(ItemLapisianCombineOutgoing));
            return;
        }

        auto itemInfo = CGameData::GetItemInfo(remake->createType, remake->createTypeId);
        if (!itemInfo)
        {
            NetworkHelper::Send(user, &failure, sizeof(ItemLapisianCombineOutgoing));
            return;
        }

        int bag{}, slot{};
        if (!UserHelper::ItemCreate(user, itemInfo, 1, bag, slot))
        {
            NetworkHelper::Send(user, &failure, sizeof(ItemLapisianCombineOutgoing));
            return;
        }

        UserHelper::ItemRemove(user, incoming->lapisianBag1, incoming->lapisianSlot1, 1);
        UserHelper::ItemRemove(user, incoming->lapisianBag2, incoming->lapisianSlot2, 1);
        UserHelper::ItemRemove(user, incoming->lapisianBag3, incoming->lapisianSlot3, 1);
        UserHelper::ItemRemove(user, incoming->liquidBag, incoming->liquidSlot, requiredCount);

        ItemLapisianCombineOutgoing success(ItemLapisianCombineResult::Success, bag, slot, itemInfo->type, itemInfo->typeId, 1);
        NetworkHelper::Send(user, &success, sizeof(ItemLapisianCombineOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x80D packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void item_rune_combine_handler(CUser* user, ItemRuneCombineIncoming_EP6_4* incoming)
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

        if (rune->count < 2 || rune->itemInfo->effect != ItemEffect::RecreationRune)
        {
            NetworkHelper::Send(user, &failure, sizeof(ItemRuneCombineOutgoing));
            return;
        }

        ItemInfo* itemInfo = nullptr;

        switch (vial->itemInfo->effect)
        {
        case ItemEffect::StrVial:
            itemInfo = CGameData::GetItemInfo(101, 1);
            break;
        case ItemEffect::DexVial:
            itemInfo = CGameData::GetItemInfo(101, 2);
            break;
        case ItemEffect::IntVial:
            itemInfo = CGameData::GetItemInfo(101, 3);
            break;
        case ItemEffect::WisVial:
            itemInfo = CGameData::GetItemInfo(101, 4);
            break;
        case ItemEffect::RecVial:
            itemInfo = CGameData::GetItemInfo(101, 5);
            break;
        case ItemEffect::LucVial:
            itemInfo = CGameData::GetItemInfo(101, 6);
            break;
        default:
            break;
        }

        if (!itemInfo)
        {
            NetworkHelper::Send(user, &failure, sizeof(ItemRuneCombineOutgoing));
            return;
        }
        
        int bag{}, slot{};
        if (!UserHelper::ItemCreate(user, itemInfo, 1, bag, slot))
        {
            NetworkHelper::Send(user, &failure, sizeof(ItemRuneCombineOutgoing));
            return;
        }

        UserHelper::ItemRemove(user, incoming->runeBag, incoming->runeSlot, 2);
        UserHelper::ItemRemove(user, incoming->vialBag, incoming->vialSlot, 1);

        ItemRuneCombineOutgoing success(ItemRuneCombineResult::Success, bag, slot, itemInfo->type, itemInfo->typeId, 1);
        NetworkHelper::Send(user, &success, sizeof(ItemRuneCombineOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x80E packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void item_perfect_lapisian_combine_handler(CUser* user, ItemPerfectLapisianCombineIncoming* incoming)
    {
        if (!incoming->cubeBag || incoming->cubeBag > user->bagsUnlocked || incoming->cubeSlot >= max_inventory_slot)
            return;

        auto& cube = user->inventory[incoming->cubeBag][incoming->cubeSlot];
        if (!cube)
            return;

        // The data does not specify an item effect
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

        // Failure result values are unclear. The client executes the same code 
        // as long as the value is nonzero and not greater than 3.

        ItemPerfectLapisianCombineOutgoing failure{};
        failure.result = ItemPerfectLapisianCombineResult::Unknown1;

        auto createType = incoming->lapisianType;
        auto createTypeId = incoming->lapisianTypeId + 1;

        auto createInfo = CGameData::GetItemInfo(createType, createTypeId);
        if (!createInfo)
        {
            NetworkHelper::Send(user, &failure, sizeof(ItemPerfectLapisianCombineOutgoing));
            return;
        }

        CUser::ItemUseNSend(user, incoming->cubeBag, incoming->cubeSlot, false);

        for (int i = 0; i < requiredCount; ++i)
        {
            if (!UserHelper::ItemRemove(user, itemInfo->itemId, 1))
            {
                NetworkHelper::Send(user, &failure, sizeof(ItemPerfectLapisianCombineOutgoing));
                return;
            }
        }

        int bag{}, slot{};
        if (!UserHelper::ItemCreate(user, createInfo, 1, bag, slot))
        {
            NetworkHelper::Send(user, &failure, sizeof(ItemPerfectLapisianCombineOutgoing));
            return;
        }

        ItemPerfectLapisianCombineOutgoing success(ItemPerfectLapisianCombineResult::Success, bag, slot, createInfo->type, createInfo->typeId, 1);
        NetworkHelper::Send(user, &success, sizeof(ItemPerfectLapisianCombineOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x806 packets. Supports vanilla recreation runes. Adding custom 
    /// item effects (e.g., perfect) will require a client modification.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void item_compose_handler(CUser* user, ItemComposeIncoming_EP6_4* incoming)
    {
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

        ItemComposeOutgoing failure{};
        failure.result = ItemComposeResult::Failure;

        if (!item->itemInfo->composeCount)
        {
            NetworkHelper::Send(user, &failure, sizeof(ItemComposeOutgoing));
            return;
        }

        if (!item->itemInfo->reqWis || item->itemInfo->reqWis > 99)
        {
            NetworkHelper::Send(user, &failure, sizeof(ItemComposeOutgoing));
            return;
        }

        // optional
        //if (item->makeType == MakeType::QuestResult)
        //{
        //    NetworkHelper::Send(user, &failure, sizeof(ItemComposeOutgoing));
        //    return;
        //}

        auto oldItemUid = item->uniqueId;
        auto oldItemId = item->itemInfo->itemId;
        auto oldCraftName = item->craftName;
        auto maxBonus = item->itemInfo->reqWis;

        // See the item descriptions

        switch (rune->itemInfo->effect)
        {
        case ItemEffect::StrRecreationRune:
        case ItemEffect::DexRecreationRune:
        case ItemEffect::IntRecreationRune:
        case ItemEffect::WisRecreationRune:
        case ItemEffect::RecRecreationRune:
        case ItemEffect::LucRecreationRune:
        {
            maxBonus *= 2;
            maxBonus = (maxBonus > 99) ? 99 : maxBonus;
            break;
        }
        default:
            break;
        }

        std::random_device seed;
        std::mt19937 eng(seed());

        std::uniform_int_distribution<uint16_t> uni(1, maxBonus);
        auto bonus = uni(eng);

        auto maxHealth = user->maxHealth;
        auto maxMana = user->maxHealth;
        auto maxStamina = user->maxHealth;

        switch (rune->itemInfo->effect)
        {
        case ItemEffect::RecreationRune:
            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);
                CItem::ReGenerationCraftExpansion(item, true);
                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            CItem::ReGenerationCraftExpansion(item, true);

            break;
        case ItemEffect::StrRecreationRune:
            if (!item->craftStrength)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);
                ItemHelper::SetCraftStrength(item, bonus);
                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            ItemHelper::SetCraftStrength(item, bonus);

            break;
        case ItemEffect::DexRecreationRune:
            if (!item->craftDexterity)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);
                ItemHelper::SetCraftDexterity(item, bonus);
                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            ItemHelper::SetCraftDexterity(item, bonus);

            break;
        case ItemEffect::IntRecreationRune:
            if (!item->craftIntelligence)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);
                ItemHelper::SetCraftIntelligence(item, bonus);
                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            ItemHelper::SetCraftIntelligence(item, bonus);

            break;
        case ItemEffect::WisRecreationRune:
            if (!item->craftWisdom)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);
                ItemHelper::SetCraftWisdom(item, bonus);
                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            ItemHelper::SetCraftWisdom(item, bonus);

            break;
        case ItemEffect::RecRecreationRune:
            if (!item->craftReaction)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);
                ItemHelper::SetCraftReaction(item, bonus);
                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            ItemHelper::SetCraftReaction(item, bonus);

            break;
        case ItemEffect::LucRecreationRune:
            if (!item->craftLuck)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);
                ItemHelper::SetCraftLuck(item, bonus);
                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            ItemHelper::SetCraftLuck(item, bonus);

            break;
        default:
            NetworkHelper::Send(user, &failure, sizeof(ItemComposeOutgoing));
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

        CUser::ItemUseNSend(user, incoming->runeBag, incoming->runeSlot, false);

        DBAgentItemCraftNameIncoming packet(user->userId, incoming->itemBag, incoming->itemSlot, item->craftName);
        NetworkHelper::SendDBAgent(&packet, sizeof(DBAgentItemCraftNameIncoming));

        GameLogItemComposeIncoming gameLog(user, item, oldItemUid, oldItemId, oldCraftName);
        NetworkHelper::SendGameLog(&gameLog, sizeof(GameLogItemComposeIncoming));

        ItemComposeOutgoing success(ItemComposeResult::Success, incoming->itemBag, incoming->itemSlot, item->craftName);
        NetworkHelper::Send(user, &success, sizeof(ItemComposeOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x830 packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void item_synthesis_list_handler(CUser* user, ItemSynthesisListIncoming* incoming)
    {
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
        outgoing.goldPerPercentage = Synthesis::goldPerPercentage;

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
                NetworkHelper::Send(user, &outgoing, sizeof(ItemSynthesisListOutgoing));

                std::fill(itemList.begin(), itemList.end(), std::tuple(0, 0));
                index = 0;
            }
        }

        if (!index)
            return;

        NetworkHelper::Send(user, &outgoing, sizeof(ItemSynthesisListOutgoing));
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
        NetworkHelper::Send(user, &outgoing, sizeof(ItemSynthesisMaterialOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x832 packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void item_synthesis_handler(CUser* user, ItemSynthesisIncoming* incoming)
    {
        constexpr auto gold_per_percentage = Synthesis::goldPerPercentage;
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

            if (!UserHelper::ItemRemove(user, itemInfo->itemId, count))
            {
                NetworkHelper::Send(user, &outgoing, sizeof(ItemSynthesisOutgoing));
                return;
            }
        }

        if (randomRate <= successRate)
        {
            if (CUser::ItemCreate(user, createInfo, synthesis.createCount))
                outgoing.result = ItemSynthesisResult::Success;
        }

        NetworkHelper::Send(user, &outgoing, sizeof(ItemSynthesisOutgoing));
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
    /// Handles incoming 0x811 packets. PT clients do not support this feature.
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

        // 255 means the slot is empty
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
                ItemHelper::CopyCraftName(from, to);
                CUser::ItemEquipmentOptionAdd(user, to);
            }
            else
            {
                to->gems = from->gems;
                ItemHelper::CopyCraftName(from, to);
            }
            
            if (!incoming->fromBag)
            {
                CUser::ItemEquipmentOptionRem(user, from);
                from->gems.fill(0);
                ItemHelper::InitCraftName(from);
                CUser::ItemEquipmentOptionAdd(user, from);
            }
            else
            {
                from->gems.fill(0);
                ItemHelper::InitCraftName(from);
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

            NetworkHelper::SendDBAgentItemCraftName(user, to, incoming->toBag, incoming->toSlot);
            NetworkHelper::SendDBAgentItemGems(user, to, incoming->toBag, incoming->toSlot);

            GameLogItemComposeIncoming gameLog1(user, to, toOldItemUid, toOldItemId, toOldCraftName);
            NetworkHelper::SendGameLog(&gameLog1, sizeof(GameLogItemComposeIncoming));

            NetworkHelper::SendDBAgentItemCraftName(user, from, incoming->fromBag, incoming->fromSlot);
            NetworkHelper::SendDBAgentItemGems(user, from, incoming->fromBag, incoming->fromSlot);

            GameLogItemComposeIncoming gameLog2(user, from, fromOldItemUid, fromOldItemId, fromOldCraftName);
            NetworkHelper::SendGameLog(&gameLog2, sizeof(GameLogItemComposeIncoming));
        }

        NetworkHelper::Send(user, &outgoing, sizeof(ItemAbilityTransferOutgoing));
    }

    /// <summary>
    /// Adds support for 6.4 packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="packet"></param>
    void extended_handler(CUser* user, uint8_t* packet)
    {
        auto opcode = util::deserialize<uint16_t>(packet, 0);

        switch (opcode)
        {
        case 0x80B:
        {
            auto incoming = reinterpret_cast<ItemLapisCombineIncoming_EP6_4*>(packet);
            item_lapis_combine_handler(user, incoming);
            break;
        }
        case 0x80C:
        {
            auto incoming = reinterpret_cast<ItemLapisianCombineIncoming_EP6_4*>(packet);
            item_lapisian_combine_handler(user, incoming);
            break;
        }
        case 0x80D:
        {
            auto incoming = reinterpret_cast<ItemRuneCombineIncoming_EP6_4*>(packet);
            item_rune_combine_handler(user, incoming);
            break;
        }
        case 0x80E:
        {
            auto incoming = reinterpret_cast<ItemPerfectLapisianCombineIncoming*>(packet);
            item_perfect_lapisian_combine_handler(user, incoming);
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

#ifdef SHAIYA_EP6_4_ENABLE_0806_HANDLER
    // CUser::PacketGem case 0x806
    util::detour((void*)0x47A003, naked_0x47A003, 9);
#endif
}
