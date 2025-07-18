#include <string>
#include <shaiya/include/network/dbAgent/incoming/0700.h>
#include <shaiya/include/network/gameLog/incoming/0400.h>
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/CUser.h"
#include "include/shaiya/include/ItemHelper.h"
#include "include/shaiya/include/ItemInfo.h"
#include "include/shaiya/include/NetworkHelper.h"
using namespace shaiya;

void ItemHelper::SetCraftStrength(CItem* item, uint value)
{
    if (value > 99)
        value = 99;

    auto str = std::to_string(value);
    if (value < 10)
        str.insert(str.begin(), 1, '0');

    item->craftStrength = value;
    item->craftName[0] = str[0];
    item->craftName[1] = str[1];
}

void ItemHelper::SetCraftDexterity(CItem* item, uint value)
{
    if (value > 99)
        value = 99;

    auto str = std::to_string(value);
    if (value < 10)
        str.insert(str.begin(), 1, '0');

    item->craftDexterity = value;
    item->craftName[2] = str[0];
    item->craftName[3] = str[1];
}

void ItemHelper::SetCraftReaction(CItem* item, uint value)
{
    if (value > 99)
        value = 99;

    auto str = std::to_string(value);
    if (value < 10)
        str.insert(str.begin(), 1, '0');

    item->craftReaction = value;
    item->craftName[4] = str[0];
    item->craftName[5] = str[1];
}

void ItemHelper::SetCraftIntelligence(CItem* item, uint value)
{
    if (value > 99)
        value = 99;

    auto str = std::to_string(value);
    if (value < 10)
        str.insert(str.begin(), 1, '0');

    item->craftIntelligence = value;
    item->craftName[6] = str[0];
    item->craftName[7] = str[1];
}

void ItemHelper::SetCraftWisdom(CItem* item, uint value)
{
    if (value > 99)
        value = 99;

    auto str = std::to_string(value);
    if (value < 10)
        str.insert(str.begin(), 1, '0');

    item->craftWisdom = value;
    item->craftName[8] = str[0];
    item->craftName[9] = str[1];
}

void ItemHelper::SetCraftLuck(CItem* item, uint value)
{
    if (value > 99)
        value = 99;

    auto str = std::to_string(value);
    if (value < 10)
        str.insert(str.begin(), 1, '0');

    item->craftLuck = value;
    item->craftName[10] = str[0];
    item->craftName[11] = str[1];
}

void ItemHelper::SetCraftHealth(CItem* item, uint value)
{
    if (value > 99)
        value = 99;

    auto str = std::to_string(value);
    if (value < 10)
        str.insert(str.begin(), 1, '0');

    item->craftHealth = value;
    item->craftName[12] = str[0];
    item->craftName[13] = str[1];
}

void ItemHelper::SetCraftMana(CItem* item, uint value)
{
    if (value > 99)
        value = 99;

    auto str = std::to_string(value);
    if (value < 10)
        str.insert(str.begin(), 1, '0');

    item->craftMana = value;
    item->craftName[14] = str[0];
    item->craftName[15] = str[1];
}

void ItemHelper::SetCraftStamina(CItem* item, uint value)
{
    if (value > 99)
        value = 99;

    auto str = std::to_string(value);
    if (value < 10)
        str.insert(str.begin(), 1, '0');

    item->craftStamina = value;
    item->craftName[16] = str[0];
    item->craftName[17] = str[1];
}

void ItemHelper::CopyCraftExpansion(CItem* source, CItem* target)
{
    target->craftName = source->craftName;
    target->craftStrength = source->craftStrength;
    target->craftDexterity = source->craftDexterity;
    target->craftReaction = source->craftReaction;
    target->craftIntelligence = source->craftIntelligence;
    target->craftWisdom = source->craftWisdom;
    target->craftLuck = source->craftLuck;
    target->craftHealth = source->craftHealth;
    target->craftMana = source->craftMana;
    target->craftStamina = source->craftStamina;
    target->craftAttackPower = source->craftAttackPower;
    target->craftAbsorption = source->craftAbsorption;
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

void ItemHelper::SendDBAgentCraftName(CUser* user, CItem* item, uint bag, uint slot)
{
    DBAgentItemCraftUpdateIncoming outgoing{};
    outgoing.billingId = user->billingId;
    outgoing.bag = bag;
    outgoing.slot = slot;
    outgoing.craftName = item->craftName;
    NetworkHelper::SendDBAgent(&outgoing, sizeof(DBAgentItemCraftUpdateIncoming));
}

void ItemHelper::SendDBAgentGems(CUser* user, CItem* item, uint bag, uint slot)
{
    DBAgentItemGemUpdateIncoming outgoing{};
    outgoing.billingId = user->billingId;
    outgoing.bag = bag;
    outgoing.slot = slot;
    outgoing.gems = item->gems;
    outgoing.money = user->money;
    NetworkHelper::SendDBAgent(&outgoing, sizeof(DBAgentItemGemUpdateIncoming));
}

void ItemHelper::SendDBAgentCloakInfo(CUser* user, CItem* item, uint bag, uint slot)
{
    ItemHelper::SendDBAgentGems(user, item, bag, slot);
}