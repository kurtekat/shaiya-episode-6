#pragma once
#include <shaiya/include/common.h>

// CUser::PacketUserDBChar

namespace shaiya
{
    enum struct ZoneEnterItemType : UINT8
    {
        UserDrop = 1,
        MobDrop
    };

    #pragma pack(push, 1)
    struct ZoneEnterItemOutgoing
    {
        UINT16 opcode{ 0x401 };
        ULONG objectId;
        ZoneEnterItemType kind;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        float x;
        float y;
        float z;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ZoneLeaveItemOutgoing
    {
        UINT16 opcode{ 0x402 };
        ULONG objectId;
    };
    #pragma pack(pop)
}
