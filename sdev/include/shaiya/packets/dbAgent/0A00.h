#pragma once
#include <sdev/include/shaiya/common.h>

// CUser::PacketUserQuest

namespace shaiya
{
    #pragma pack(push, 1)
    struct UserQuestStartIncoming
    {
        UINT16 opcode{ 0xA01 };
        UserId userId;
        UINT16 questId;
        UINT16 delay;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserQuestEndIncoming
    {
        UINT16 opcode{ 0xA02 };
        UserId userId;
        UINT16 questId;
        UINT8 bySuccess;
    };
    #pragma pack(pop)
}
