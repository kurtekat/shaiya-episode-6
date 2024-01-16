#pragma once
#include <include/shaiya/common.h>

// CUser::PacketPvP

namespace shaiya
{
    enum struct PvPRequestResult : UINT8
    {
        Rejected,
        Accepted,
        CannotRequest,
        DidNotRespond
    };

    #pragma pack(push, 1)
    struct PvPRequestIncoming
    {
        UINT16 opcode{ 0x2401 };
        CharId senderId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PvPRequestOutgoing
    {
        UINT16 opcode{ 0x2401 };
        CharId senderId;
        CharId targetId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PvPRequestResultIncoming
    {
        UINT16 opcode{ 0x2402 };
        PvPRequestResult result;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PvPRequestResultOutgoing
    {
        UINT16 opcode{ 0x2402 };
        PvPRequestResult result;
        CharId targetId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PvPExchangeItemOutgoing
    {
        UINT16 opcode{ 0x240D };
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
}
