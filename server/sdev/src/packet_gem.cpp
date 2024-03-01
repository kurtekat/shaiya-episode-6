#include <map>
#include <random>
#include <ranges>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>
#include <include/shaiya/packets/0800.h>
#include <include/shaiya/packets/dbAgent/0700.h>
#include <include/shaiya/packets/gameLog/0400.h>
#include <include/shaiya/include/CGameData.h>
#include <include/shaiya/include/CItem.h>
#include <include/shaiya/include/CUser.h>
#include <include/shaiya/include/CZone.h>
#include <include/shaiya/include/SConnection.h>
#include <include/shaiya/include/SConnectionTBaseReconnect.h>
#include <include/shaiya/include/Synthesis.h>
using namespace shaiya;

namespace packet_gem
{
    int find_available_slot(CUser* user, int bag)
    {
        for (int slot = 0; slot < max_inventory_slot; ++slot)
            if (!user->inventory[bag][slot])
                return slot;

        return -1;
    }

    bool is_perfect_lapisian(CItem* lapisian, CItem* upgradeItem)
    {
        auto enchantStep = CItem::GetEnchantStep(upgradeItem);
        auto lapisianType = static_cast<CGameData::ItemPerfectLapisianType>(lapisian->itemInfo->country);

        if (CItem::IsWeapon(upgradeItem))
        {
            if (enchantStep < 10)
            {
                switch (lapisian->itemInfo->itemId)
                {
                case 95004:
                case 95005:
                    return true;
                default:
                    break;
                }
            }

            if (enchantStep == lapisian->itemInfo->range)
                if (lapisianType == CGameData::ItemPerfectLapisianType::Weapon)
                    return true;
        }
        else
        {
            if (enchantStep < 10)
            {
                switch (lapisian->itemInfo->itemId)
                {
                case 95005:
                case 95009:
                    return true;
                default:
                    break;
                }
            }

            if (enchantStep == lapisian->itemInfo->range)
                if (lapisianType == CGameData::ItemPerfectLapisianType::Armor)
                    return true;
        }

        return false;
    }

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

        ItemRuneCombineOutgoing outgoing{};
        outgoing.result = ItemRuneCombineResult::Failure;

        if (rune->count < 2 || rune->itemInfo->effect != CGameData::ItemEffect::ItemCompose)
        {
            SConnection::Send(&user->connection, &outgoing, 3);
            return;
        }

        CGameData::ItemInfo* itemInfo = nullptr;

        switch (vial->itemInfo->effect)
        {
        case CGameData::ItemEffect::ItemRemakeStr:
            itemInfo = CGameData::GetItemInfo(101, 1);
            break;
        case CGameData::ItemEffect::ItemRemakeDex:
            itemInfo = CGameData::GetItemInfo(101, 2);
            break;
        case CGameData::ItemEffect::ItemRemakeInt:
            itemInfo = CGameData::GetItemInfo(101, 3);
            break;
        case CGameData::ItemEffect::ItemRemakeWis:
            itemInfo = CGameData::GetItemInfo(101, 4);
            break;
        case CGameData::ItemEffect::ItemRemakeRec:
            itemInfo = CGameData::GetItemInfo(101, 5);
            break;
        case CGameData::ItemEffect::ItemRemakeLuc:
            itemInfo = CGameData::GetItemInfo(101, 6);
            break;
        default:
            break;
        }

        if (!itemInfo)
        {
            SConnection::Send(&user->connection, &outgoing, 3);
            return;
        }

        outgoing.result = ItemRuneCombineResult::Success;
        outgoing.bag = 1;
        outgoing.slot = 0;
        outgoing.type = itemInfo->type;
        outgoing.typeId = itemInfo->typeId;
        outgoing.count = 1;

        while (outgoing.bag <= user->bagsUnlocked)
        {
            outgoing.slot = find_available_slot(user, outgoing.bag);

            if (outgoing.slot != -1)
            {
                if (!CUser::ItemCreate(user, itemInfo, outgoing.count))
                    break;

                SConnection::Send(&user->connection, &outgoing, sizeof(ItemRuneCombineOutgoing));

                CUser::ItemUseNSend(user, incoming->runeBag, incoming->runeSlot, false);
                CUser::ItemUseNSend(user, incoming->runeBag, incoming->runeSlot, false);
                CUser::ItemUseNSend(user, incoming->vialBag, incoming->vialSlot, false);
                break;
            }

            ++outgoing.bag;
        }
    }

    void item_compose_handler(CUser* user, ItemComposeIncoming* incoming)
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

        ItemComposeOutgoing outgoing{};
        outgoing.result = ItemComposeResult::Failure;

        if (item->itemInfo->realType > CGameData::ItemRealType::Bracelet)
        {
            SConnection::Send(&user->connection, &outgoing, 3);
            return;
        }

        if (!item->itemInfo->composeCount)
        {
            SConnection::Send(&user->connection, &outgoing, 3);
            return;
        }

        if (item->itemInfo->reqWis <= 0 || item->itemInfo->reqWis >= 100)
        {
            SConnection::Send(&user->connection, &outgoing, 3);
            return;
        }

        if (item->makeType == ItemMakeType::QuestResult)
        {
            SConnection::Send(&user->connection, &outgoing, 3);
            return;
        }

        GameLogItemComposeIncoming log{};
        CUser::SetGameLogMain(user, &log);

        log.oldItemUid = item->uniqueId;
        log.oldItemId = item->itemInfo->itemId;
        log.oldCraftName = item->craftName;

        std::random_device seed;
        std::mt19937 eng(seed());

        std::uniform_int_distribution<int> uni(1, item->itemInfo->reqWis);
        std::uint8_t bonus = uni(eng);
        std::string text = std::to_string(bonus);

        if (bonus < 10)
            text.insert(text.begin(), 1, '0');

        auto maxHealth = user->maxHealth;
        auto maxMana = user->maxHealth;
        auto maxStamina = user->maxHealth;

        switch (rune->itemInfo->effect)
        {
        case CGameData::ItemEffect::ItemCompose:
            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);
                CItem::ReGenerationCraftExpansion(item, true);
                CUser::ItemEquipmentOptionAdd(user, item);

                if (!user->initEquipment)
                {
                    if (maxHealth != user->maxHealth)
                        CUser::SendMaxHP(user);

                    if (maxMana != user->maxMana)
                        CUser::SendMaxMP(user);

                    if (maxStamina != user->maxStamina)
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

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftStrength = bonus;
                item->craftName[0] = text[0];
                item->craftName[1] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);

                if (!user->initEquipment)
                {
                    if (maxHealth != user->maxHealth)
                        CUser::SendMaxHP(user);

                    if (maxMana != user->maxMana)
                        CUser::SendMaxMP(user);

                    if (maxStamina != user->maxStamina)
                        CUser::SendMaxSP(user);
                }

                CUser::SetAttack(user);
                break;
            }

            item->craftStrength = bonus;
            item->craftName[0] = text[0];
            item->craftName[1] = text[1];

            break;
        case CGameData::ItemEffect::ItemComposeDex:
            if (!item->craftDexterity)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftDexterity = bonus;
                item->craftName[2] = text[0];
                item->craftName[3] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);

                if (!user->initEquipment)
                {
                    if (maxHealth != user->maxHealth)
                        CUser::SendMaxHP(user);

                    if (maxMana != user->maxMana)
                        CUser::SendMaxMP(user);

                    if (maxStamina != user->maxStamina)
                        CUser::SendMaxSP(user);
                }

                CUser::SetAttack(user);
                break;
            }

            item->craftDexterity = bonus;
            item->craftName[2] = text[0];
            item->craftName[3] = text[1];

            break;
        case CGameData::ItemEffect::ItemComposeInt:
            if (!item->craftIntelligence)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftIntelligence = bonus;
                item->craftName[6] = text[0];
                item->craftName[7] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);

                if (!user->initEquipment)
                {
                    if (maxHealth != user->maxHealth)
                        CUser::SendMaxHP(user);

                    if (maxMana != user->maxMana)
                        CUser::SendMaxMP(user);

                    if (maxStamina != user->maxStamina)
                        CUser::SendMaxSP(user);
                }

                CUser::SetAttack(user);
                break;
            }

            item->craftIntelligence = bonus;
            item->craftName[6] = text[0];
            item->craftName[7] = text[1];

            break;
        case CGameData::ItemEffect::ItemComposeWis:
            if (!item->craftWisdom)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftWisdom = bonus;
                item->craftName[8] = text[0];
                item->craftName[9] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);

                if (!user->initEquipment)
                {
                    if (maxHealth != user->maxHealth)
                        CUser::SendMaxHP(user);

                    if (maxMana != user->maxMana)
                        CUser::SendMaxMP(user);

                    if (maxStamina != user->maxStamina)
                        CUser::SendMaxSP(user);
                }

                CUser::SetAttack(user);
                break;
            }

            item->craftWisdom = bonus;
            item->craftName[8] = text[0];
            item->craftName[9] = text[1];

            break;
        case CGameData::ItemEffect::ItemComposeRec:
            if (!item->craftReaction)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftReaction = bonus;
                item->craftName[4] = text[0];
                item->craftName[5] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);

                if (!user->initEquipment)
                {
                    if (maxHealth != user->maxHealth)
                        CUser::SendMaxHP(user);

                    if (maxMana != user->maxMana)
                        CUser::SendMaxMP(user);

                    if (maxStamina != user->maxStamina)
                        CUser::SendMaxSP(user);
                }

                CUser::SetAttack(user);
                break;
            }

            item->craftReaction = bonus;
            item->craftName[4] = text[0];
            item->craftName[5] = text[1];

            break;
        case CGameData::ItemEffect::ItemComposeLuc:
            if (!item->craftLuck)
                return;

            if (!incoming->itemBag)
            {
                CUser::ItemEquipmentOptionRem(user, item);

                item->craftLuck = bonus;
                item->craftName[10] = text[0];
                item->craftName[11] = text[1];

                CUser::ItemEquipmentOptionAdd(user, item);

                if (!user->initEquipment)
                {
                    if (maxHealth != user->maxHealth)
                        CUser::SendMaxHP(user);

                    if (maxMana != user->maxMana)
                        CUser::SendMaxMP(user);

                    if (maxStamina != user->maxStamina)
                        CUser::SendMaxSP(user);
                }

                CUser::SetAttack(user);
                break;
            }

            item->craftLuck = bonus;
            item->craftName[10] = text[0];
            item->craftName[11] = text[1];

            break;
        default:
            SConnection::Send(&user->connection, &outgoing, 3);
            return;
        }

        outgoing.result = ItemComposeResult::Success;
        outgoing.bag = incoming->itemBag;
        outgoing.slot = incoming->itemSlot;
        outgoing.craftName = item->craftName;
        SConnection::Send(&user->connection, &outgoing, sizeof(ItemComposeOutgoing));

        UserItemCraftNameIncoming packet{ 0x717, user->userId, incoming->itemBag, incoming->itemSlot, item->craftName };
        SConnectionTBaseReconnect::Send(g_pClientToDBAgent, &packet, sizeof(UserItemCraftNameIncoming));

        log.itemUid = item->uniqueId;
        log.itemId = item->itemInfo->itemId;
        log.itemName = item->itemInfo->itemName;
        log.gems = item->gems;
        log.makeTime = item->makeTime;
        log.craftName = item->craftName;
        SConnectionTBaseReconnect::Send(g_pClientToGameLog, &log, sizeof(GameLogItemComposeIncoming));

        CUser::ItemUseNSend(user, incoming->runeBag, incoming->runeSlot, false);
    }

    void item_synthesis_list_handler(CUser* user, ItemSynthesisListIncoming* incoming)
    {
        if (user->stateType == UserStateType::Death)
            return;

        if (!incoming->squareBag || incoming->squareBag > user->bagsUnlocked || incoming->squareSlot >= max_inventory_slot)
            return;

        auto& square = user->inventory[incoming->squareBag][incoming->squareSlot];
        if (!square)
            return;

        if (square->itemInfo->effect != CGameData::ItemEffect::ChaoticSquare)
            return;

        auto synthesis = g_synthesis.find(square->itemInfo->itemId);
        if (synthesis == g_synthesis.end())
            return;

        user->recallItemBag = incoming->squareBag;
        user->recallItemSlot = incoming->squareSlot;

        CUser::CancelActionExc(user);
        MyShop::Ended(&user->myShop);

        ItemSynthesisListOutgoing outgoing{};
        outgoing.goldPerPercentage = synthesis_min_money;

        int index = 0;
        for (const auto& synthesis : synthesis->second)
        {
            outgoing.createType[index] = synthesis.createType;
            outgoing.createTypeId[index] = synthesis.createTypeId;

            ++index;

            if (index < 10)
                continue;
            else
            {
                SConnection::Send(&user->connection, &outgoing, sizeof(ItemSynthesisListOutgoing));

                outgoing.createType.fill(0);
                outgoing.createTypeId.fill(0);
                index = 0;
            }
        }

        if (!index)
            return;

        SConnection::Send(&user->connection, &outgoing, sizeof(ItemSynthesisListOutgoing));
    }

    void item_synthesis_material_handler(CUser* user, ItemSynthesisMaterialIncoming* incoming)
    {
        auto& square = user->inventory[user->recallItemBag][user->recallItemSlot];
        if (!square)
            return;

        if (square->itemInfo->effect != CGameData::ItemEffect::ChaoticSquare)
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
        SConnection::Send(&user->connection, &outgoing, sizeof(ItemSynthesisMaterialOutgoing));
    }

    void item_synthesis_handler(CUser* user, ItemSynthesisIncoming* incoming)
    {
        if (!incoming->squareBag || incoming->squareBag > user->bagsUnlocked || incoming->squareSlot >= max_inventory_slot)
            return;

        auto& square = user->inventory[incoming->squareBag][incoming->squareSlot];
        if (!square)
            return;

        if (square->itemInfo->effect != CGameData::ItemEffect::ChaoticSquare)
            return;

        if (incoming->money > user->money)
            return;

        auto it = g_synthesis.find(square->itemInfo->itemId);
        if (it == g_synthesis.end())
            return;

        if (incoming->index >= it->second.size())
            return;

        auto& synthesis = it->second[incoming->index];
        auto itemInfo = CGameData::GetItemInfo(synthesis.createType, synthesis.createTypeId);
        if (!itemInfo)
            return;

        auto money = (incoming->money > synthesis_max_money) ? synthesis_max_money : incoming->money;
        auto successRate = synthesis.successRate;

        if (money >= synthesis_min_money)
            successRate += (money / synthesis_min_money) * 100;

        if (incoming->hammerBag > user->bagsUnlocked || incoming->hammerSlot >= max_inventory_slot)
            return;

        if (incoming->hammerBag > 0)
        {
            auto& hammer = user->inventory[incoming->hammerBag][incoming->hammerSlot];
            if (!hammer)
                return;

            if (hammer->itemInfo->effect != CGameData::ItemEffect::CraftingHammer)
                return;

            successRate += hammer->itemInfo->reqVg * 100;
            CUser::ItemUseNSend(user, incoming->hammerBag, incoming->hammerSlot, false);
        }

        CUser::ItemUseNSend(user, incoming->squareBag, incoming->squareSlot, false);

        user->money -= money;
        CUser::SendDBMoney(user);

        int randomRate = 0;
        if (successRate < synthesis_max_success_rate)
        {
            std::random_device seed;
            std::mt19937 eng(seed());

            std::uniform_int_distribution<int> uni(
                synthesis_min_success_rate, 
                synthesis_max_success_rate
            );

            randomRate = uni(eng);
        }

        const auto& materials = std::ranges::views::zip(
            std::as_const(synthesis.materialType),
            std::as_const(synthesis.materialTypeId),
            std::as_const(synthesis.materialCount)
        );

        bool hasMaterials = false;
        for (const auto& [type, typeId, count] : materials)
        {
            if (!type || !typeId || !count)
                continue;

            hasMaterials = Synthesis::useMaterial(user, type, typeId, count);
        }

        ItemSynthesisOutgoing outgoing{};
        outgoing.result = ItemSynthesisResult::Failure;

        if (hasMaterials && randomRate <= successRate)
        {
            CUser::ItemCreate(user, itemInfo, synthesis.createCount);
            outgoing.result = ItemSynthesisResult::Success;
        }

        SConnection::Send(&user->connection, &outgoing, sizeof(ItemSynthesisOutgoing));
    }

    void item_free_synthesis_handler(CUser* user, ItemFreeSynthesisIncoming* incoming)
    {
    }
}

unsigned u0x479FBC = 0x479FBC;
void __declspec(naked) naked_0x479FB4()
{
    __asm
    {
        movzx eax,word ptr[esi]
#ifdef SHAIYA_EP6_BLACKSMITH
        cmp eax,0x80D
        je case_0x80D
#endif
        cmp eax,0x830
        je case_0x830
        cmp eax,0x831
        je case_0x831
        cmp eax,0x832
        je case_0x832
        cmp eax,0x833
        je case_0x833

        // original
        add eax,-0x801
        jmp u0x479FBC

#ifdef SHAIYA_EP6_BLACKSMITH
        case_0x80D:
        pushad

        push esi // packet
        push edi // user
        call packet_gem::item_rune_combine_handler
        add esp,0x8
        
        popad

        jmp exit_switch
#endif

        // chaotic squares

        case_0x830:
        pushad

        push esi // packet
        push edi // user
        call packet_gem::item_synthesis_list_handler
        add esp,0x8
        
        popad

        jmp exit_switch

        case_0x831:
        pushad

        push esi // packet
        push edi // user
        call packet_gem::item_synthesis_material_handler
        add esp,0x8
        
        popad

        jmp exit_switch

        case_0x832:
        pushad

        push esi // packet
        push edi // user
        call packet_gem::item_synthesis_handler
        add esp,0x8
        
        popad

        jmp exit_switch

        case_0x833:
        pushad

        push esi // packet
        push edi // user
        call packet_gem::item_free_synthesis_handler
        add esp,0x8
        
        popad

        exit_switch:
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

    #ifdef SHAIYA_EP6_BLACKSMITH
    // CUser::PacketGem case 0x806
    util::detour((void*)0x47A003, naked_0x47A003, 9);
    // CUser::ItemLapisianAdd
    util::detour((void*)0x46CCF0, naked_0x46CCF0, 5);
    #endif
}
