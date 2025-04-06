#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/UserTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TPC_PC_MOVE
    struct GameCharMoveIncoming
    {
        uint16_t opcode{ 0x501 };
        uint8_t motion;
        uint16_t direction;
        float x;
        float y;
        float z;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameCharAttackUserIncoming
    {
        uint16_t opcode{ 0x502 };
        uint32_t targetId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameCharAttackMobIncoming
    {
        uint16_t opcode{ 0x503 };
        uint32_t targetId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameCharMotionIncoming
    {
        uint16_t opcode{ 0x506 };
        MotionType motionType;
    };
    #pragma pack(pop)

    enum struct GameCharRebirthType : uint8_t
    {
        NearestTown = 2,
        LeaderResurrect,
        KillSoulByItem,
        KillSoulByItemNoMove
    };

    #pragma pack(push, 1)
    struct GameCharRebirthIncoming
    {
        uint16_t opcode{ 0x553 };
        GameCharRebirthType rebirthType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_ITEM_REPAIR
    struct GameItemRepairIncoming
    {
        uint16_t opcode{ 0x554 };
        uint8_t bag;
        uint8_t slot;
        uint32_t npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameTownMoveScrollIncoming
    {
        uint16_t opcode{ 0x55A };
        uint8_t bag;
        uint8_t slot;
        uint8_t gateIndex;
    };
    #pragma pack(pop)
}
