//#define SHAIYA_EP6_4_ENABLE_0806_HANDLER
#include <random>
#include <ranges>
#include <string>
#include <util/util.h>
#include <shaiya/include/common/ItemEffect.h>
#include <shaiya/include/common/ItemSlot.h>
#include <shaiya/include/common/ItemType.h>
#include <shaiya/include/network/TP_MAIN.h>
#include <shaiya/include/network/dbAgent/incoming/0700.h>
#include <shaiya/include/network/game/incoming/0800.h>
#include <shaiya/include/network/game/outgoing/0200.h>
#include <shaiya/include/network/game/outgoing/0800.h>
#include <shaiya/include/network/gameLog/incoming/0400.h>
#include "include/main.h"
#include "include/shaiya/CGameData.h"
#include "include/shaiya/CItem.h"
#include "include/shaiya/CUser.h"
#include "include/shaiya/ItemFinder.h"
#include "include/shaiya/ItemHelper.h"
#include "include/shaiya/ItemInfo.h"
#include "include/shaiya/ItemPredicate.h"
#include "include/shaiya/ItemRemake.h"
#include "include/shaiya/ItemSynthesis.h"
#include "include/shaiya/NetworkHelper.h"
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
        if (!ItemFinder(user, bag, slot, ItemEffectEqualF(ItemEffect::LapisianAddItemProtect)))
            return false;

        CUser::ItemUseNSend(user, bag, slot, false);
        return true;
    }

    /// <summary>
    /// Handles incoming 0x80B packets.
    /// </summary>
    void handler_0x80B(CUser* user, GameItemRemake5Incoming_EP6_4* incoming)
    {
        if (!incoming->lapisBag1 || incoming->lapisBag1 > user->bagsUnlocked)
            return;

        if (incoming->lapisSlot1 >= ItemSlotCount)
            return;

        auto& lapis1 = user->inventory[incoming->lapisBag1][incoming->lapisSlot1];
        if (!lapis1)
            return;

        if (!incoming->lapisBag2 || incoming->lapisBag2 > user->bagsUnlocked)
            return;

        if (incoming->lapisSlot2 >= ItemSlotCount)
            return;

        auto& lapis2 = user->inventory[incoming->lapisBag2][incoming->lapisSlot2];
        if (!lapis2)
            return;

        if (!incoming->lapisBag3 || incoming->lapisBag3 > user->bagsUnlocked)
            return;

        if (incoming->lapisSlot3 >= ItemSlotCount)
            return;

        auto& lapis3 = user->inventory[incoming->lapisBag3][incoming->lapisSlot3];
        if (!lapis3)
            return;

        if (!incoming->vialBag || incoming->vialBag > user->bagsUnlocked)
            return;

        if (incoming->vialSlot >= ItemSlotCount)
            return;

        auto& vial = user->inventory[incoming->vialBag][incoming->vialSlot];
        if (!vial)
            return;

        if (lapis1->type != ItemType::Lapis)
            return;

        if (lapis2->type != ItemType::Lapis)
            return;

        if (lapis3->type != ItemType::Lapis)
            return;

        if (vial->info->effect != ItemEffect::CrowleyEssence)
            return;

        if (lapis1->info->reqIg == 30 || lapis1->info->reqIg == 99)
            return;

        if (lapis2->info->reqIg == 30 || lapis2->info->reqIg == 99)
            return;

        if (lapis3->info->reqIg == 30 || lapis3->info->reqIg == 99)
            return;

        int requiredCount = 0;
        if (lapis1->info->reqIg >= 36)
            ++requiredCount;

        if (lapis2->info->reqIg >= 36)
            ++requiredCount;

        if (lapis3->info->reqIg >= 36)
            ++requiredCount;

        if (vial->count < requiredCount)
            return;

        auto itemId1 = lapis1->info->itemId;
        auto itemId2 = lapis2->info->itemId;
        auto itemId3 = lapis3->info->itemId;
        auto predicate = ItemRemakeContainsF(itemId1, itemId2, itemId3);

        auto itemRemake = std::find_if(g_itemRemake5.cbegin(), g_itemRemake5.cend(), predicate);
        if (itemRemake != g_itemRemake5.cend())
        {
            auto newItemInfo = CGameData::GetItemInfo(itemRemake->newItemType, itemRemake->newItemTypeId);
            if (!newItemInfo)
                return;

            UserHelper::ItemRemove(user, incoming->lapisBag1, incoming->lapisSlot1, 1);
            UserHelper::ItemRemove(user, incoming->lapisBag2, incoming->lapisSlot2, 1);
            UserHelper::ItemRemove(user, incoming->lapisBag3, incoming->lapisSlot3, 1);
            UserHelper::ItemRemove(user, incoming->vialBag, incoming->vialSlot, requiredCount);

            int bag{}, slot{};
            if (UserHelper::ItemCreate(user, newItemInfo, 1, bag, slot))
            {
                GameItemRemake5Outgoing success{};
                success.result = GameItemRemakeResult::Success;
                success.newItem.bag = bag;
                success.newItem.slot = slot;
                success.newItem.type = newItemInfo->type;
                success.newItem.typeId = newItemInfo->typeId;
                success.newItem.count = 1;
                NetworkHelper::Send(user, &success, sizeof(GameItemRemake5Outgoing));
            }
        }
        else
        {
            GameItemRemake5Outgoing failure{};
            failure.result = GameItemRemakeResult::Failure;
            NetworkHelper::Send(user, &failure, sizeof(GameItemRemake5Outgoing));
        }
    }

    /// <summary>
    /// Handles incoming 0x80C packets.
    /// </summary>
    void handler_0x80C(CUser* user, GameItemRemake4Incoming_EP6_4* incoming)
    {
        if (!incoming->lapisianBag1 || incoming->lapisianBag1 > user->bagsUnlocked)
            return;

        if (incoming->lapisianSlot1 >= ItemSlotCount)
            return;

        auto& lapisian1 = user->inventory[incoming->lapisianBag1][incoming->lapisianSlot1];
        if (!lapisian1)
            return;

        if (!incoming->lapisianBag2 || incoming->lapisianBag2 > user->bagsUnlocked)
            return;

        if (incoming->lapisianSlot2 >= ItemSlotCount)
            return;

        auto& lapisian2 = user->inventory[incoming->lapisianBag2][incoming->lapisianSlot2];
        if (!lapisian2)
            return;

        if (!incoming->lapisianBag3 || incoming->lapisianBag3 > user->bagsUnlocked)
            return;

        if (incoming->lapisianSlot3 >= ItemSlotCount)
            return;

        auto& lapisian3 = user->inventory[incoming->lapisianBag3][incoming->lapisianSlot3];
        if (!lapisian3)
            return;

        if (!incoming->vialBag || incoming->vialBag > user->bagsUnlocked)
            return;

        if (incoming->vialSlot >= ItemSlotCount)
            return;

        auto& vial = user->inventory[incoming->vialBag][incoming->vialSlot];
        if (!vial)
            return;

        if (lapisian1->type != ItemType::Lapisian)
            return;

        if (lapisian2->type != ItemType::Lapisian)
            return;

        if (lapisian3->type != ItemType::Lapisian)
            return;

        if (vial->info->effect != ItemEffect::CrowleyLiquid)
            return;

        auto itemId1 = lapisian1->info->itemId;
        auto itemId2 = lapisian2->info->itemId;
        auto itemId3 = lapisian3->info->itemId;
        auto predicate = ItemRemakeContainsF(itemId1, itemId2, itemId3);

        auto itemRemake = std::find_if(g_itemRemake4.cbegin(), g_itemRemake4.cend(), predicate);
        if (itemRemake != g_itemRemake4.cend())
        {
            auto newItemInfo = CGameData::GetItemInfo(itemRemake->newItemType, itemRemake->newItemTypeId);
            if (!newItemInfo)
                return;

            UserHelper::ItemRemove(user, incoming->lapisianBag1, incoming->lapisianSlot1, 1);
            UserHelper::ItemRemove(user, incoming->lapisianBag2, incoming->lapisianSlot2, 1);
            UserHelper::ItemRemove(user, incoming->lapisianBag3, incoming->lapisianSlot3, 1);
            UserHelper::ItemRemove(user, incoming->vialBag, incoming->vialSlot, 1);

            int bag{}, slot{};
            if (UserHelper::ItemCreate(user, newItemInfo, 1, bag, slot))
            {
                GameItemRemake4Outgoing success{};
                success.result = GameItemRemakeResult::Success;
                success.newItem.bag = bag;
                success.newItem.slot = slot;
                success.newItem.type = newItemInfo->type;
                success.newItem.typeId = newItemInfo->typeId;
                success.newItem.count = 1;
                NetworkHelper::Send(user, &success, sizeof(GameItemRemake4Outgoing));
            }
        }
        else
        {
            GameItemRemake4Outgoing failure{};
            failure.result = GameItemRemakeResult::Failure;
            NetworkHelper::Send(user, &failure, sizeof(GameItemRemake4Outgoing));
        }
    }

    /// <summary>
    /// Handles incoming 0x80D packets.
    /// </summary>
    void handler_0x80D(CUser* user, GameRuneUpgradeIncoming_EP6_4* incoming)
    {
        if (!incoming->runeBag || incoming->runeBag > user->bagsUnlocked)
            return;

        if (incoming->runeSlot >= ItemSlotCount)
            return;

        auto& rune = user->inventory[incoming->runeBag][incoming->runeSlot];
        if (!rune)
            return;

        if (!incoming->vialBag || incoming->vialBag > user->bagsUnlocked)
            return;

        if (incoming->vialSlot >= ItemSlotCount)
            return;

        auto& vial = user->inventory[incoming->vialBag][incoming->vialSlot];
        if (!vial)
            return;

        if (rune->count < 2)
            return;

        if (rune->info->effect != ItemEffect::RecreationRune)
        {
            GameRuneUpgradeOutgoing failure{};
            failure.result = GameRuneUpgradeResult::Failure;
            NetworkHelper::Send(user, &failure, sizeof(GameRuneUpgradeOutgoing));
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
                GameRuneUpgradeOutgoing success{};
                success.result = GameRuneUpgradeResult::Success;
                success.newItem.bag = bag;
                success.newItem.slot = slot;
                success.newItem.type = newItemInfo->type;
                success.newItem.typeId = newItemInfo->typeId;
                success.newItem.count = 1;
                NetworkHelper::Send(user, &success, sizeof(GameRuneUpgradeOutgoing));
            }
        }
        else
        {
            GameRuneUpgradeOutgoing failure{};
            failure.result = GameRuneUpgradeResult::Failure;
            NetworkHelper::Send(user, &failure, sizeof(GameRuneUpgradeOutgoing));
        }
    }

    /// <summary>
    /// Handles incoming 0x80E packets.
    /// </summary>
    void handler_0x80E(CUser* user, GameLapisianUpgradeIncoming* incoming)
    {
        if (!incoming->cubeBag || incoming->cubeBag > user->bagsUnlocked)
            return;

        if (incoming->cubeSlot >= ItemSlotCount)
            return;

        auto& cube = user->inventory[incoming->cubeBag][incoming->cubeSlot];
        if (!cube)
            return;

        // The data does not specify an item effect
        if (cube->info->itemId != 101101)
            return;

        if (incoming->lapisianType != ItemType::Lapisian)
            return;

        auto oldItemInfo = CGameData::GetItemInfo(incoming->lapisianType, incoming->lapisianTypeId);
        if (!oldItemInfo)
            return;

        auto newItemInfo = CGameData::GetItemInfo(incoming->lapisianType, incoming->lapisianTypeId + 1);
        if (!newItemInfo)
            return;

        // Failure result values are unclear. The client executes the same code 
        // as long as the value is nonzero and not greater than 3.

        GameLapisianUpgradeOutgoing failure{};
        failure.result = GameLapisianUpgradeResult::Unknown1;

        auto successRate = oldItemInfo->reqRec;
        if (successRate != 10000)
        {
            NetworkHelper::Send(user, &failure, sizeof(GameLapisianUpgradeOutgoing));
            return;
        }

        auto lapisianLv = oldItemInfo->attackTime;
        if (lapisianLv < 6 || lapisianLv > 19)
        {
            NetworkHelper::Send(user, &failure, sizeof(GameLapisianUpgradeOutgoing));
            return;
        }

        auto requiredCount = oldItemInfo->reqLuc;
        if (!requiredCount)
        {
            NetworkHelper::Send(user, &failure, sizeof(GameLapisianUpgradeOutgoing));
            return;
        }

        CUser::ItemUseNSend(user, incoming->cubeBag, incoming->cubeSlot, false);

        for (int i = 0; i < requiredCount; ++i)
        {
            auto type = oldItemInfo->type;
            auto typeId = oldItemInfo->typeId;

            int bag{}, slot{};
            if (!ItemFinder(user, bag, slot, ItemCountGreaterEqualF(type, typeId, 1)))
                return;

            if (!UserHelper::ItemRemove(user, bag, slot, 1))
                return;
        }

        int bag{}, slot{};
        if (UserHelper::ItemCreate(user, newItemInfo, 1, bag, slot))
        {
            GameLapisianUpgradeOutgoing success{};
            success.result = GameLapisianUpgradeResult::Success;
            success.newItem.bag = bag;
            success.newItem.slot = slot;
            success.newItem.type = newItemInfo->type;
            success.newItem.typeId = newItemInfo->typeId;
            success.newItem.count = 1;
            NetworkHelper::Send(user, &success, sizeof(GameLapisianUpgradeOutgoing));
        }
    }

    /// <summary>
    /// Handles incoming 0x806 packets. Supports vanilla recreation runes. Adding custom 
    /// item effects (e.g., perfect) requires a client modification.
    /// </summary>
    void handler_0x806(CUser* user, GameItemComposeIncoming_EP6_4* incoming)
    {
        if (!incoming->runeBag || incoming->runeBag > user->bagsUnlocked)
            return;

        if (incoming->runeSlot >= ItemSlotCount)
            return;

        auto& rune = user->inventory[incoming->runeBag][incoming->runeSlot];
        if (!rune)
            return;

        if (incoming->itemBag > user->bagsUnlocked)
            return;

        if (incoming->itemSlot >= ItemSlotCount)
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

        if (!item->info->reqWis || item->info->reqWis > ItemCraft_MAX)
        {
            NetworkHelper::Send(user, &failure, sizeof(GameItemComposeOutgoing));
            return;
        }

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
    void handler_0x830(CUser* user, GameChaoticSquareListIncoming* incoming)
    {
        if (!incoming->chaoticSquareBag || incoming->chaoticSquareBag > user->bagsUnlocked)
            return;

        if (incoming->chaoticSquareSlot >= ItemSlotCount)
            return;

        auto& chaoticSquare = user->inventory[incoming->chaoticSquareBag][incoming->chaoticSquareSlot];
        if (!chaoticSquare)
            return;

        if (chaoticSquare->info->effect != ItemEffect::ChaoticSquare)
            return;

        user->savePosUseBag = incoming->chaoticSquareBag;
        user->savePosUseSlot = incoming->chaoticSquareSlot;

        CUser::CancelActionExc(user);
        MyShop::Ended(&user->myShop);

        auto itemId = chaoticSquare->info->itemId;
        for (const auto& chaoticSquare : g_chaoticSquares)
        {
            if (chaoticSquare.itemId == itemId)
            {
                GameChaoticSquareListOutgoing outgoing{};
                outgoing.newItemType = chaoticSquare.newItemType;
                outgoing.newItemTypeId = chaoticSquare.newItemTypeId;
                outgoing.goldPerPercentage = ItemSynthesisConstants::GoldPerPercentage;
                NetworkHelper::Send(user, &outgoing, sizeof(GameChaoticSquareListOutgoing));
            }
        }
    }

    /// <summary>
    /// Handles incoming 0x831 packets.
    /// </summary>
    void handler_0x831(CUser* user, GameItemSynthesisRecipeIncoming* incoming)
    {
        auto& chaoticSquare = user->inventory[user->savePosUseBag][user->savePosUseSlot];
        if (!chaoticSquare)
            return;

        if (chaoticSquare->info->effect != ItemEffect::ChaoticSquare)
            return;

        auto it = g_itemSyntheses.find(chaoticSquare->info->itemId);
        if (it == g_itemSyntheses.end())
            return;

        if (incoming->index >= it->second.size())
            return;

        auto& synthesis = it->second[incoming->index];
        if (incoming->newItemType != synthesis.newItemType || incoming->newItemTypeId != synthesis.newItemTypeId)
            return;

        GameItemSynthesisRecipeOutgoing outgoing{};
        outgoing.successRate = synthesis.successRate;
        outgoing.materialType = synthesis.materialType;
        outgoing.newItemType = synthesis.newItemType;
        outgoing.materialTypeId = synthesis.materialTypeId;
        outgoing.newItemTypeId = synthesis.newItemTypeId;
        outgoing.materialCount = synthesis.materialCount;
        outgoing.newItemCount = synthesis.newItemCount;
        NetworkHelper::Send(user, &outgoing, sizeof(GameItemSynthesisRecipeOutgoing));
    }

    /// <summary>
    /// Handles incoming 0x832 packets.
    /// </summary>
    void handler_0x832(CUser* user, GameItemSynthesisIncoming* incoming)
    {
        if (!incoming->chaoticSquareBag || incoming->chaoticSquareBag > user->bagsUnlocked)
            return;

        if (incoming->chaoticSquareSlot >= ItemSlotCount)
            return;

        auto& chaoticSquare = user->inventory[incoming->chaoticSquareBag][incoming->chaoticSquareSlot];
        if (!chaoticSquare)
            return;

        if (chaoticSquare->info->effect != ItemEffect::ChaoticSquare)
            return;

        auto it = g_itemSyntheses.find(chaoticSquare->info->itemId);
        if (it == g_itemSyntheses.end())
            return;

        if (incoming->index >= it->second.size())
            return;

        auto& synthesis = it->second[incoming->index];
        auto newItemInfo = CGameData::GetItemInfo(synthesis.newItemType, synthesis.newItemTypeId);
        if (!newItemInfo)
            return;

        if (incoming->money > user->money)
            return;

        auto successRate = synthesis.successRate;
        auto goldPerPercentage = ItemSynthesisConstants::GoldPerPercentage;

        if (goldPerPercentage)
        {
            auto money = incoming->money;
            if (money > ItemSynthesisConstants::MaxMoney)
                money = ItemSynthesisConstants::MaxMoney;

            if (money >= ItemSynthesisConstants::MinMoney)
            {
                auto bonus = ((double)money / goldPerPercentage) * 100.0;
                successRate += static_cast<int>(bonus);

                user->money -= money;
                CUser::SendDBMoney(user);
            }
        }

        if (incoming->hammerBag != 0)
        {
            if (incoming->hammerBag > user->bagsUnlocked)
                return;

            if (incoming->hammerSlot >= ItemSlotCount)
                return;

            auto& hammer = user->inventory[incoming->hammerBag][incoming->hammerSlot];
            if (!hammer)
                return;

            if (hammer->info->effect != ItemEffect::CraftingHammer)
                return;

            successRate += hammer->info->reqVg * 100;
            CUser::ItemUseNSend(user, incoming->hammerBag, incoming->hammerSlot, false);
        }

        CUser::ItemUseNSend(user, incoming->chaoticSquareBag, incoming->chaoticSquareSlot, false);

        for (const auto& [type, typeId, count] : std::views::zip(
            std::as_const(synthesis.materialType),
            std::as_const(synthesis.materialTypeId),
            std::as_const(synthesis.materialCount)
        ))
        {
            if (!type || !typeId || !count)
                continue;

            int bag{}, slot{};
            if (!ItemFinder(user, bag, slot, ItemCountGreaterEqualF(type, typeId, count)))
                return;

            if (!UserHelper::ItemRemove(user, bag, slot, count))
                return;
        }

        int randomValue = 0;
        if (successRate < ItemSynthesisConstants::MaxSuccessRate)
        {
            std::random_device seed;
            std::mt19937 eng(seed());

            std::uniform_int_distribution<int> uni(
                ItemSynthesisConstants::MinSuccessRate,
                ItemSynthesisConstants::MaxSuccessRate);

            randomValue = uni(eng);
        }

        if (randomValue <= successRate)
        {
            CUser::ItemCreate(user, newItemInfo, synthesis.newItemCount);

            GameItemSynthesisOutgoing success{};
            success.result = GameItemSynthesisResult::Success;
            NetworkHelper::Send(user, &success, sizeof(GameItemSynthesisOutgoing));
        }
        else
        {
            GameItemSynthesisOutgoing failure{};
            failure.result = GameItemSynthesisResult::Failure;
            NetworkHelper::Send(user, &failure, sizeof(GameItemSynthesisOutgoing));
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
    void handler_0x811(CUser* user, GameItemAbilityTransferIncoming* incoming)
    {
        constexpr int baseSuccessRate = 30;

        if (!incoming->cubeBag || incoming->cubeBag > user->bagsUnlocked)
            return;

        if (incoming->cubeSlot >= ItemSlotCount)
            return;

        auto& cube = user->inventory[incoming->cubeBag][incoming->cubeSlot];
        if (!cube)
            return;

        if (incoming->srcBag > user->bagsUnlocked)
            return;

        if (incoming->srcSlot >= ItemSlotCount)
            return;

        auto& source = user->inventory[incoming->srcBag][incoming->srcSlot];
        if (!source)
            return;

        if (incoming->destBag > user->bagsUnlocked)
            return;

        if (incoming->destSlot >= ItemSlotCount)
            return;

        auto& target = user->inventory[incoming->destBag][incoming->destSlot];
        if (!target)
            return;

        if (cube->info->effect != ItemEffect::ItemAbilityTransfer)
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

        int successRate = baseSuccessRate;

        // 255 means the slot is empty
        if (incoming->catalystSlot != 255)
        {
            if (!incoming->catalystBag || incoming->catalystBag > user->bagsUnlocked)
                return;

            if (incoming->catalystSlot >= ItemSlotCount)
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

        GameItemAbilityTransferOutgoing outgoing{};
        outgoing.result = GameItemAbilityTransferResult::Failure;
        outgoing.srcBag = incoming->srcBag;
        outgoing.srcSlot = incoming->srcSlot;
        outgoing.destBag = incoming->destBag;
        outgoing.destSlot = incoming->destSlot;

        int randomValue = 0;
        if (successRate < 100)
        {
            std::random_device seed;
            std::mt19937 eng(seed());

            std::uniform_int_distribution<int> uni(1, 100);
            randomValue = uni(eng);
        }

        if (randomValue <= successRate)
        {
            outgoing.result = GameItemAbilityTransferResult::Success;

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

        NetworkHelper::Send(user, &outgoing, sizeof(GameItemAbilityTransferOutgoing));
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
            handler_0x80B(user, reinterpret_cast<GameItemRemake5Incoming_EP6_4*>(packet));
            break;
        }
        case 0x80C:
        {
            handler_0x80C(user, reinterpret_cast<GameItemRemake4Incoming_EP6_4*>(packet));
            break;
        }
        case 0x80D:
        {
            handler_0x80D(user, reinterpret_cast<GameRuneUpgradeIncoming_EP6_4*>(packet));
            break;
        }
        case 0x80E:
        {
            handler_0x80E(user, reinterpret_cast<GameLapisianUpgradeIncoming*>(packet));
            break;
        }
        case 0x811:
        {
            handler_0x811(user, reinterpret_cast<GameItemAbilityTransferIncoming*>(packet));
            break;
        }
        case 0x830:
        {
            handler_0x830(user, reinterpret_cast<GameChaoticSquareListIncoming*>(packet));
            break;
        }
        case 0x831:
        {
            handler_0x831(user, reinterpret_cast<GameItemSynthesisRecipeIncoming*>(packet));
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
