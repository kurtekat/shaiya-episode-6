#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/MotionType.h>

// CUser::PacketPC

namespace shaiya
{
    #pragma pack(push, 1)
    struct UserMoveIncoming
    {
        UINT16 opcode{ 0x501 };
        UINT8 motionValue;
        UINT16 direction;
        float x;
        float y;
        float z;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserAttackUserIncoming
    {
        UINT16 opcode{ 0x502 };
        ULONG targetId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserAttackMobIncoming
    {
        UINT16 opcode{ 0x503 };
        ULONG targetId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserMotionIncoming
    {
        UINT16 opcode{ 0x506 };
        MotionType motionType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserRebirthIncoming
    {
        UINT16 opcode{ 0x553 };
        enum struct 
            RebirthType : UINT8
        {
            NearestTown = 2,
            LeaderResurrect,
            KillSoulByItem,
            KillSoulByItemNoMove
        } rebirthType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemRepairIncoming
    {
        UINT16 opcode{ 0x554 };
        UINT8 bag;
        UINT8 slot;
        ULONG npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct TownMoveScrollIncoming
    {
        UINT16 opcode{ 0x55A };
        UINT8 bag;
        UINT8 slot;
        UINT8 gateIndex;
    };
    #pragma pack(pop)
}
