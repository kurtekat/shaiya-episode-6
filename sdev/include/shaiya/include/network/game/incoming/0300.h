#pragma once
#include <shaiya/include/common.h>

// CUser::PacketGetInfo

namespace shaiya
{
    #pragma pack(push, 1)
    struct GetInfoTargetUserIncoming
    {
        UINT16 opcode{ 0x302 };
        ULONG targetId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GetInfoTargetMobIncoming
    {
        UINT16 opcode{ 0x305 };
        ULONG targetId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GetInfoInspectIncoming
    {
        UINT16 opcode{ 0x307 };
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GetInfoTargetNpcIncoming
    {
        UINT16 opcode{ 0x30A };
    };
    #pragma pack(pop)
}
