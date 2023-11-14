#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct DBStatusGroup
    {
        // hg
        Honor = 1,
        // vg, cg, og, ig
        Other = 2,
    };

    struct SaveStatusGroupIncoming
    {
        UINT16 opcode{ 0x605 };
        UserId userId;
        DBStatusGroup group;
        UINT16 value;
    };
    #pragma pack(pop)
}
