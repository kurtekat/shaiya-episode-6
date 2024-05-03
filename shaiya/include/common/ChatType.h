#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    enum struct ChatType : UINT8
    {
        Normal = 1,
        To,
        Guild,
        Party,
        Trade = 5,
        All = 5,
        Shout,
        Zone
    };
}
