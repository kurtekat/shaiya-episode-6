#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>

// CUser::PacketExchange

namespace shaiya
{
    #pragma pack(push, 1)
    struct ExchangeRequestOutgoing
    {
        UINT16 opcode{ 0xA01 };
        ULONG targetId;
    };
    #pragma pack(pop)

    enum struct ExchangeRequestResult : UINT8
    {
        Accepted,
        Rejected
    };

    #pragma pack(push, 1)
    struct ExchangeRequestResultOutgoing
    {
        UINT16 opcode{ 0xA02 };
        ExchangeRequestResult result;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ExchangeReadyOutgoing
    {
        UINT16 opcode{ 0xA05 };
        enum struct 
            Kind : UINT8 {
            Sender = 1,
            Target,
            Cancel
        } kind;
        bool canceled;

        ExchangeReadyOutgoing() = default;

        ExchangeReadyOutgoing(Kind kind, bool canceled)
            : kind(kind), canceled(canceled)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ExchangeItemAddOutgoing
    {
        UINT16 opcode{ 0xA06 };
        UINT8 srcBag;
        UINT8 srcSlot;
        UINT8 count;
        UINT8 destSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ExchangeItemOutgoing
    {
        UINT16 opcode{ 0xA09 };
        UINT8 destSlot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        UINT16 quality;
        Gems gems;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ExchangeItemOutgoing2
    {
        UINT16 opcode{ 0xA09 };
        UINT8 destSlot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        UINT16 quality;
        ULONG fromDate;
        ULONG toDate;
        Gems gems;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ExchangeConfirmOutgoing
    {
        UINT16 opcode{ 0xA0A };
        enum struct 
            Kind : UINT8 {
            Sender = 1,
            Target,
            Cancel
        } kind;
        bool confirmed;

        ExchangeConfirmOutgoing() = default;

        ExchangeConfirmOutgoing(Kind kind, bool confirmed)
            : kind(kind), confirmed(confirmed)
        {
        }
    };
    #pragma pack(pop)
}
