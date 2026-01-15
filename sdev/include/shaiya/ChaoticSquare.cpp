#include "ChaoticSquare.h"
#include "ChaoticSquarePredicate.h"
using namespace shaiya;

ChaoticSquare* ChaoticSquare::Find(ItemId itemId)
{
    auto first = g_chaoticSquares.begin();
    auto last = g_chaoticSquares.end();
    auto it = std::find_if(first, last, ChaoticSquareFindF(itemId));
    return it == last ? nullptr : &(*it);
}

ChaoticSquareRecipe* ChaoticSquare::FindRecipe(int id)
{
    auto first = g_chaoticSquareRecipes.begin();
    auto last = g_chaoticSquareRecipes.end();
    auto it = std::find_if(first, last, ChaoticSquareRecipeFindF(id));
    return it == last ? nullptr : &(*it);
}
