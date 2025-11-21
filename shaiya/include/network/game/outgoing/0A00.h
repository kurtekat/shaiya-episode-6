#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Gems.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_EXC_REQUEST
    struct GameExchangeRequestOutgoing
    {
        uint16_t opcode{ 0xA01 };
        uint32_t targetId;
    };
    #pragma pack(pop)

    enum struct GameExchangeAnswerResult : uint8_t
    {
        Accepted,
        Rejected
    };

    #pragma pack(push, 1)
    // TP_EXC_ANSWER
    struct GameExchangeAnswerOutgoing
    {
        uint16_t opcode{ 0xA02 };
        GameExchangeAnswerResult result;
    };
    #pragma pack(pop)

    enum struct GameExchangeReadyType : uint8_t
    {
        Sender = 1,
        Target,
        Cancel
    };

    #pragma pack(push, 1)
    // TP_EXC_READY
    struct GameExchangeReadyOutgoing
    {
        uint16_t opcode{ 0xA05 };
        GameExchangeReadyType type;
        bool canceled;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_EXC_ADD
    struct GameExchangeAddOutgoing
    {
        uint16_t opcode{ 0xA06 };
        uint8_t bag;
        uint8_t slot;
        uint8_t count;
        uint8_t destSlot;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_EXC_ADD_DEST
    struct GameExchangeAddDestOutgoing_EP5
    {
        uint16_t opcode{ 0xA09 };
        uint8_t destSlot;
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
        uint16_t quality;
        Gems gems;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_EXC_ADD_DEST
    struct GameExchangeAddDestOutgoing_EP6_4
    {
        uint16_t opcode{ 0xA09 };
        uint8_t destSlot;
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
        uint16_t quality;
        time32_t fromDate;
        time32_t toDate;
        Gems gems;
        CraftName craftName;
    };
    #pragma pack(pop)

    enum struct GameExchangeConfirmType : uint8_t
    {
        Sender = 1,
        Target,
        Cancel
    };

    #pragma pack(push, 1)
    struct GameExchangeConfirmOutgoing
    {
        uint16_t opcode{ 0xA0A };
        GameExchangeConfirmType type;
        bool confirmed;
    };
    #pragma pack(pop)
}
