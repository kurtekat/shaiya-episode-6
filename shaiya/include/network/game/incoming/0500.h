#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/user/MotionType.h>

// CUser::PacketPC

namespace shaiya
{
    #pragma pack(push, 1)
    struct UserMoveIncoming
    {
        UINT16 opcode{ 0x501 };
        // CUser->144D
        UINT8 unknown;
        UINT16 direction;
        float x;
        float y;
        float z;

        UserMoveIncoming() = default;

        UserMoveIncoming(UINT8 unknown, UINT16 direction, float x, float y, float z)
            : unknown(unknown), direction(direction), x(x), y(y), z(z)
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
