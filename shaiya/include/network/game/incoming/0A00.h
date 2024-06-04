#pragma once
#include <shaiya/include/common.h>

// CUser::PacketExchange

namespace shaiya
{
    #pragma pack(push, 1)
    struct ExchangeRequestIncoming
    {
        UINT16 opcode{ 0xA01 };
        ULONG targetId;

        ExchangeRequestIncoming() = default;

        ExchangeRequestIncoming(ULONG targetId)
            : targetId(targetId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ExchangeIncoming
    {
        UINT16 opcode{ 0xA05 };
        bool canceled;

        ExchangeIncoming() = default;

        ExchangeIncoming(bool canceled)
            : canceled(canceled)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ExchangeConfirmIncoming
    {
        UINT16 opcode{ 0xA0A };
        bool confirmed;

        ExchangeConfirmIncoming() = default;

        ExchangeConfirmIncoming(bool confirmed)
            : confirmed(confirmed)
        {
        }
    };
    #pragma pack(pop)
}
