#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/user/MotionType.h>

// CUser::PacketPC

namespace shaiya
{
    enum struct UserRebirthType : UINT8
    {
        NearestTown = 2,
        LeaderResurrect,
        KillSoulByItem,
        KillSoulByItemNoMove
    };

    #pragma pack(push, 1)
    struct UserMoveIncoming
    {
        UINT16 opcode{ 0x501 };
        UINT8 motionValue;
        UINT16 direction;
        float x;
        float y;
        float z;

        UserMoveIncoming() = default;

        UserMoveIncoming(UINT8 motionValue, UINT16 direction, float x, float y, float z)
            : motionValue(motionValue), direction(direction), x(x), y(y), z(z)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserAttackUserIncoming
    {
        UINT16 opcode{ 0x502 };
        ULONG targetId;

        UserAttackUserIncoming() = default;

        UserAttackUserIncoming(ULONG targetId)
            : targetId(targetId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserAttackMobIncoming
    {
        UINT16 opcode{ 0x503 };
        ULONG targetId;

        UserAttackMobIncoming() = default;

        UserAttackMobIncoming(ULONG targetId)
            : targetId(targetId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserMotionIncoming
    {
        UINT16 opcode{ 0x506 };
        MotionType8 motionType;

        UserMotionIncoming() = default;

        UserMotionIncoming(MotionType8 motionType)
            : motionType(motionType)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserRebirthIncoming
    {
        UINT16 opcode{ 0x553 };
        UserRebirthType rebirthType;

        UserRebirthIncoming() = default;

        UserRebirthIncoming(UserRebirthType rebirthType)
            : rebirthType(rebirthType)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemRepairIncoming
    {
        UINT16 opcode{ 0x554 };
        UINT8 bag;
        UINT8 slot;
        ULONG npcId;

        ItemRepairIncoming() = default;

        ItemRepairIncoming(UINT8 bag, UINT8 slot, ULONG npcId)
            : bag(bag), slot(slot), npcId(npcId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemTownScrollIncoming
    {
        UINT16 opcode{ 0x55A };
        UINT8 bag;
        UINT8 slot;
        UINT8 gateIndex;

        ItemTownScrollIncoming() = default;

        ItemTownScrollIncoming(UINT8 bag, UINT8 slot, UINT8 gateIndex)
            : bag(bag), slot(slot), gateIndex(gateIndex)
        {
        }
    };
    #pragma pack(pop)
}
