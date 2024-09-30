#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/MotionType.h>
#include <shaiya/include/common/ShapeType.h>

// CUser::PacketPC

namespace shaiya
{
    enum struct SkillUseStatusType : UINT8
    {
        Triggered = 1,
        Stopped = 3
    };

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

    enum struct UserDeathKillerType : UINT8
    {
        User = 1,
        Mob,
        Npc
    };

    #pragma pack(push, 1)
    struct UserMoveOutgoing
    {
        UINT16 opcode{ 0x501 };
        ULONG charId;
        UINT8 motionValue;
        UINT16 direction;
        float x;
        float y;
        float z;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserAttackUserOutgoing
    {
        UINT16 opcode{ 0x502 };
        UserAttackSuccessResult result;
        ULONG charId;
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
        ULONG charId;
        ULONG targetId;
        UINT16 targetDmgHP;
        UINT16 targetDmgSP;
        UINT16 targetDmgMP;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserDeathOutgoing
    {
        UINT16 opcode{ 0x504 };
        ULONG charId;
        UserDeathKillerType killerType;
        ULONG killerId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct RecoverAddOutgoing
    {
        UINT16 opcode{ 0x505 };
        ULONG charId;
        int health;
        int mana;
        int stamina;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserMotionOutgoing
    {
        UINT16 opcode{ 0x506 };
        ULONG charId;
        MotionType motionType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserEquipmentOutgoing
    {
        UINT16 opcode{ 0x507 };
        ULONG charId;
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT8 enchantStep;
        // omit if slot != 7
        CloakBadge cloakBadge;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemUseOutgoing
    {
        UINT16 opcode{ 0x50A };
        ULONG charId;
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
        // CSkill->id
        ULONG id;
        UINT16 skillId;
        UINT8 skillLv;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct SkillRemoveOutgoing
    {
        UINT16 opcode{ 0x50E };
        // CSkill->id
        ULONG id;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct SkillKeepOutgoing
    {
        UINT16 opcode{ 0x50F };
        ULONG charId;
        UINT16 skillId;
        UINT8 skillLv;
        UINT16 health;
        UINT16 mana;
        UINT16 stamina;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct SkillUseOutgoing
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

    #pragma pack(push, 1)
    struct SkillUseOutgoing2
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
        SkillUseStatusType statusType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserShapeTypeOutgoing
    {
        UINT16 opcode{ 0x51D };
        ULONG charId;
        ShapeType shapeType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserShapeTypeOutgoing2
    {
        UINT16 opcode{ 0x51D };
        ULONG charId;
        ShapeType shapeType;
        UINT32 vehicleType;
        UINT32 vehicleTypeId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct RecoverSetOutgoing
    {
        UINT16 opcode{ 0x521 };
        UINT32 health;
        UINT32 mana;
        UINT32 stamina;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserKillCountOutgoing
    {
        UINT16 opcode{ 0x522 };
        ULONG charId;
        UINT32 kills;
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
    };
    #pragma pack(pop)
}
