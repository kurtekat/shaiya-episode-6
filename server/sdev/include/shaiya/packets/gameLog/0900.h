#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameLogChatIncoming
    {
        UINT16 opcode{ 0x901 };
        ULONG userId;
        ULONG charId;
        UINT16 mapId;
        ChatType chatType;
        UINT8 messageLength;
        ChatMessage message;
    };

    struct GameLogChatToIncoming
    {
        UINT16 opcode{ 0x902 };
        ULONG userId;
        ULONG charId;
        UINT16 mapId;
        ChatType chatType;
        CharName targetName;
        UINT8 messageLength;
        ChatMessage message;
    };
    #pragma pack(pop)
}
