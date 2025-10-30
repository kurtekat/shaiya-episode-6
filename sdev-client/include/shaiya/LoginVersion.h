#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    // notes: code page (see 0x40A550)
    // CP_ACP (see winnls.h)
    enum struct LoginVersion : int32_t
    {
        Korea = 1,     //
        China,         //
        Vietnam,       // 65001 (UTF-8)
        Japan,         // 932
        Taiwan,        // 950
        English,       // CP_ACP
        Germany,       // CP_ACP
        Singapore,     // 950
        HongKong,      // 950
        France,        // CP_ACP
        Russia,        // CP_ACP
        Turkey,        // 1254
        Brazil,        // CP_ACP
        LatinAmerica,  // CP_ACP
        Poland,        // 1250
        Italy,         // CP_ACP
        Philippines    // CP_ACP
    };
}
