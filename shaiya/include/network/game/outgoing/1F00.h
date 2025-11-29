#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/network/game/RewardItemUnit.h>

namespace shaiya
{
    // notes: system message

    enum struct GameRewardItemGetResult : uint8_t
    {
        Success,
        Failure  // 7188
    };

    #pragma pack(push, 1)
    struct GameRewardItemGetResultOutgoing
    {
        uint16_t opcode{ 0x1F01 };
        GameRewardItemGetResult result;
        uint32_t messageNumber;
        // optional
        uint32_t value; // <v>
    };
    #pragma pack(pop)

    enum struct GameRewardItemMedalResult : uint8_t
    {
        Bronze, // 7189
        Silver, // 7190
        Gold    // 7191
    };

    #pragma pack(push, 1)
    struct GameRewardItemMedalOutgoing
    {
        uint16_t opcode{ 0x1F02 };
        GameRewardItemMedalResult result;
        uint8_t unknown1;
        uint8_t unknown2;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameRewardItemListOutgoing
    {
        uint16_t opcode{ 0x1F03 };
        uint32_t itemCount;
        Array<RewardItemUnit, 20> itemList;

        constexpr static int baseLength = 6;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameRewardItemGetOutgoing
    {
        uint16_t opcode{ 0x1F04 };
        uint32_t unknown{ 0 };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameRewardItemListIndexOutgoing
    {
        uint16_t opcode{ 0x1F05 };
        uint32_t index;
        uint32_t unknown{ 0 };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameRewardItemEventEndedOutgoing
    {
        // 2044
        uint16_t opcode{ 0x1F06 };
    };
    #pragma pack(pop)
}
