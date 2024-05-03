#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    // notes: system message

    enum struct RewardItemClaimResult : UINT8
    {
        Success,
        Failure  // 7188
    };

    enum struct RewardItemMedalResult : UINT8
    {
        Bronze, // 7189
        Silver, // 7190
        Gold    // 7191
    };

    #pragma pack(push, 1)
    struct RewardItemClaimResultOutgoing
    {
        UINT16 opcode{ 0x1F01 };
        RewardItemClaimResult result;
        UINT32 messageNumber;
        // optional
        UINT32 value; // <v>

        RewardItemClaimResultOutgoing() = default;

        RewardItemClaimResultOutgoing(RewardItemClaimResult result, UINT32 messageNumber, UINT32 value)
            : result(result), messageNumber(messageNumber), value(value)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct RewardItemMedalOutgoing
    {
        UINT16 opcode{ 0x1F02 };
        RewardItemMedalResult result;
        UINT8 unknown1;
        UINT8 unknown2;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct Item1F03
    {
        UINT32 minutes;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct RewardItemListOutgoing
    {
        UINT16 opcode{ 0x1F03 };
        UINT32 itemCount;
        Array<Item1F03, 20> itemList;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct RewardItemClaimOutgoing
    {
        UINT16 opcode{ 0x1F04 };
        UINT32 unknown{ 0 };

        RewardItemClaimOutgoing() = default;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct RewardItemEventProgressOutgoing
    {
        UINT16 opcode{ 0x1F05 };
        UINT32 cursorIndex;
        BOOL completedEvent;

        RewardItemEventProgressOutgoing() = default;

        RewardItemEventProgressOutgoing(UINT32 cursorIndex, BOOL completedEvent)
            : cursorIndex(cursorIndex), completedEvent(completedEvent)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct RewardItemEventEndedOutgoing
    {
        // 2044
        UINT16 opcode{ 0x1F06 };

        RewardItemEventEndedOutgoing() = default;
    };
    #pragma pack(pop)
}
