#pragma once
#include <include/shaiya/common.h>

// CUser::PacketPvP

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct PvPRequestResult : UINT8
    {
        Rejected,
        Accepted,
        CannotRequest,
        DidNotRespond
    };

    struct PvPRequestIncoming
    {
        UINT16 opcode{ 0x2401 };
        CharId senderId;
    };

    struct PvPRequestOutgoing
    {
        UINT16 opcode{ 0x2401 };
        CharId senderId;
        CharId targetId;
    };

    struct PvPRequestResultIncoming
    {
        UINT16 opcode{ 0x2402 };
        PvPRequestResult result;
    };

    struct PvPRequestResultOutgoing
    {
        UINT16 opcode{ 0x2402 };
        PvPRequestResult result;
        CharId targetId;
    };

    struct PvPExchangeItemOutgoing
    {
        UINT16 opcode{ 0x240D };
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
    #pragma pack(pop)
}
