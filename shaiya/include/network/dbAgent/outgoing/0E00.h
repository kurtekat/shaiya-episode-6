#pragma once
#include <shaiya/include/common.h>

// CUser::PacketUserPoint

namespace shaiya
{
    #pragma pack(push, 1)
    struct DBAgentReloadPointOutgoing
    {
        UINT16 opcode{ 0xE06 };
        ULONG userId;
        UINT32 points;

        DBAgentReloadPointOutgoing() = default;

        DBAgentReloadPointOutgoing(ULONG userId, UINT32 points)
            : userId(userId), points(points)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct DBAgentAddPointOutgoing
    {
        UINT16 opcode{ 0xE08 };
        ULONG userId;
        UINT32 addPoints;

        DBAgentAddPointOutgoing() = default;

        DBAgentAddPointOutgoing(ULONG userId, UINT32 addPoints)
            : userId(userId), addPoints(addPoints)
        {
        }
    };
    #pragma pack(pop)
}
