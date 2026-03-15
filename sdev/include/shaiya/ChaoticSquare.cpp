#include "ChaoticSquare.h"
using namespace shaiya;

ChaoticSquare* ChaoticSquare::Find(ItemId itemId)
{
    auto first = g_chaoticSquares.begin();
    auto last = g_chaoticSquares.end();

    auto it = std::find_if(first, last, [=](const auto& square) {
        return square.itemId == itemId;
        });

    return it == last ? nullptr : &(*it);
}

ChaoticSquareRecipe* ChaoticSquare::FindRecipe(int id)
{
    auto first = g_chaoticSquareRecipes.begin();
    auto last = g_chaoticSquareRecipes.end();

    auto it = std::find_if(first, last, [=](const auto& recipe) {
        return recipe.id == id;
        });

    return it == last ? nullptr : &(*it);
}
