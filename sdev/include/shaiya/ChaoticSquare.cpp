#include "ChaoticSquare.h"
using namespace shaiya;

ChaoticSquare* ChaoticSquare::Find(uint32_t itemId)
{
    auto first = g_chaoticSquares.begin();
    auto last = g_chaoticSquares.end();

    auto it = std::find_if(first, last, [=](const auto& square) {
        return square.itemId == itemId;
        });

    return it == last ? nullptr : &(*it);
}
