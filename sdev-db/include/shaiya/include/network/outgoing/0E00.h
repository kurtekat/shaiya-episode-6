#pragma once
#include <shaiya/include/common.h>

// CUser::PacketUserPoint

namespace shaiya
{
    #pragma pack(push, 1)
    struct DBAgentPointReloadOutgoing
    {
        UINT16 opcode{ 0xE06 };
        ULONG userId;
        UINT32 points;

        DBAgentPointReloadOutgoing() = default;

        DBAgentPointReloadOutgoing(ULONG userId, UINT32 points)
            : userId(userId), points(points)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentPointAddOutgoing
    {
        UINT16 opcode{ 0xE08 };
        ULONG userId;
        UINT32 addPoints;

        DBAgentPointAddOutgoing() = default;

        DBAgentPointAddOutgoing(ULONG userId, UINT32 addPoints)
            : userId(userId), addPoints(addPoints)
        {
        }
    };
    #pragma pack(pop)
}
