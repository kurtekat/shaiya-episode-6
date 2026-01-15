//#define SHAIYA_EP6_4_ENABLE_0806_HANDLER
#include <random>
#include <ranges>
#include <string>
#include <util/util.h>
#include <shaiya/include/common/ItemEffect.h>
#include <shaiya/include/common/ItemType.h>
#include <shaiya/include/network/TP_MAIN.h>
#include <shaiya/include/network/dbAgent/incoming/0700.h>
#include <shaiya/include/network/game/incoming/0800.h>
#include <shaiya/include/network/game/outgoing/0200.h>
#include <shaiya/include/network/game/outgoing/0800.h>
#include <shaiya/include/network/gameLog/incoming/0400.h>
#include "include/main.h"
#include "include/operator.h"
#include "include/shaiya/CGameData.h"
#include "include/shaiya/ChaoticSquare.h"
#include "include/shaiya/ChaoticSquarePredicate.h"
#include "include/shaiya/CItem.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/ItemFinder.h"
#include "include/shaiya/ItemHelper.h"
#include "include/shaiya/ItemInfo.h"
#include "include/shaiya/ItemPredicate.h"
#include "include/shaiya/Network.h"
#include "include/shaiya/SConnection.h"
#include "include/shaiya/UserHelper.h"
using namespace shaiya;

namespace packet_gem
{
    /// <summary>
    /// Adds support for item effect 103.
    /// </summary>
    bool lapisian_add_protect(CUser* user, GameLapisianAddIncoming_EP6_4* incoming)
    {
        if (!incoming->itemProtect)
            return false;

        int bag{}, slot{};
        if (!ItemFinder(user, bag, slot, ItemEffectEqualToF(ItemEffect::LapisianAddItemProtect)))
            return false;

        CUser::ItemUseNSend(user, bag, slot, false);
        return true;
    }

    /// <summary>
    /// Handles incoming 0x80B packets. Does not do anything else for now.
    /// </summary>
    void handler_0x80B(CUser* user, GameItemGemComposeIncoming_EP6_4* incoming)
    {
        if (!incoming->bag1)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->bag1, incoming->slot1))
            return;

        auto& item1 = user->inventory[incoming->bag1][incoming->slot1];
        if (!item1)
            return;

        if (!incoming->bag2)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->bag2, incoming->slot2))
            return;

        auto& item2 = user->inventory[incoming->bag2][incoming->slot2];
        if (!item2)
            return;

        if (!incoming->bag3)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->bag3, incoming->slot3))
            return;

        auto& item3 = user->inventory[incoming->bag3][incoming->slot3];
        if (!item3)
            return;

        if (!incoming->vialBag)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->vialBag, incoming->vialSlot))
            return;

        auto& vial = user->inventory[incoming->vialBag][incoming->vialSlot];
        if (!vial)
            return;

        if (item1->type != ItemType::Lapis)
            return;

        if (item2->type != ItemType::Lapis)
            return;

        if (item3->type != ItemType::Lapis)
            return;

        if (vial->info->effect != ItemEffect::CrowleyEssence)
            return;

        if (item1->info->reqIg <= 30 || item1->info->reqIg > 40)
            return;

        if (item2->info->reqIg <= 30 || item2->info->reqIg > 40)
            return;

        if (item3->info->reqIg <= 30 || item3->info->reqIg > 40)
            return;

        int requiredCount = 0;
        if (item1->info->reqIg >= 36)
            ++requiredCount;

        if (item2->info->reqIg >= 36)
            ++requiredCount;

        if (item3->info->reqIg >= 36)
            ++requiredCount;

        if (vial->count < requiredCount)
            return;

        // to-do
    }

    /// <summary>
    /// Handles incoming 0x80C packets. Does not do anything else for now.
    /// </summary>
    void handler_0x80C(CUser* user, GameItemLapisianComposeIncoming_EP6_4* incoming)
    {
        if (!incoming->bag1)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->bag1, incoming->slot1))
            return;

        auto& item1 = user->inventory[incoming->bag1][incoming->slot1];
        if (!item1)
            return;

        if (!incoming->bag2)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->bag2, incoming->slot2))
            return;

        auto& item2 = user->inventory[incoming->bag2][incoming->slot2];
        if (!item2)
            return;

        if (!incoming->bag3)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->bag3, incoming->slot3))
            return;

        auto& item3 = user->inventory[incoming->bag3][incoming->slot3];
        if (!item3)
            return;

        if (!incoming->vialBag)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->vialBag, incoming->vialSlot))
            return;

        auto& vial = user->inventory[incoming->vialBag][incoming->vialSlot];
        if (!vial)
            return;

        if (item1->type != ItemType::Lapisian)
            return;

        if (item2->type != ItemType::Lapisian)
            return;

        if (item3->type != ItemType::Lapisian)
            return;

        if (vial->info->effect != ItemEffect::CrowleyLiquid)
            return;

        // to-do
    }

    /// <summary>
    /// Handles incoming 0x80D packets.
    /// </summary>
    void handler_0x80D(CUser* user, GameUpperRuneComposeIncoming_EP6_4* incoming)
    {
        if (!incoming->runeBag)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->runeBag, incoming->runeSlot))
            return;

        auto& rune = user->inventory[incoming->runeBag][incoming->runeSlot];
        if (!rune)
            return;

        if (!incoming->vialBag)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->vialBag, incoming->vialSlot))
            return;

        auto& vial = user->inventory[incoming->vialBag][incoming->vialSlot];
        if (!vial)
            return;

        if (rune->count < 2)
            return;

        if (rune->info->effect != ItemEffect::RecreationRune)
        {
            GameUpperRuneComposeOutgoing failure{};
            failure.result = GameUpperRuneComposeResult::Failure;
            SConnection::Send(user, &failure, sizeof(GameUpperRuneComposeOutgoing));
            return;
        }

        ItemInfo* newItemInfo = nullptr;

        switch (vial->info->effect)
        {
        case ItemEffect::StrVial:
            newItemInfo = CGameData::GetItemInfo(101, 1);
            break;
        case ItemEffect::DexVial:
            newItemInfo = CGameData::GetItemInfo(101, 2);
            break;
        case ItemEffect::IntVial:
            newItemInfo = CGameData::GetItemInfo(101, 3);
            break;
        case ItemEffect::WisVial:
            newItemInfo = CGameData::GetItemInfo(101, 4);
            break;
        case ItemEffect::RecVial:
            newItemInfo = CGameData::GetItemInfo(101, 5);
            break;
        case ItemEffect::LucVial:
            newItemInfo = CGameData::GetItemInfo(101, 6);
            break;
        default:
            break;
        }

        if (newItemInfo)
        {
            UserHelper::ItemRemove(user, incoming->runeBag, incoming->runeSlot, 2);
            UserHelper::ItemRemove(user, incoming->vialBag, incoming->vialSlot, 1);

            int bag{}, slot{};
            if (UserHelper::ItemCreate(user, newItemInfo, 1, bag, slot))
            {
                GameUpperRuneComposeOutgoing success{};
                success.result = GameUpperRuneComposeResult::Success;
                success.newItem.bag = bag;
                success.newItem.slot = slot;
                success.newItem.type = newItemInfo->type;
                success.newItem.typeId = newItemInfo->typeId;
                success.newItem.count = 1;
                SConnection::Send(user, &success, sizeof(GameUpperRuneComposeOutgoing));
            }
        }
        else
        {
            GameUpperRuneComposeOutgoing failure{};
            failure.result = GameUpperRuneComposeResult::Failure;
            SConnection::Send(user, &failure, sizeof(GameUpperRuneComposeOutgoing));
        }
    }

    /// <summary>
    /// Handles incoming 0x80E packets.
    /// </summary>
    void handler_0x80E(CUser* user, GameItemLapisianRemakeIncoming* incoming)
    {
        if (!incoming->cubeBag)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->cubeBag, incoming->cubeSlot))
            return;

        auto& cube = user->inventory[incoming->cubeBag][incoming->cubeSlot];
        if (!cube)
            return;

        // Requires an item (not an item effect)
        if (cube->info->type != 101 && cube->info->typeId != 101)
            return;

        if (incoming->lapisianType != ItemType::Lapisian)
            return;

        auto oldItemInfo = CGameData::GetItemInfo(incoming->lapisianType, incoming->lapisianTypeId);
        if (!oldItemInfo)
            return;

        auto newItemInfo = CGameData::GetItemInfo(incoming->lapisianType, incoming->lapisianTypeId + 1);
        if (!newItemInfo)
            return;

        GameItemLapisianRemakeOutgoing failure{};
        failure.result = GameItemLapisianRemakeResult::Failure;

        // See system message 510

        auto lapisianLv = oldItemInfo->attackTime;
        if (lapisianLv < 6 || lapisianLv > 19)
        {
            SConnection::Send(user, &failure, sizeof(GameItemLapisianRemakeOutgoing));
            return;
        }

        auto requiredCount = oldItemInfo->reqLuc;
        if (!requiredCount)
        {
            SConnection::Send(user, &failure, sizeof(GameItemLapisianRemakeOutgoing));
            return;
        }

        CUser::ItemUseNSend(user, incoming->cubeBag, incoming->cubeSlot, false);

        for (int i = 0; i < requiredCount; ++i)
        {
            int bag{}, slot{};
            if (!ItemFinder(user, bag, slot, ItemEqualToF(oldItemInfo->type, oldItemInfo->typeId)))
                return;

            if (!UserHelper::ItemRemove(user, bag, slot, 1))
                return;
        }

        int bag{}, slot{};
        if (UserHelper::ItemCreate(user, newItemInfo, 1, bag, slot))
        {
            GameItemLapisianRemakeOutgoing success{};
            success.result = GameItemLapisianRemakeResult::Success;
            success.newItem.bag = bag;
            success.newItem.slot = slot;
            success.newItem.type = newItemInfo->type;
            success.newItem.typeId = newItemInfo->typeId;
            success.newItem.count = 1;
            SConnection::Send(user, &success, sizeof(GameItemLapisianRemakeOutgoing));
        }
    }

    /// <summary>
    /// Handles incoming 0x806 packets. Supports vanilla recreation runes. Adding custom 
    /// item effects (e.g., perfect) requires a client modification.
    /// </summary>
    void handler_0x806(CUser* user, GameItemComposeIncoming_EP6_4* incoming)
    {
        if (!incoming->runeBag)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->runeBag, incoming->runeSlot))
            return;

        auto& rune = user->inventory[incoming->runeBag][incoming->runeSlot];
        if (!rune)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->itemBag, incoming->itemSlot))
            return;

        auto& item = user->inventory[incoming->itemBag][incoming->itemSlot];
        if (!item)
            return;

        GameItemComposeOutgoing failure{};
        failure.result = GameItemComposeResult::Failure;

        if (!item->info->craftExpansions)
        {
            SConnection::Send(user, &failure, sizeof(GameItemComposeOutgoing));
            return;
        }

        if (!item->info->reqWis || item->info->reqWis > ItemCraft_MAX)
        {
            SConnection::Send(user, &failure, sizeof(GameItemComposeOutgoing));
            return;
        }

        //if (item->makeType == MakeType::QuestResult)
        //{
        //    SConnection::Send(user, &failure, sizeof(GameItemComposeOutgoing));
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
            if (maxCraftValue > ItemCraft_MAX)
                maxCraftValue = ItemCraft_MAX;

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
            SConnection::Send(user, &failure, sizeof(GameItemComposeOutgoing));
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
        Network::SendGameLog(&gameLog.packet, sizeof(GameLogItemComposeIncoming));

        GameItemComposeOutgoing success{};
        success.result = GameItemComposeResult::Success;
        success.bag = incoming->itemBag;
        success.slot = incoming->itemSlot;
        success.craftName = item->craftName;
        SConnection::Send(user, &success, sizeof(GameItemComposeOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x830 packets.
    /// </summary>
    void handler_0x830(CUser* user, GameChaoticSquareResultItemListIncoming* incoming)
    {
        if (!incoming->squareBag)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->squareBag, incoming->squareSlot))
            return;

        auto& item = user->inventory[incoming->squareBag][incoming->squareSlot];
        if (!item)
            return;

        if (item->info->effect != ItemEffect::ChaoticSquare)
            return;

        auto square = ChaoticSquare::Find(item->info->itemId);
        if (!square)
            return;

        user->savePosUseBag = incoming->squareBag;
        user->savePosUseSlot = incoming->squareSlot;

        CUser::CancelActionExc(user);
        MyShop::Ended(&user->myShop);

        for (const auto& resultList : square->resultLists)
        {
            GameChaoticSquareResultItemListOutgoing outgoing{};
            outgoing.resultItemType = resultList.itemType;
            outgoing.resultItemTypeId = resultList.itemTypeId;
            outgoing.fortuneMoney = g_chaoticSquareFortuneMoney;
            SConnection::Send(user, &outgoing, sizeof(GameChaoticSquareResultItemListOutgoing));
        }
    }

    /// <summary>
    /// Handles incoming 0x831 packets.
    /// </summary>
    void handler_0x831(CUser* user, GameChaoticSquareRecipeIncoming* incoming)
    {
        auto& item = user->inventory[user->savePosUseBag][user->savePosUseSlot];
        if (!item)
            return;

        if (item->info->effect != ItemEffect::ChaoticSquare)
            return;

        auto square = ChaoticSquare::Find(item->info->itemId);
        if (!square)
            return;

        if (incoming->index >= square->recipeList.size())
            return;

        auto id = square->recipeList[incoming->index];
        auto recipe = ChaoticSquare::FindRecipe(id);
        if (!recipe)
            return;

        if (incoming->resultItemType != recipe->resultItem.type || incoming->resultItemTypeId != recipe->resultItem.typeId)
            return;

        GameChaoticSquareRecipeOutgoing outgoing{};
        outgoing.chance = recipe->chance;
        outgoing.materialType = recipe->materialType;
        outgoing.resultItemType = recipe->resultItem.type;
        outgoing.materialTypeId = recipe->materialTypeId;
        outgoing.resultItemTypeId = recipe->resultItem.typeId;
        outgoing.materialCount = recipe->materialCount;
        outgoing.resultItemCount = recipe->resultItem.count;
        SConnection::Send(user, &outgoing, sizeof(GameChaoticSquareRecipeOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x832 packets.
    /// </summary>
    void handler_0x832(CUser* user, GameItemSynthesisIncoming* incoming)
    {
        if (!incoming->squareBag)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->squareBag, incoming->squareSlot))
            return;

        auto& item = user->inventory[incoming->squareBag][incoming->squareSlot];
        if (!item)
            return;

        if (item->info->effect != ItemEffect::ChaoticSquare)
            return;

        auto square = ChaoticSquare::Find(item->info->itemId);
        if (!square)
            return;

        if (incoming->index >= square->recipeList.size())
            return;

        auto id = square->recipeList[incoming->index];
        auto recipe = ChaoticSquare::FindRecipe(id);
        if (!recipe)
            return;

        if (incoming->money > user->money)
            return;

        auto fortuneMoney = g_chaoticSquareFortuneMoney;
        auto chance = recipe->chance;

        if (fortuneMoney >= 100)
        {
            auto minMoney = fortuneMoney / 100;
            auto maxMoney = fortuneMoney * 5;

            auto money = incoming->money;
            if (money > maxMoney)
                money = maxMoney;

            if (money >= minMoney)
            {
                auto bonus = ((double)money / fortuneMoney) * 100.0;
                chance += static_cast<int>(bonus);

                user->money -= money;
                CUser::SendDBMoney(user);
            }
        }

        if (incoming->hammerBag != 0)
        {
            if (!UserHelper::IsValidItemPosition(user, incoming->hammerBag, incoming->hammerSlot))
                return;

            auto& hammer = user->inventory[incoming->hammerBag][incoming->hammerSlot];
            if (!hammer)
                return;

            if (hammer->info->effect != ItemEffect::CraftingHammer)
                return;

            chance += hammer->info->reqVg * 100;
            CUser::ItemUseNSend(user, incoming->hammerBag, incoming->hammerSlot, false);
        }

        CUser::ItemUseNSend(user, incoming->squareBag, incoming->squareSlot, false);

        if (UserHelper::RecipeRemove(user, *recipe))
        {
            auto randomChance = 0;
            if (chance < 10000)
            {
                std::random_device seed;
                std::mt19937 eng(seed());

                std::uniform_int_distribution<int> uni(100, 10000);
                randomChance = uni(eng);
            }

            if (randomChance <= chance)
            {
                auto itemInfo = CGameData::GetItemInfo(recipe->resultItem.type, recipe->resultItem.typeId);
                if (!itemInfo)
                    return;

                CUser::ItemCreate(user, itemInfo, recipe->resultItem.count);

                GameItemSynthesisOutgoing success{};
                success.result = GameItemSynthesisResult::Success;
                SConnection::Send(user, &success, sizeof(GameItemSynthesisOutgoing));
            }
            else
            {
                for (const auto& failItem : square->failItems)
                {
                    auto itemInfo = CGameData::GetItemInfo(failItem.type, failItem.typeId);
                    if (!itemInfo)
                        continue;

                    CUser::ItemCreate(user, itemInfo, failItem.count);
                }

                GameItemSynthesisOutgoing failure{};
                failure.result = GameItemSynthesisResult::Failure;
                SConnection::Send(user, &failure, sizeof(GameItemSynthesisOutgoing));
            }
        }
    }

    /// <summary>
    /// Handles incoming 0x833 packets. This feature will not be implemented.
    /// </summary>
    void handler_0x833(CUser* user, GameItemFreeSynthesisIncoming* incoming)
    {
    }

    /// <summary>
    /// Handles incoming 0x811 packets. See the docs for a list of supported clients.
    /// </summary>
    void handler_0x811(CUser* user, GameItemAbilityMoveIncoming* incoming)
    {
        constexpr auto baseChance = 30;
        auto chance = baseChance;

        if (!incoming->cubeBag)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->cubeBag, incoming->cubeSlot))
            return;

        auto& cube = user->inventory[incoming->cubeBag][incoming->cubeSlot];
        if (!cube)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->srcBag, incoming->srcSlot))
            return;

        auto& source = user->inventory[incoming->srcBag][incoming->srcSlot];
        if (!source)
            return;

        if (!UserHelper::IsValidItemPosition(user, incoming->destBag, incoming->destSlot))
            return;

        auto& target = user->inventory[incoming->destBag][incoming->destSlot];
        if (!target)
            return;

        if (cube->info->effect != ItemEffect::ItemAbilityMove)
            return;

        if (target->info->realType != source->info->realType)
            return;

        if (target->info->level < source->info->level)
            return;

        if (target->info->slots < source->info->slots)
            return;

        if (target->info->craftExpansions < source->info->craftExpansions)
            return;

        if (target->info->reqWis < source->info->reqWis)
            return;

        // 255 means the slot is empty
        if (incoming->catalystSlot != 255)
        {
            if (!incoming->catalystBag)
                return;

            if (!UserHelper::IsValidItemPosition(user, incoming->catalystBag, incoming->catalystSlot))
                return;

            auto& catalyst = user->inventory[incoming->catalystBag][incoming->catalystSlot];
            if (!catalyst)
                return;

            if (catalyst->info->effect != ItemEffect::Catalyst)
                return;

            chance += catalyst->info->reqVg;
            CUser::ItemUseNSend(user, incoming->catalystBag, incoming->catalystSlot, false);
        }

        CUser::ItemUseNSend(user, incoming->cubeBag, incoming->cubeSlot, false);

        GameItemAbilityMoveOutgoing outgoing{};
        outgoing.result = GameItemAbilityMoveResult::Failure;
        outgoing.srcBag = incoming->srcBag;
        outgoing.srcSlot = incoming->srcSlot;
        outgoing.destBag = incoming->destBag;
        outgoing.destSlot = incoming->destSlot;

        auto randomChance = 0;
        if (chance < 100)
        {
            std::random_device seed;
            std::mt19937 eng(seed());

            std::uniform_int_distribution<int> uni(1, 100);
            randomChance = uni(eng);
        }

        if (randomChance <= chance)
        {
            outgoing.result = GameItemAbilityMoveResult::Success;

            auto maxHealth = user->maxHealth;
            auto maxMana = user->maxHealth;
            auto maxStamina = user->maxHealth;

            if (!incoming->destBag)
            {
                for (const auto& gem : target->gems)
                {
                    if (!gem)
                        continue;

                    CUser::GemEquipmentRem(user, incoming->destSlot, gem);
                }

                target->gems = source->gems;

                CUser::ItemEquipmentOptionRem(user, target);
                ItemHelper::CopyCraftExpansion(source, target);
                CUser::ItemEquipmentOptionAdd(user, target);
            }
            else
            {
                target->gems = source->gems;
                ItemHelper::CopyCraftExpansion(source, target);
            }
            
            if (!incoming->srcBag)
            {
                for (const auto& gem : source->gems)
                {
                    if (!gem)
                        continue;

                    CUser::GemEquipmentRem(user, incoming->srcSlot, gem);
                }

                source->gems.fill(0);

                CUser::ItemEquipmentOptionRem(user, source);
                ItemHelper::InitCraftExpansion(source);
                CUser::ItemEquipmentOptionAdd(user, source);
            }
            else
            {
                source->gems.fill(0);
                ItemHelper::InitCraftExpansion(source);
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

            ItemHelper::SendDBAgentCraftName(user, target, incoming->destBag, incoming->destSlot);
            ItemHelper::SendDBAgentGems(user, target, incoming->destBag, incoming->destSlot);

            ItemHelper::SendDBAgentCraftName(user, source, incoming->srcBag, incoming->srcSlot);
            ItemHelper::SendDBAgentGems(user, source, incoming->srcBag, incoming->srcSlot);
        }

        SConnection::Send(user, &outgoing, sizeof(GameItemAbilityMoveOutgoing));
    }

    /// <summary>
    /// Adds support for 6.4 packets.
    /// </summary>
    void handler(CUser* user, TP_MAIN* packet)
    {
        switch (packet->opcode)
        {
        case 0x80B:
        {
            handler_0x80B(user, reinterpret_cast<GameItemGemComposeIncoming_EP6_4*>(packet));
            break;
        }
        case 0x80C:
        {
            handler_0x80C(user, reinterpret_cast<GameItemLapisianComposeIncoming_EP6_4*>(packet));
            break;
        }
        case 0x80D:
        {
            handler_0x80D(user, reinterpret_cast<GameUpperRuneComposeIncoming_EP6_4*>(packet));
            break;
        }
        case 0x80E:
        {
            handler_0x80E(user, reinterpret_cast<GameItemLapisianRemakeIncoming*>(packet));
            break;
        }
        case 0x811:
        {
            handler_0x811(user, reinterpret_cast<GameItemAbilityMoveIncoming*>(packet));
            break;
        }
        case 0x830:
        {
            handler_0x830(user, reinterpret_cast<GameChaoticSquareResultItemListIncoming*>(packet));
            break;
        }
        case 0x831:
        {
            handler_0x831(user, reinterpret_cast<GameChaoticSquareRecipeIncoming*>(packet));
            break;
        }
        case 0x832:
        {
            handler_0x832(user, reinterpret_cast<GameItemSynthesisIncoming*>(packet));
            break;
        }
        case 0x833:
        {
            handler_0x833(user, reinterpret_cast<GameItemFreeSynthesisIncoming*>(packet));
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

unsigned u0x46D5BE = 0x46D5BE;
unsigned u0x46CCCF = 0x46CCCF;
void __declspec(naked) naked_0x46CCC8()
{
    // esi = CItem* (lapisian)
    __asm
    {
        // enchant step
        movzx eax,byte ptr[esp+0x13]
        mov ecx,[esi+0x30]
        // minimum step
        movzx edx,word ptr[ecx+0x42]
        test edx,edx
        je maximum_step

        cmp eax,edx
        jl _0x46D5BE

        maximum_step:
        movzx edx,byte ptr[ecx+0x44]
        test edx,edx
        je original

        cmp eax,edx
        jnl _0x46D5BE

        original:
        mov ecx,[esi+0x30]
        movzx eax,byte ptr[ecx+0x32]
        jmp u0x46CCCF

        _0x46D5BE:
        jmp u0x46D5BE
    }
}

unsigned u0x46CD3F = 0x46CD3F;
void __declspec(naked) naked_0x46CD38()
{
    __asm
    {
        mov edi,[esp+0x14]
        mov edi,[edi+0x30]
        // success rate
        movzx edi,word ptr[edi+0x3A]
        test edi,edi
        je _original

        imul edi,edi,0x64
        jmp u0x46CD3F

        _original:
        // g_LapisianEnchantSuccessRate
        mov edi,[edx*0x4+0x581C88]
        jmp u0x46CD3F
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
        call packet_gem::lapisian_add_protect
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
        call packet_gem::lapisian_add_protect
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
    // CUser::ItemLapisianAdd (perfect lapisian)
    util::detour((void*)0x46CCC8, naked_0x46CCC8, 7);
    // CUser::ItemLapisianAdd (perfect lapisian)
    util::detour((void*)0x46CD38, naked_0x46CD38, 7);
    // CUser::ItemLapisianAdd (success)
    util::detour((void*)0x46CDB0, naked_0x46CDB0, 5);
    // CUser::ItemLapisianAdd (failure)
    util::detour((void*)0x46D3BC, naked_0x46D3BC, 8);

#ifdef SHAIYA_EP6_4_ENABLE_0806_HANDLER
    // CUser::PacketGem case 0x806
    util::detour((void*)0x47A003, naked_0x47A003, 9);
#endif
}
