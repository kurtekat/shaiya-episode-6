#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    enum struct GameAdminCmdBSetStatusType : uint8_t
    {
        Grow,
        Level,
        Money,
        StatusPoints,
        SkillPoints,
        Str,
        Dex,
        Rec,
        Int,
        Luc,
        Wis,
        Hg,
        Vg,
        Cg,
        Og,
        Ig,
        Exp,
        Kills,
        Deaths
    };

    #pragma pack(push, 1)
    struct GameAdminCmdBSetStatusOutgoing
    {
        uint16_t opcode{ 0xF701 };
        GameAdminCmdBSetStatusType type;
        uint32_t value;
    };
    #pragma pack(pop)
}
