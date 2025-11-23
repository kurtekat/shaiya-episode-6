#include <algorithm>
#include <shaiya/include/network/dbAgent/incoming/0700.h>
#include <shaiya/include/network/gameLog/incoming/0400.h>
#include "CItem.h"
#include "CUser.h"
#include "ItemEnchant.h"
#include "ItemHelper.h"
#include "ItemInfo.h"
#include "NetworkHelper.h"
using namespace shaiya;

void ItemHelper::SetCraftStrength(CItem* item, int value)
{
    value = std::clamp(value, 0, ItemCraft_MAX);
    char ones = value % 10;
    char tens = value / 10 % 10;
    ones += 48;
    tens += 48;

    item->craftStrength = value;
    item->craftName[0] = tens;
    item->craftName[1] = ones;
}

void ItemHelper::SetCraftDexterity(CItem* item, int value)
{
    value = std::clamp(value, 0, ItemCraft_MAX);
    char ones = value % 10;
    char tens = value / 10 % 10;
    ones += 48;
    tens += 48;

    item->craftDexterity = value;
    item->craftName[2] = tens;
    item->craftName[3] = ones;
}

void ItemHelper::SetCraftReaction(CItem* item, int value)
{
    value = std::clamp(value, 0, ItemCraft_MAX);
    char ones = value % 10;
    char tens = value / 10 % 10;
    ones += 48;
    tens += 48;

    item->craftReaction = value;
    item->craftName[4] = tens;
    item->craftName[5] = ones;
}

void ItemHelper::SetCraftIntelligence(CItem* item, int value)
{
    value = std::clamp(value, 0, ItemCraft_MAX);
    char ones = value % 10;
    char tens = value / 10 % 10;
    ones += 48;
    tens += 48;

    item->craftIntelligence = value;
    item->craftName[6] = tens;
    item->craftName[7] = ones;
}

void ItemHelper::SetCraftWisdom(CItem* item, int value)
{
    value = std::clamp(value, 0, ItemCraft_MAX);
    char ones = value % 10;
    char tens = value / 10 % 10;
    ones += 48;
    tens += 48;

    item->craftWisdom = value;
    item->craftName[8] = tens;
    item->craftName[9] = ones;
}

void ItemHelper::SetCraftLuck(CItem* item, int value)
{
    value = std::clamp(value, 0, ItemCraft_MAX);
    char ones = value % 10;
    char tens = value / 10 % 10;
    ones += 48;
    tens += 48;

    item->craftLuck = value;
    item->craftName[10] = tens;
    item->craftName[11] = ones;
}

void ItemHelper::SetCraftHealth(CItem* item, int value)
{
    value = std::clamp(value, 0, ItemCraft_MAX);
    char ones = value % 10;
    char tens = value / 10 % 10;
    ones += 48;
    tens += 48;

    item->craftHealth = value;
    item->craftName[12] = tens;
    item->craftName[13] = ones;
}

void ItemHelper::SetCraftMana(CItem* item, int value)
{
    value = std::clamp(value, 0, ItemCraft_MAX);
    char ones = value % 10;
    char tens = value / 10 % 10;
    ones += 48;
    tens += 48;

    item->craftMana = value;
    item->craftName[14] = tens;
    item->craftName[15] = ones;
}

void ItemHelper::SetCraftStamina(CItem* item, int value)
{
    value = std::clamp(value, 0, ItemCraft_MAX);
    char ones = value % 10;
    char tens = value / 10 % 10;
    ones += 48;
    tens += 48;

    item->craftStamina = value;
    item->craftName[16] = tens;
    item->craftName[17] = ones;
}

void ItemHelper::SetCraftAttackPower(CItem* item, int step)
{
    if (!CItem::IsWeapon(item))
        return;

    step = std::clamp(step, 0, ItemEnchant_MAX);
    int value = g_LapisianEnchantAddValue->step[step].weapon;
    char ones = step % 10;
    char tens = step / 10 % 10;
    ones += 48;
    tens += 48;

    item->craftAttackPower = value;
    item->craftName[18] = tens;
    item->craftName[19] = ones;
}

void ItemHelper::SetCraftAbsorption(CItem* item, int step)
{
    if (CItem::IsWeapon(item))
        return;

    step = std::clamp(step, 0, ItemEnchant_MAX);
    int value = g_LapisianEnchantAddValue->step[step].defense;

    step += 50;
    char ones = step % 10;
    char tens = step / 10 % 10;
    ones += 48;
    tens += 48;

    item->craftAbsorption = value;
    item->craftName[18] = tens;
    item->craftName[19] = ones;
}

void ItemHelper::CopyCraftExpansion(CItem* item, CItem* dest)
{
    dest->craftName = item->craftName;
    dest->craftStrength = item->craftStrength;
    dest->craftDexterity = item->craftDexterity;
    dest->craftReaction = item->craftReaction;
    dest->craftIntelligence = item->craftIntelligence;
    dest->craftWisdom = item->craftWisdom;
    dest->craftLuck = item->craftLuck;
    dest->craftHealth = item->craftHealth;
    dest->craftMana = item->craftMana;
    dest->craftStamina = item->craftStamina;
    dest->craftAttackPower = item->craftAttackPower;
    dest->craftAbsorption = item->craftAbsorption;
}

void ItemHelper::InitCraftExpansion(CItem* item)
{
    CItem::InitCraftExpansion(item);
    item->craftStrength = 0;
    item->craftDexterity = 0;
    item->craftReaction = 0;
    item->craftIntelligence = 0;
    item->craftWisdom = 0;
    item->craftLuck = 0;
    item->craftHealth = 0;
    item->craftMana = 0;
    item->craftStamina = 0;
    item->craftAttackPower = 0;
    item->craftAbsorption = 0;
}

void ItemHelper::SendDBAgentCraftName(CUser* user, CItem* item, int bag, int slot)
{
    DBAgentItemCraftUpdateIncoming outgoing{};
    outgoing.billingId = user->billingId;
    outgoing.bag = bag;
    outgoing.slot = slot;
    outgoing.craftName = item->craftName;
    NetworkHelper::SendDBAgent(&outgoing, sizeof(DBAgentItemCraftUpdateIncoming));
}

void ItemHelper::SendDBAgentGems(CUser* user, CItem* item, int bag, int slot)
{
    DBAgentItemGemUpdateIncoming outgoing{};
    outgoing.billingId = user->billingId;
    outgoing.bag = bag;
    outgoing.slot = slot;
    outgoing.gems = item->gems;
    outgoing.money = user->money;
    NetworkHelper::SendDBAgent(&outgoing, sizeof(DBAgentItemGemUpdateIncoming));
}

void ItemHelper::SendDBAgentCloakInfo(CUser* user, CItem* item, int bag, int slot)
{
    ItemHelper::SendDBAgentGems(user, item, bag, slot);
}