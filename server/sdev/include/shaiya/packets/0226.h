#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct UserAppearanceChangeIncoming
    {
        UINT16 opcode{ 0x226 };
        UINT8 bag;
        UINT8 slot;
        UINT8 hair;
        UINT8 face;
        UINT8 size;
        Sex sex;
    };

    struct UserAppearanceChangeOutgoing
    {
        UINT16 opcode{ 0x226 };
        ULONG charId;
        UINT8 hair;
        UINT8 face;
        UINT8 size;
        Sex sex;
    };
    #pragma pack(pop)
}
