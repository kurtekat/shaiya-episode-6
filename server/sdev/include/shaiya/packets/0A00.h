#pragma once
#include <include/shaiya/common.h>

// CUser::PacketExchange

namespace shaiya
{
    #pragma pack(push, 1)
    struct ExchangeIncoming
    {
        UINT16 opcode{ 0xA05 };
        UINT8 state;
    };

    struct ExchangeOutgoing
    {
        UINT16 opcode{ 0xA05 };
        UINT8 state1;
        UINT8 state2;
    };

    struct ExchangeItemAddOutgoing
    {
        UINT16 opcode{ 0xA06 };
        UINT8 srcBag;
        UINT8 srcSlot;
        UINT8 count;
        UINT8 destSlot;
    };

    struct ExchangeItemOutgoing
    {
        UINT16 opcode{ 0xA09 };
        UINT8 destSlot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
        UINT16 quality;
        #ifdef WITH_ITEM_DURATION
        ULONG fromDate;
        ULONG toDate;
        #endif
        Gems gems;
        CraftName craftName;
    };

    struct ExchangeConfirmIncoming
    {
        UINT16 opcode{ 0xA0A };
        UINT8 state;
    };

    struct ExchangeConfirmOutgoing
    {
        UINT16 opcode{ 0xA0A };
        UINT8 state1;
        UINT8 state2;
    };
    #pragma pack(pop)
}
