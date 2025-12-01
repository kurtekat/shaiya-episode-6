#pragma once
#include <shaiya/include/common/ItemEffect.h>

namespace shaiya
{
    struct CItem;

    struct ItemCountGreaterEqualF
    {
        ItemCountGreaterEqualF(int type, int typeId, int count)
            : m_type(type), m_typeId(typeId), m_count(count)
        {
        }

        bool operator()(const CItem* item)
        {
            return item->type == m_type && item->typeId == m_typeId && item->count >= m_count;
        }

    private:

        int m_type;
        int m_typeId;
        int m_count;
    };

    struct ItemEffectEqualF
    {
        ItemEffectEqualF(ItemEffect itemEffect)
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
}
