#pragma once
#include <shaiya/include/common.h>

// CUser::PacketGetInfo

namespace shaiya
{
    #pragma pack(push, 1)
    struct GetInfoTargetIncoming
    {
        UINT16 opcode{ 0x302 };
        ULONG targetId;

        GetInfoTargetIncoming() = default;

        GetInfoTargetIncoming(ULONG targetId)
            : targetId(targetId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GetInfoInspectIncoming
    {
        UINT16 opcode{ 0x307 };
        ULONG charId;

        GetInfoInspectIncoming() = default;

        GetInfoInspectIncoming(ULONG charId)
            : charId(charId)
        {
        }
    };
    #pragma pack(pop)
}
