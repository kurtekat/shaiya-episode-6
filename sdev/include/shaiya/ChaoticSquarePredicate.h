#pragma once
#include "ChaoticSquare.h"

namespace shaiya
{
    struct ChaoticSquareFindF
    {
        explicit ChaoticSquareFindF(ItemId itemId)
            : m_itemId(itemId)
        {
        }

        bool operator()(const ChaoticSquare& square) const
        {
            return square.itemId == m_itemId;
        }

    private:

        ItemId m_itemId;
    };

    struct ChaoticSquareRecipeFindF
    {
        explicit ChaoticSquareRecipeFindF(int id)
            : m_id(id)
        {
        }

        bool operator()(const ChaoticSquareRecipe& recipe) const
        {
            return recipe.id == m_id;
        }

    private:

        int m_id;
    };
}