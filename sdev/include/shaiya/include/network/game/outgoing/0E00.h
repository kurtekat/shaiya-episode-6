#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct NpcZoneEnterOutgoing
    {
        UINT16 opcode{ 0xE01 };
        ULONG objectId;
        UINT8 npcType;
        UINT16 npcTypeId;
        float x;
        float y;
        float z;
        UINT16 direction;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct NpcZoneLeaveOutgoing
    {
        UINT16 opcode{ 0xE02 };
        ULONG objectId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct NpcMoveOutgoing
    {
        UINT16 opcode{ 0xE03 };
        ULONG objectId;
        UINT8 motionValue;
        float x;
        float y;
        float z;
    };
    #pragma pack(pop)
}
