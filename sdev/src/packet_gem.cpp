//#define SHAIYA_EP6_4_ENABLE_0806_HANDLER
#include <random>
#include <ranges>
#include <string>
#include <tuple>
#include <util/util.h>
#include <shaiya/include/common/ItemTypes.h>
#include <shaiya/include/network/dbAgent/incoming/0700.h>
#include <shaiya/include/network/game/incoming/0800.h>
#include <shaiya/include/network/game/outgoing/0200.h>
#include <shaiya/include/network/game/outgoing/0800.h>
#include <shaiya/include/network/gameLog/incoming/0400.h>
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
using namespace shaiya;

namespace packet_gem
{
    /// <summary>
    /// Adds support for safety charms.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    /// <returns></returns>
    bool remove_charm(CUser* user, GameLapisianAddIncoming_EP6_4* incoming)
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
    bool enable_step(CItem* lapisian, CItem* item)
    {
        constexpr int max_enchant_step = 20;
        constexpr int armor_difference = 50;

        auto enchantStep = CItem::GetEnchantStep(item);
        auto isWeapon = CItem::IsWeapon(item);

        if (!isWeapon && enchantStep > armor_difference)
            enchantStep -= armor_difference;

        if (enchantStep >= max_enchant_step)
            return false;

        auto successRate = lapisian->info->reqRec;
        if (successRate != 10000)
            return false;

        auto lapisianLv = lapisian->info->attackTime;
        if (!lapisianLv || lapisianLv > max_enchant_step)
            return false;

        // Hot Time Lapisia +1
        if (enchantStep < 10 && lapisian->info->itemId == 95005)
            return true;

        auto lapisianStep = lapisian->info->range;
        auto lapisianType = std::to_underlying(lapisian->info->country);

        if (isWeapon)
        {
            // Weapon Lapisia +1
            if (enchantStep < 10 && lapisian->info->itemId == 95004)
                return true;
            else if (enchantStep == lapisianStep && lapisianType == 0)
                return true;
        }
        else
        {
            // Armor Lapisia +1
            if (enchantStep < 10 && lapisian->info->itemId == 95009)
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
    void handler_0x80B(CUser* user, GameItemRemake5Incoming_EP6_4* incoming)
    {
        if (!incoming->lapisBag1 || incoming->lapisBag1 > user->bagsUnlocked || incoming->lapisSlot1 >= max_inventory_slot)
            return;

        auto& lapis1 = user->inventory[incoming->lapisBag1][incoming->lapisSlot1];
        if (!lapis1)
            return;

        if (lapis1->type != std::to_underlying(ItemType::Lapis))
            return;

        if (lapis1->info->reqIg == 30 || lapis1->info->reqIg == 99)
            return;

        if (!incoming->lapisBag2 || incoming->lapisBag2 > user->bagsUnlocked || incoming->lapisSlot2 >= max_inventory_slot)
            return;

        auto& lapis2 = user->inventory[incoming->lapisBag2][incoming->lapisSlot2];
        if (!lapis2)
            return;

        if (lapis2->type != std::to_underlying(ItemType::Lapis))
            return;

        if (lapis2->info->reqIg == 30 || lapis2->info->reqIg == 99)
            return;

        if (!incoming->lapisBag3 || incoming->lapisBag3 > user->bagsUnlocked || incoming->lapisSlot3 >= max_inventory_slot)
            return;

        auto& lapis3 = user->inventory[incoming->lapisBag3][incoming->lapisSlot3];
        if (!lapis3)
            return;

        if (lapis3->type != std::to_underlying(ItemType::Lapis))
            return;

        if (lapis3->info->reqIg == 30 || lapis3->info->reqIg == 99)
            return;

        auto slot1 = incoming->lapisSlot1;
        auto slot2 = incoming->lapisSlot2;
        auto slot3 = incoming->lapisSlot3;
        if (slot1 == slot2 || slot2 == slot3 || slot3 == slot1)
            return;

        if (!incoming->essenceBag || incoming->essenceBag > user->bagsUnlocked || incoming->essenceSlot >= max_inventory_slot)
            return;

        auto& essence = user->inventory[incoming->essenceBag][incoming->essenceSlot];
        if (!essence)
            return;

        int requiredCount = 0;
        if (lapis1->info->reqIg >= 36)
            ++requiredCount;

        if (lapis2->info->reqIg >= 36)
            ++requiredCount;

        if (lapis3->info->reqIg >= 36)
            ++requiredCount;

        GameItemRemake5Outgoing failure{};
        failure.result = GameItemRemake5Result::Failure;

        if (essence->count < requiredCount || essence->info->effect != ItemEffect::CrowleyEssence)
        {
            NetworkHelper::Send(user, &failure, sizeof(GameItemRemake5Outgoing));
            return;
        }

        auto itemId1 = lapis1->info->itemId;
        auto itemId2 = lapis2->info->itemId;
        auto itemId3 = lapis3->info->itemId;

        auto remake = std::find_if(g_itemRemake5.begin(), g_itemRemake5.end(), [&itemId1, &itemId2, &itemId3](const auto& remake) {
            return remake.itemId1 == itemId1 && remake.itemId2 == itemId2 && remake.itemId3 == itemId3;
            });

        if (remake == g_itemRemake5.end())
        {
            NetworkHelper::Send(user, &failure, sizeof(GameItemRemake5Outgoing));
            return;
        }

        auto itemInfo = CGameData::GetItemInfo(remake->createType, remake->createTypeId);
        if (!itemInfo)
        {
            NetworkHelper::Send(user, &failure, sizeof(GameItemRemake5Outgoing));
            return;
        }

        int bag{}, slot{};
        if (!UserHelper::ItemCreate(user, itemInfo, 1, bag, slot))
        {
            NetworkHelper::Send(user, &failure, sizeof(GameItemRemake5Outgoing));
            return;
        }

        UserHelper::ItemRemove(user, incoming->lapisBag1, incoming->lapisSlot1, 1);
        UserHelper::ItemRemove(user, incoming->lapisBag2, incoming->lapisSlot2, 1);
        UserHelper::ItemRemove(user, incoming->lapisBag3, incoming->lapisSlot3, 1);
        UserHelper::ItemRemove(user, incoming->essenceBag, incoming->essenceSlot, requiredCount);

        GameItemRemake5Outgoing success{};
        success.result = GameItemRemake5Result::Success;
        success.newItem.bag = bag;
        success.newItem.slot = slot;
        success.newItem.type = itemInfo->type;
        success.newItem.typeId = itemInfo->typeId;
        success.newItem.count = 1;
        NetworkHelper::Send(user, &success, sizeof(GameItemRemake5Outgoing));
    }

    /// <summary>
    /// Handles incoming 0x80C packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void handler_0x80C(CUser* user, GameItemRemake4Incoming_EP6_4* incoming)
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

        auto slot1 = incoming->lapisianSlot1;
        auto slot2 = incoming->lapisianSlot2;
        auto slot3 = incoming->lapisianSlot3;
        if (slot1 == slot2 || slot2 == slot3 || slot3 == slot1)
            return;

        if (!incoming->liquidBag || incoming->liquidBag > user->bagsUnlocked || incoming->liquidSlot >= max_inventory_slot)
            return;

        auto& liquid = user->inventory[incoming->liquidBag][incoming->liquidSlot];
        if (!liquid)
            return;

        GameItemRemake4Outgoing failure{};
        failure.result = GameItemRemake4Result::Failure;

        if (liquid->info->effect != ItemEffect::CrowleyLiquid)
        {
            NetworkHelper::Send(user, &failure, sizeof(GameItemRemake4Outgoing));
            return;
        }

        auto itemId1 = lapisian1->info->itemId;
        auto itemId2 = lapisian2->info->itemId;
        auto itemId3 = lapisian3->info->itemId;

        auto remake = std::find_if(g_itemRemake4.begin(), g_itemRemake4.end(), [&itemId1, &itemId2, &itemId3](const auto& remake) {
            return remake.itemId1 == itemId1 && remake.itemId2 == itemId2 && remake.itemId3 == itemId3;
            });

        if (remake == g_itemRemake4.end())
        {
            NetworkHelper::Send(user, &failure, sizeof(GameItemRemake4Outgoing));
            return;
        }

        auto itemInfo = CGameData::GetItemInfo(remake->createType, remake->createTypeId);
        if (!itemInfo)
        {
            NetworkHelper::Send(user, &failure, sizeof(GameItemRemake4Outgoing));
            return;
        }

        int bag{}, slot{};
        if (!UserHelper::ItemCreate(user, itemInfo, 1, bag, slot))
        {
            NetworkHelper::Send(user, &failure, sizeof(GameItemRemake4Outgoing));
            return;
        }

        UserHelper::ItemRemove(user, incoming->lapisianBag1, incoming->lapisianSlot1, 1);
        UserHelper::ItemRemove(user, incoming->lapisianBag2, incoming->lapisianSlot2, 1);
        UserHelper::ItemRemove(user, incoming->lapisianBag3, incoming->lapisianSlot3, 1);
        UserHelper::ItemRemove(user, incoming->liquidBag, incoming->liquidSlot, 1);

        GameItemRemake4Outgoing success{};
        success.result = GameItemRemake4Result::Success;
        success.newItem.bag = bag;
        success.newItem.slot = slot;
        success.newItem.type = itemInfo->type;
        success.newItem.typeId = itemInfo->typeId;
        success.newItem.count = 1;
        NetworkHelper::Send(user, &success, sizeof(GameItemRemake4Outgoing));
    }

    /// <summary>
    /// Handles incoming 0x80D packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void handler_0x80D(CUser* user, GameRecreationRuneUpgradeIncoming_EP6_4* incoming)
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

        GameRecreationRuneUpgradeOutgoing failure{};
        failure.result = GameRecreationRuneUpgradeResult::Failure;

        if (rune->count < 2 || rune->info->effect != ItemEffect::RecreationRune)
        {
            NetworkHelper::Send(user, &failure, sizeof(GameRecreationRuneUpgradeOutgoing));
            return;
        }

        ItemInfo* itemInfo = nullptr;

        switch (vial->info->effect)
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
            NetworkHelper::Send(user, &failure, sizeof(GameRecreationRuneUpgradeOutgoing));
            return;
        }
        
        int bag{}, slot{};
        if (!UserHelper::ItemCreate(user, itemInfo, 1, bag, slot))
        {
            NetworkHelper::Send(user, &failure, sizeof(GameRecreationRuneUpgradeOutgoing));
            return;
        }

        UserHelper::ItemRemove(user, incoming->runeBag, incoming->runeSlot, 2);
        UserHelper::ItemRemove(user, incoming->vialBag, incoming->vialSlot, 1);

        GameRecreationRuneUpgradeOutgoing success{};
        success.result = GameRecreationRuneUpgradeResult::Success;
        success.newItem.bag = bag;
        success.newItem.slot = slot;
        success.newItem.type = itemInfo->type;
        success.newItem.typeId = itemInfo->typeId;
        success.newItem.count = 1;
        NetworkHelper::Send(user, &success, sizeof(GameRecreationRuneUpgradeOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x80E packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void handler_0x80E(CUser* user, GameLapisianUpgradeIncoming* incoming)
    {
        if (!incoming->cubeBag || incoming->cubeBag > user->bagsUnlocked || incoming->cubeSlot >= max_inventory_slot)
            return;

        auto& cube = user->inventory[incoming->cubeBag][incoming->cubeSlot];
        if (!cube)
            return;

        // The data does not specify an item effect
        if (cube->info->itemId != 101101)
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

        GameLapisianUpgradeOutgoing failure{};
        failure.result = GameLapisianUpgradeResult::Unknown1;

        auto createType = incoming->lapisianType;
        auto createTypeId = incoming->lapisianTypeId + 1;

        auto createInfo = CGameData::GetItemInfo(createType, createTypeId);
        if (!createInfo)
        {
            NetworkHelper::Send(user, &failure, sizeof(GameLapisianUpgradeOutgoing));
            return;
        }

        CUser::ItemUseNSend(user, incoming->cubeBag, incoming->cubeSlot, false);

        for (int i = 0; i < requiredCount; ++i)
        {
            if (!UserHelper::ItemRemove(user, itemInfo->itemId, 1))
            {
                NetworkHelper::Send(user, &failure, sizeof(GameLapisianUpgradeOutgoing));
                return;
            }
        }

        int bag{}, slot{};
        if (!UserHelper::ItemCreate(user, createInfo, 1, bag, slot))
        {
            NetworkHelper::Send(user, &failure, sizeof(GameLapisianUpgradeOutgoing));
            return;
        }

        GameLapisianUpgradeOutgoing success{};
        success.result = GameLapisianUpgradeResult::Success;
        success.newItem.bag = bag;
        success.newItem.slot = slot;
        success.newItem.type = createInfo->type;
        success.newItem.typeId = createInfo->typeId;
        success.newItem.count = 1;
        NetworkHelper::Send(user, &success, sizeof(GameLapisianUpgradeOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x806 packets. Supports vanilla recreation runes. Adding custom 
    /// item effects (e.g., perfect) will require a client modification.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void handler_0x806(CUser* user, GameItemComposeIncoming_EP6_4* incoming)
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

        GameItemComposeOutgoing failure{};
        failure.result = GameItemComposeResult::Failure;

        if (!item->info->craftExpansions)
        {
            NetworkHelper::Send(user, &failure, sizeof(GameItemComposeOutgoing));
            return;
        }

        if (!item->info->reqWis || item->info->reqWis > 99)
        {
            NetworkHelper::Send(user, &failure, sizeof(GameItemComposeOutgoing));
            return;
        }

        // optional
        //if (item->makeType == MakeType::QuestResult)
        //{
        //    NetworkHelper::Send(user, &failure, sizeof(GameItemComposeOutgoing));
        //    return;
        //}

        auto composeUniqueId = rune->uniqueId;
        auto composeItemId = rune->info->itemId;
        auto oldCraftName = item->craftName;
        auto maxCraftValue = item->info->reqWis;

        // See the item descriptions

        switch (rune->info->effect)
        {
        case ItemEffect::StrRecreationRune:
        case ItemEffect::DexRecreationRune:
        case ItemEffect::IntRecreationRune:
        case ItemEffect::WisRecreationRune:
        case ItemEffect::RecRecreationRune:
        case ItemEffect::LucRecreationRune:
        {
            maxCraftValue *= 2;
            maxCraftValue = (maxCraftValue > 99) ? 99 : maxCraftValue;
            break;
        }
        default:
            break;
        }

        std::random_device seed;
        std::mt19937 eng(seed());

        std::uniform_int_distribution<uint16_t> uni(1, maxCraftValue);
        auto craftValue = uni(eng);

        auto maxHealth = user->maxHealth;
        auto maxMana = user->maxHealth;
        auto maxStamina = user->maxHealth;

        switch (rune->info->effect)
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
                ItemHelper::SetCraftStrength(item, craftValue);
                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            ItemHelper::SetCraftStrength(item, craftValue);

            break;
        case ItemEffect::DexRecreationRune:
            if (!item->craftDexterity)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);
                ItemHelper::SetCraftDexterity(item, craftValue);
                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            ItemHelper::SetCraftDexterity(item, craftValue);

            break;
        case ItemEffect::IntRecreationRune:
            if (!item->craftIntelligence)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);
                ItemHelper::SetCraftIntelligence(item, craftValue);
                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            ItemHelper::SetCraftIntelligence(item, craftValue);

            break;
        case ItemEffect::WisRecreationRune:
            if (!item->craftWisdom)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);
                ItemHelper::SetCraftWisdom(item, craftValue);
                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            ItemHelper::SetCraftWisdom(item, craftValue);

            break;
        case ItemEffect::RecRecreationRune:
            if (!item->craftReaction)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);
                ItemHelper::SetCraftReaction(item, craftValue);
                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            ItemHelper::SetCraftReaction(item, craftValue);

            break;
        case ItemEffect::LucRecreationRune:
            if (!item->craftLuck)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);
                ItemHelper::SetCraftLuck(item, craftValue);
                CUser::ItemEquipmentOptionAdd(user, item);
                break;
            }

            ItemHelper::SetCraftLuck(item, craftValue);

            break;
        default:
            NetworkHelper::Send(user, &failure, sizeof(GameItemComposeOutgoing));
            return;
        }

        if (!incoming->itemBag)
        {
            if (!user->initStatusFlag)
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
        ItemHelper::SendDBAgentCraftName(user, item, incoming->itemBag, incoming->itemSlot);

        GameLogItemComposeIncoming gameLog{};
        CUser::SetGameLogMain(user, &gameLog.packet);
        gameLog.packet.uniqueId = item->uniqueId;
        gameLog.packet.itemId = item->info->itemId;
        gameLog.packet.itemName = item->info->itemName;
        gameLog.packet.gems = item->gems;
        gameLog.packet.makeTime = item->makeTime;
        gameLog.packet.craftName = item->craftName;
        gameLog.packet.composeUniqueId = composeUniqueId;
        gameLog.packet.composeItemId = composeItemId;
        gameLog.packet.oldCraftName = oldCraftName;
        NetworkHelper::SendGameLog(&gameLog.packet, sizeof(GameLogItemComposeIncoming));

        GameItemComposeOutgoing success{};
        success.result = GameItemComposeResult::Success;
        success.bag = incoming->itemBag;
        success.slot = incoming->itemSlot;
        success.craftName = item->craftName;
        NetworkHelper::Send(user, &success, sizeof(GameItemComposeOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x830 packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void handler_0x830(CUser* user, GameItemSynthesisListIncoming* incoming)
    {
        if (!incoming->squareBag || incoming->squareBag > user->bagsUnlocked || incoming->squareSlot >= max_inventory_slot)
            return;

        auto& square = user->inventory[incoming->squareBag][incoming->squareSlot];
        if (!square)
            return;

        if (square->info->effect != ItemEffect::ChaoticSquare)
            return;

        auto synthesis = g_synthesis.find(square->info->itemId);
        if (synthesis == g_synthesis.end())
            return;

        user->savePosUseBag = incoming->squareBag;
        user->savePosUseSlot = incoming->squareSlot;

        CUser::CancelActionExc(user);
        MyShop::Ended(&user->myShop);

        GameItemSynthesisListOutgoing outgoing{};
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
                NetworkHelper::Send(user, &outgoing, sizeof(GameItemSynthesisListOutgoing));

                std::fill(itemList.begin(), itemList.end(), std::tuple(0, 0));
                index = 0;
            }
        }

        if (!index)
            return;

        NetworkHelper::Send(user, &outgoing, sizeof(GameItemSynthesisListOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x831 packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void handler_0x831(CUser* user, GameItemSynthesisMaterialIncoming* incoming)
    {
        auto& square = user->inventory[user->savePosUseBag][user->savePosUseSlot];
        if (!square)
            return;

        if (square->info->effect != ItemEffect::ChaoticSquare)
            return;

        auto it = g_synthesis.find(square->info->itemId);
        if (it == g_synthesis.end())
            return;

        if (incoming->index >= it->second.size())
            return;

        auto& synthesis = it->second[incoming->index];
        if (incoming->createType != synthesis.createType || incoming->createTypeId != synthesis.createTypeId)
            return;

        GameItemSynthesisMaterialOutgoing outgoing{};
        outgoing.successRate = synthesis.successRate;
        outgoing.materialType = synthesis.materialType;
        outgoing.createType = synthesis.createType;
        outgoing.materialTypeId = synthesis.materialTypeId;
        outgoing.createTypeId = synthesis.createTypeId;
        outgoing.materialCount = synthesis.materialCount;
        outgoing.createCount = synthesis.createCount;
        NetworkHelper::Send(user, &outgoing, sizeof(GameItemSynthesisMaterialOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x832 packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void handler_0x832(CUser* user, GameItemSynthesisIncoming* incoming)
    {
        constexpr auto min_success_rate = 100;
        constexpr auto max_success_rate = 10000;

        if (!incoming->squareBag || incoming->squareBag > user->bagsUnlocked || incoming->squareSlot >= max_inventory_slot)
            return;

        auto& square = user->inventory[incoming->squareBag][incoming->squareSlot];
        if (!square)
            return;

        if (square->info->effect != ItemEffect::ChaoticSquare)
            return;

        auto it = g_synthesis.find(square->info->itemId);
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
        if (money > Synthesis::goldPerPercentage5x)
            money = Synthesis::goldPerPercentage5x;

        auto successRate = synthesis.successRate;
        if (money >= Synthesis::goldPerPercentage && Synthesis::goldPerPercentage > 0)
            successRate += (money / Synthesis::goldPerPercentage) * 100;

        if (incoming->hammerBag != 0)
        {
            if (incoming->hammerBag > user->bagsUnlocked || incoming->hammerSlot >= max_inventory_slot)
                return;

            auto& hammer = user->inventory[incoming->hammerBag][incoming->hammerSlot];
            if (!hammer)
                return;

            if (hammer->info->effect != ItemEffect::CraftingHammer)
                return;

            successRate += hammer->info->reqVg * 100;
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

        GameItemSynthesisOutgoing outgoing{};
        outgoing.result = GameItemSynthesisResult::Failure;

        for (const auto& [type, typeId, count] : materials)
        {
            auto itemInfo = CGameData::GetItemInfo(type, typeId);
            if (!itemInfo)
                continue;

            if (!UserHelper::ItemRemove(user, itemInfo->itemId, count))
            {
                NetworkHelper::Send(user, &outgoing, sizeof(GameItemSynthesisOutgoing));
                return;
            }
        }

        if (randomRate <= successRate)
        {
            if (CUser::ItemCreate(user, createInfo, synthesis.createCount))
                outgoing.result = GameItemSynthesisResult::Success;
        }

        NetworkHelper::Send(user, &outgoing, sizeof(GameItemSynthesisOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x833 packets. This feature will not be implemented.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void handler_0x833(CUser* user, GameItemFreeSynthesisIncoming* incoming)
    {
    }

    /// <summary>
    /// Handles incoming 0x811 packets. ES client 171 supports this feature.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="incoming"></param>
    void handler_0x811(CUser* user, GameItemAbilityTransferIncoming* incoming)
    {
        constexpr auto min_success_rate = 30;
        constexpr auto max_success_rate = 100;

        if (!incoming->cubeBag || incoming->cubeBag > user->bagsUnlocked || incoming->cubeSlot >= max_inventory_slot)
            return;

        auto& cube = user->inventory[incoming->cubeBag][incoming->cubeSlot];
        if (!cube)
            return;

        if (cube->info->effect != ItemEffect::ItemAbilityTransfer)
            return;

        if (incoming->srcBag > user->bagsUnlocked || incoming->srcSlot >= max_inventory_slot)
            return;

        auto& srcItem = user->inventory[incoming->srcBag][incoming->srcSlot];
        if (!srcItem)
            return;

        if (incoming->destBag > user->bagsUnlocked || incoming->destSlot >= max_inventory_slot)
            return;

        auto& destItem = user->inventory[incoming->destBag][incoming->destSlot];
        if (!destItem)
            return;

        if (destItem->info->realType != srcItem->info->realType)
            return;

        if (destItem->info->level < srcItem->info->level)
            return;

        if (destItem->info->slots < srcItem->info->slots)
            return;

        if (destItem->info->craftExpansions < srcItem->info->craftExpansions)
            return;

        if (destItem->info->reqWis < srcItem->info->reqWis)
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

            if (catalyst->info->effect != ItemEffect::Catalyst)
                return;

            successRate += catalyst->info->reqVg;
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

        auto oldCraftName1 = destItem->craftName;
        auto oldCraftName2 = srcItem->craftName;

        GameItemAbilityTransferOutgoing outgoing{};
        outgoing.result = GameItemAbilityTransferResult::Failure;
        outgoing.srcBag = incoming->srcBag;
        outgoing.srcSlot = incoming->srcSlot;
        outgoing.destBag = incoming->destBag;
        outgoing.destSlot = incoming->destSlot;

        if (randomRate <= successRate)
        {
            outgoing.result = GameItemAbilityTransferResult::Success;

            auto maxHealth = user->maxHealth;
            auto maxMana = user->maxHealth;
            auto maxStamina = user->maxHealth;

            if (!incoming->destBag)
            {
                CUser::ItemEquipmentOptionRem(user, destItem);
                destItem->gems = srcItem->gems;
                ItemHelper::CopyCraftExpansion(srcItem, destItem);
                CUser::ItemEquipmentOptionAdd(user, destItem);
            }
            else
            {
                destItem->gems = srcItem->gems;
                ItemHelper::CopyCraftExpansion(srcItem, destItem);
            }
            
            if (!incoming->srcBag)
            {
                CUser::ItemEquipmentOptionRem(user, srcItem);
                srcItem->gems.fill(0);
                ItemHelper::InitCraftExpansion(srcItem);
                CUser::ItemEquipmentOptionAdd(user, srcItem);
            }
            else
            {
                srcItem->gems.fill(0);
                ItemHelper::InitCraftExpansion(srcItem);
            }

            if (!incoming->destBag || !incoming->srcBag)
            {
                if (!user->initStatusFlag)
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

            ItemHelper::SendDBAgentCraftName(user, destItem, incoming->destBag, incoming->destSlot);
            ItemHelper::SendDBAgentGems(user, destItem, incoming->destBag, incoming->destSlot);

            ItemHelper::SendDBAgentCraftName(user, srcItem, incoming->srcBag, incoming->srcSlot);
            ItemHelper::SendDBAgentGems(user, srcItem, incoming->srcBag, incoming->srcSlot);
        }

        NetworkHelper::Send(user, &outgoing, sizeof(GameItemAbilityTransferOutgoing));
    }

    /// <summary>
    /// Adds support for 6.4 packets.
    /// </summary>
    /// <param name="user"></param>
    /// <param name="packet"></param>
    void handler(CUser* user, uint8_t* packet)
    {
        auto opcode = util::deserialize<uint16_t>(packet, 0);

        switch (opcode)
        {
        case 0x80B:
        {
            auto incoming = reinterpret_cast<GameItemRemake5Incoming_EP6_4*>(packet);
            handler_0x80B(user, incoming);
            break;
        }
        case 0x80C:
        {
            auto incoming = reinterpret_cast<GameItemRemake4Incoming_EP6_4*>(packet);
            handler_0x80C(user, incoming);
            break;
        }
        case 0x80D:
        {
            auto incoming = reinterpret_cast<GameRecreationRuneUpgradeIncoming_EP6_4*>(packet);
            handler_0x80D(user, incoming);
            break;
        }
        case 0x80E:
        {
            auto incoming = reinterpret_cast<GameLapisianUpgradeIncoming*>(packet);
            handler_0x80E(user, incoming);
            break;
        }
        case 0x811:
        {
            auto incoming = reinterpret_cast<GameItemAbilityTransferIncoming*>(packet);
            handler_0x811(user, incoming);
            break;
        }
        case 0x830:
        {
            auto incoming = reinterpret_cast<GameItemSynthesisListIncoming*>(packet);
            handler_0x830(user, incoming);
            break;
        }
        case 0x831:
        {
            auto incoming = reinterpret_cast<GameItemSynthesisMaterialIncoming*>(packet);
            handler_0x831(user, incoming);
            break;
        }
        case 0x832:
        {
            auto incoming = reinterpret_cast<GameItemSynthesisIncoming*>(packet);
            handler_0x832(user, incoming);
            break;
        }
        case 0x833:
        {
            auto incoming = reinterpret_cast<GameItemFreeSynthesisIncoming*>(packet);
            handler_0x833(user, incoming);
            break;
        }
        default:
            SConnection::Close(user, 9, 0);
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
        call packet_gem::handler
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
        call packet_gem::handler_0x806
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
        call packet_gem::enable_step
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
        call packet_gem::remove_charm
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
        call packet_gem::remove_charm
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
