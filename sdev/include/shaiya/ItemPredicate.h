#pragma once
#include <shaiya/include/common/ItemEffect.h>
#include "CItem.h"
#include "ItemInfo.h"

namespace shaiya
{
    struct ItemMinCountF
    {
        ItemMinCountF(int type, int typeId, int count)
            : m_type(type), m_typeId(typeId), m_count(count)
        {
        }

        bool operator()(const CItem* item)
        {
            if (!item)
                return false;

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
            if (!item)
                return false;

            return item->type == m_type 
                && item->typeId == m_typeId;
        }

    private:

        int m_type;
        int m_typeId;
    };

    struct ItemEffectEqualToF
    {
        explicit ItemEffectEqualToF(ItemEffect effect)
            : m_effect(effect)
        {
        }

        bool operator()(const CItem* item)
        {
            if (!item)
                return false;

            return item->info->effect == m_effect;
        }

    private:

        ItemEffect m_effect;
    };

    struct ItemSetEqualToF
    {
        explicit ItemSetEqualToF(uint16_t id)
            : m_id(id)
        {
        }

        bool operator()(const CItem* item)
        {
            if (!item)
                return false;

            return item->info->drop == m_id;
        }

    private:

        uint16_t m_id;
    };
}
