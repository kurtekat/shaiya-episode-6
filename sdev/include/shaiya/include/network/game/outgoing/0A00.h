#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/ItemTypes.h>

// CUser::PacketExchange

namespace shaiya
{
    #pragma pack(push, 1)
    struct ExchangeRequestOutgoing
    {
        UINT16 opcode{ 0xA01 };
        ULONG targetId;

        ExchangeRequestOutgoing() = default;

        ExchangeRequestOutgoing(ULONG targetId)
            : targetId(targetId)
        {
        }
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

    enum struct ExchangeReadyType : UINT8
    {
        Sender = 1,
        Target,
        Cancel
    };

    #pragma pack(push, 1)
    struct ExchangeReadyOutgoing
    {
        UINT16 opcode{ 0xA05 };
        ExchangeReadyType type;
        bool canceled;

        ExchangeReadyOutgoing() = default;

        ExchangeReadyOutgoing(ExchangeReadyType type, bool canceled)
            : type(type), canceled(canceled)
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
    struct ExchangeItemOutgoing_EP5
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
    struct ExchangeItemOutgoing_EP6_4
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

    enum struct ExchangeConfirmType : UINT8
    {
        Sender = 1,
        Target,
        Cancel
    };

    #pragma pack(push, 1)
    struct ExchangeConfirmOutgoing
    {
        UINT16 opcode{ 0xA0A };
        ExchangeConfirmType type;
        bool confirmed;

        ExchangeConfirmOutgoing() = default;

        ExchangeConfirmOutgoing(ExchangeConfirmType type, bool confirmed)
            : type(type), confirmed(confirmed)
        {
        }
    };
    #pragma pack(pop)
}
