#pragma once
#include <shaiya/include/common.h>
#include "CExchange.h"

namespace shaiya
{
    struct CItem;

    #pragma pack(push, 1)
    struct CExchangePvP : CExchange
    {
        uint32_t money;          //0x1610
        Array<CItem*, 8> items;  //0x1614
        // 0x4C
    };
    #pragma pack(pop)

    static_assert(sizeof(CExchangePvP) == 0x4C);
}
