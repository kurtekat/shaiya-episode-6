#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct GameGetInfoUserHealthIncoming
    {
        uint16_t opcode{ 0x302 };
        uint32_t targetId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameGetInfoMobHealthIncoming
    {
        uint16_t opcode{ 0x305 };
        uint32_t targetId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameGetInfoUserItemsIncoming
    {
        uint16_t opcode{ 0x307 };
        uint32_t targetId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GetInfoNpcIncoming
    {
        uint16_t opcode{ 0x30A };
    };
    #pragma pack(pop)
}
