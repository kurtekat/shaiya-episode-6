#include <string>
#include "include/shaiya/include/CItem.h"
#include "include/shaiya/include/ItemHelper.h"
using namespace shaiya;

void ItemHelper::SetCraftStrength(CItem* item, UINT16 value)
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

void ItemHelper::SetCraftDexterity(CItem* item, UINT16 value)
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

void ItemHelper::SetCraftReaction(CItem* item, UINT16 value)
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

void ItemHelper::SetCraftIntelligence(CItem* item, UINT16 value)
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

void ItemHelper::SetCraftWisdom(CItem* item, UINT16 value)
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

void ItemHelper::SetCraftLuck(CItem* item, UINT16 value)
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

void ItemHelper::SetCraftHealth(CItem* item, UINT16 value)
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

void ItemHelper::SetCraftMana(CItem* item, UINT16 value)
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

void ItemHelper::SetCraftStamina(CItem* item, UINT16 value)
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

void ItemHelper::CopyCraftName(CItem* from, CItem* to)
{
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

void ItemHelper::InitCraftName(CItem* item)
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
