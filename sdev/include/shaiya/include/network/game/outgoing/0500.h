#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/UserTypes.h>

// CUser::PacketPC

namespace shaiya
{
    #pragma pack(push, 1)
    struct UserMoveOutgoing
    {
        UINT16 opcode{ 0x501 };
        ULONG objectId;
        UINT8 motionValue;
        UINT16 direction;
        float x;
        float y;
        float z;
    };
    #pragma pack(pop)

    // Credit: Anna Melashkina (Imgeneus)
    enum struct UserAttackSuccessResult : UINT8
    {
        Normal,
        Critical,
        Miss,
        Failed,
        SuccessBuff,
        InsufficientRange,
        NotEnoughMPSP,
        WrongEquipment,
        PreviousSkillRequired,
        CooldownNotOver,
        CannotAttack,
        WrongTarget,
        TooFastAttack
    };

    #pragma pack(push, 1)
    struct UserAttackUserOutgoing
    {
        UINT16 opcode{ 0x502 };
        UserAttackSuccessResult result;
        ULONG objectId;
        ULONG targetId;
        UINT16 targetDmgHP;
        UINT16 targetDmgSP;
        UINT16 targetDmgMP;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserAttackMobOutgoing
    {
        UINT16 opcode{ 0x503 };
        UserAttackSuccessResult result;
        ULONG objectId;
        ULONG targetId;
        UINT16 targetDmgHP;
        UINT16 targetDmgSP;
        UINT16 targetDmgMP;
    };
    #pragma pack(pop)

    enum struct UserDeathKillerType : UINT8
    {
        User = 1,
        Mob,
        Npc
    };

    #pragma pack(push, 1)
    struct UserDeathOutgoing
    {
        UINT16 opcode{ 0x504 };
        ULONG objectId;
        UserDeathKillerType killerType;
        ULONG killerId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserRecoverAddOutgoing
    {
        UINT16 opcode{ 0x505 };
        ULONG objectId;
        int health;
        int mana;
        int stamina;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserMotionOutgoing
    {
        UINT16 opcode{ 0x506 };
        ULONG objectId;
        MotionType motionType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserEquipmentOutgoing
    {
        UINT16 opcode{ 0x507 };
        ULONG objectId;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 enchantStep;
        // omit if slot != 7
        CloakBadge cloakBadge;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserItemUseOutgoing
    {
        UINT16 opcode{ 0x50A };
        ULONG objectId;
        UINT8 bag;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct SkillApplyOutgoing
    {
        UINT16 opcode{ 0x50D };
        ULONG objectId;
        UINT16 skillId;
        UINT8 skillLv;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct SkillRemoveOutgoing
    {
        UINT16 opcode{ 0x50E };
        ULONG objectId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserSkillKeepOutgoing
    {
        UINT16 opcode{ 0x50F };
        ULONG objectId;
        UINT16 skillId;
        UINT8 skillLv;
        UINT16 health;
        UINT16 mana;
        UINT16 stamina;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserSkillUseOutgoing_EP5
    {
        UINT16 opcode{ 0x511 };
        UINT8 targetType;
        ULONG senderId;
        ULONG targetId;
        UINT16 skillId;
        UINT8 skillLv;
        UINT16 health;
        UINT16 stamina;
        UINT16 mana;
    };
    #pragma pack(pop)

    enum struct UserSkillUseStatus : UINT8
    {
        Triggered = 1,
        Stopped = 3
    };

    #pragma pack(push, 1)
    struct UserSkillUseOutgoing_EP6
    {
        UINT16 opcode{ 0x511 };
        UINT8 targetType;
        ULONG senderId;
        ULONG targetId;
        UINT16 skillId;
        UINT8 skillLv;
        UINT16 health;
        UINT16 stamina;
        UINT16 mana;
        UserSkillUseStatus status;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserShapeTypeOutgoing_EP5
    {
        UINT16 opcode{ 0x51D };
        ULONG objectId;
        ShapeType shapeType;

        UserShapeTypeOutgoing_EP5() = default;

        UserShapeTypeOutgoing_EP5(ULONG objectId, ShapeType shapeType)
            : objectId(objectId), shapeType(shapeType)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserShapeTypeOutgoing_EP6_4
    {
        UINT16 opcode{ 0x51D };
        ULONG objectId;
        ShapeType shapeType;
        UINT32 vehicleType;
        UINT32 vehicleTypeId;

        UserShapeTypeOutgoing_EP6_4() = default;

        UserShapeTypeOutgoing_EP6_4(ULONG objectId, ShapeType shapeType, UINT32 vehicleType, UINT32 vehicleTypeId)
            : objectId(objectId), shapeType(shapeType), vehicleType(vehicleType), vehicleTypeId(vehicleTypeId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserRecoverSetOutgoing
    {
        UINT16 opcode{ 0x521 };
        UINT32 health;
        UINT32 mana;
        UINT32 stamina;

        UserRecoverSetOutgoing() = default;

        UserRecoverSetOutgoing(UINT32 health, UINT32 mana, UINT32 stamina)
            : health(health), mana(mana), stamina(stamina)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserKillCountOutgoing
    {
        UINT16 opcode{ 0x522 };
        ULONG objectId;
        UINT32 kills;

        UserKillCountOutgoing() = default;

        UserKillCountOutgoing(ULONG objectId, UINT32 kills)
            : objectId(objectId), kills(kills)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserStatusOutgoing
    {
        UINT16 opcode{ 0x526 };
        UINT32 strength;
        UINT32 reaction;
        UINT32 intelligence;
        UINT32 wisdom;
        UINT32 dexterity;
        UINT32 luck;
        UINT32 minAttackPower;
        UINT32 maxAttackPower;
        UINT32 minMagicPower;
        UINT32 maxMagicPower;
        UINT32 defense;
        UINT32 resistance;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemRepairOutgoing
    {
        UINT16 opcode{ 0x554 };
        UINT8 bag;
        UINT8 slot;
        UINT32 money;

        ItemRepairOutgoing() = default;

        ItemRepairOutgoing(UINT8 bag, UINT8 slot, UINT32 money)
            : bag(bag), slot(slot), money(money)
        {
        }
    };
    #pragma pack(pop)
}
