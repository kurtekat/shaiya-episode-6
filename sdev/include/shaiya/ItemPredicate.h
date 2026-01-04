#pragma once
#include <algorithm>
#include <ranges>
#include <shaiya/include/common/ItemEffect.h>
#include "ItemRemake.h"

namespace shaiya
{
    struct CItem;

    struct ItemMinCountF
    {
        ItemMinCountF(int type, int typeId, int count)
            : m_type(type), m_typeId(typeId), m_count(count)
        {
        }

        bool operator()(const CItem* item)
        {
            return item->type == m_type 
                && item->typeId == m_typeId 
                && item->count >= m_count;
        }

    private:

        int m_type;
        int m_typeId;
        int m_count;
    };

    struct ItemEqualToF
    {
        ItemEqualToF(int type, int typeId)
            : m_type(type), m_typeId(typeId)
        {
        }

        bool operator()(const CItem* item)
        {
            return item->type == m_type 
                && item->typeId == m_typeId;
        }

    private:

        int m_type;
        int m_typeId;
    };

    struct ItemEffectEqualToF
    {
        explicit ItemEffectEqualToF(ItemEffect itemEffect)
            : m_effect(itemEffect)
        {
        }

        bool operator()(const CItem* item)
        {
            return item->info->effect == m_effect;
        }

    private:

        ItemEffect m_effect;
    };

    struct ItemRemakeContainsF
    {
        ItemRemakeContainsF(uint32_t itemId1, uint32_t itemId2, uint32_t itemId3)
            : m_itemId1(itemId1)
            , m_itemId2(itemId2)
            , m_itemId3(itemId3)
        {
        }

        bool operator()(const ItemRemake& itemRemake)
        {
            return std::ranges::contains(itemRemake.items, m_itemId1)
                && std::ranges::contains(itemRemake.items, m_itemId2)
                && std::ranges::contains(itemRemake.items, m_itemId3);
        }

    private:

        uint32_t m_itemId1;
        uint32_t m_itemId2;
        uint32_t m_itemId3;
    };
}
