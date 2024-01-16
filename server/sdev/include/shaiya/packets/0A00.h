#pragma once
#include <include/shaiya/common.h>

// CUser::PacketExchange

namespace shaiya
{
    enum struct ExchangeRequestResult : UINT8
    {
        Accepted,
        Rejected
    };

    enum struct ExchangeType : UINT8
    {
        Sender = 1,
        Target,
        CancelReady
    };

    #pragma pack(push, 1)
    struct ExchangeRequestIncoming
    {
        UINT16 opcode{ 0xA01 };
        CharId targetId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ExchangeRequestOutgoing
    {
        UINT16 opcode{ 0xA01 };
        CharId targetId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ExchangeRequestResultOutgoing
    {
        UINT16 opcode{ 0xA02 };
        ExchangeRequestResult result;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ExchangeIncoming
    {
        UINT16 opcode{ 0xA05 };
        bool canceled;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ExchangeOutgoing
    {
        UINT16 opcode{ 0xA05 };
        ExchangeType excType;
        bool canceled;
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
        #ifdef SHAIYA_EP6_ITEM_DURATION
        ULONG fromDate;
        ULONG toDate;
        #endif
        Gems gems;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ExchangeConfirmIncoming
    {
        UINT16 opcode{ 0xA0A };
        bool confirmed;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ExchangeConfirmOutgoing
    {
        UINT16 opcode{ 0xA0A };
        ExchangeType excType;
        bool confirmed;
    };
    #pragma pack(pop)
}
