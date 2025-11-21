#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Gems.h>
#include <shaiya/include/common/UserTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_PC_MOVE
    struct GameCharMoveOutgoing
    {
        uint16_t opcode{ 0x501 };
        uint32_t objectId;
        uint8_t motion;
        uint16_t direction;
        float x;
        float y;
        float z;
    };
    #pragma pack(pop)

    // Credit: Anna Melashkina (Imgeneus)
    enum struct GameCharAttackResult : uint8_t
    {
        Normal,
        Critical,
        Miss,
        Failed,
        SuccessBuff,
        TooFarAway,
        NotEnoughMPSP,
        WrongEquipment,
        PreviousSkillRequired,
        CooldownNotOver,
        CannotAttack,
        WrongTarget,
        TooFastAttack
    };

    #pragma pack(push, 1)
    // TP_PC_ATTACK
    struct GameCharAttackUserOutgoing
    {
        uint16_t opcode{ 0x502 };
        GameCharAttackResult result;
        uint32_t objectId;
        uint32_t targetId;
        uint16_t targetDmgHP;
        uint16_t targetDmgSP;
        uint16_t targetDmgMP;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_PC_ATTACK
    struct GameCharAttackMobOutgoing
    {
        uint16_t opcode{ 0x503 };
        GameCharAttackResult result;
        uint32_t objectId;
        uint32_t targetId;
        uint16_t targetDmgHP;
        uint16_t targetDmgSP;
        uint16_t targetDmgMP;
    };
    #pragma pack(pop)

    enum struct GameUserDeathKillerType : uint8_t
    {
        User = 1,
        Mob,
        Npc
    };

    #pragma pack(push, 1)
    // TP_DEATH
    struct GameUserDeathOutgoing
    {
        uint16_t opcode{ 0x504 };
        uint32_t objectId;
        GameUserDeathKillerType killerType;
        uint32_t killerId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_USER_RECOVER
    struct GameUserRecoverOutgoing
    {
        uint16_t opcode{ 0x505 };
        uint32_t objectId;
        int32_t health;
        int32_t mana;
        int32_t stamina;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_PC_MOTION
    struct GameCharMotionOutgoing
    {
        uint16_t opcode{ 0x506 };
        uint32_t objectId;
        MotionType motionType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_PC_EQUIPMENT
    struct GameCharEquipmentOutgoing
    {
        uint16_t opcode{ 0x507 };
        uint32_t objectId;
        uint8_t slot;
        uint8_t type;
        uint8_t typeId;
        uint8_t enchantStep;
        // Omit if slot != 7
        CloakInfo cloakInfo;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_PC_USEITEM
    struct GameCharItemUseOutgoing
    {
        uint16_t opcode{ 0x50A };
        uint32_t objectId;
        uint8_t bag;
        uint8_t slot;
        uint8_t type;
        uint8_t typeId;
        uint8_t count;
    };
    #pragma pack(pop)

    enum struct GameCharMaxEnergyType : uint8_t
    {
        HP, SP, MP
    };

    #pragma pack(push, 1)
    // TP_SET_MAX
    struct GameCharMaxEnergyOutgoing
    {
        uint16_t opcode{ 0x50B };
        uint32_t objectId;
        GameCharMaxEnergyType type;
        int32_t value;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_PC_SKILL_SET
    struct GameCharSkillSetOutgoing
    {
        uint16_t opcode{ 0x50D };
        uint32_t objectId;
        uint16_t skillId;
        uint8_t skillLv;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_PC_SKILL_REMOVE
    struct GameCharSkillRemoveOutgoing
    {
        uint16_t opcode{ 0x50E };
        uint32_t objectId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_SKILL_KEEP
    struct GameUserSkillKeepOutgoing
    {
        uint16_t opcode{ 0x50F };
        uint32_t objectId;
        uint16_t skillId;
        uint8_t skillLv;
        uint16_t health;
        uint16_t mana;
        uint16_t stamina;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_PC_SKILL_USE
    struct GameCharSkillUseOutgoing_EP5
    {
        uint16_t opcode{ 0x511 };
        uint8_t targetType;
        uint32_t senderId;
        uint32_t targetId;
        uint16_t skillId;
        uint8_t skillLv;
        uint16_t health;
        uint16_t stamina;
        uint16_t mana;
    };
    #pragma pack(pop)

    enum struct GameCharSkillUseStatusType : uint8_t
    {
        Triggered = 1,
        Stopped = 3
    };

    #pragma pack(push, 1)
    // TP_PC_SKILL_USE
    struct GameCharSkillUseOutgoing_EP6
    {
        uint16_t opcode{ 0x511 };
        uint8_t targetType;
        uint32_t senderId;
        uint32_t targetId;
        uint16_t skillId;
        uint8_t skillLv;
        uint16_t health;
        uint16_t stamina;
        uint16_t mana;
        GameCharSkillUseStatusType statusType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_PC_SHAPE
    struct GameCharShapeOutgoing_EP5
    {
        uint16_t opcode{ 0x51D };
        uint32_t objectId;
        ShapeType shapeType;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_PC_SHAPE
    struct GameCharShapeOutgoing_EP6_4
    {
        uint16_t opcode{ 0x51D };
        uint32_t objectId;
        ShapeType shapeType;
        uint32_t vehicleType;
        uint32_t vehicleTypeId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_USER_RECOVERSET
    struct GameUserRecoverSetOutgoing
    {
        uint16_t opcode{ 0x521 };
        int32_t health;
        int32_t mana;
        int32_t stamina;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_USER_KILLINFO
    struct GameUserKillInfoOutgoing
    {
        uint16_t opcode{ 0x522 };
        uint32_t objectId;
        uint32_t kills;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameUserStatusOutgoing
    {
        uint16_t opcode{ 0x526 };
        int32_t strength;
        int32_t reaction;
        int32_t intelligence;
        int32_t wisdom;
        int32_t dexterity;
        int32_t luck;
        int32_t minAttackPower;
        int32_t maxAttackPower;
        int32_t minMagicPower;
        int32_t maxMagicPower;
        int32_t defense;
        int32_t resistance;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TP_ITEM_REPAIR
    struct GameItemRepairOutgoing
    {
        uint16_t opcode{ 0x554 };
        uint8_t bag;
        uint8_t slot;
        uint32_t money;
    };
    #pragma pack(pop)
}
