#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Sex.h>

// CUser::PacketMainInterface

namespace shaiya
{
    #pragma pack(push, 1)
    struct ItemBagToBagIncoming
    {
        UINT16 opcode{ 0x204 };
        UINT8 srcBag;
        UINT8 srcSlot;
        UINT8 destBag;
        UINT8 destSlot;
        // warehouse
        ULONG npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemPickIncoming
    {
        UINT16 opcode{ 0x205 };
        ULONG objectId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemRemoveIncoming
    {
        UINT16 opcode{ 0x206 };
        UINT8 bag;
        UINT8 slot;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct UserStatusUpIncoming
    {
        UINT16 opcode{ 0x208 };
        UINT16 strength;
        UINT16 dexterity;
        UINT16 reaction;
        UINT16 intelligence;
        UINT16 wisdom;
        UINT16 luck;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct SkillGetIncoming
    {
        UINT16 opcode{ 0x209 };
        UINT16 skillId;
        UINT8 skillLv;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PortalEnableIncoming
    {
        UINT16 opcode{ 0x20A };
        UINT8 portalId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct NpcGateKeeperUseIncoming
    {
        UINT16 opcode{ 0x20C };
        ULONG npcId;
        UINT8 gateIndex;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct NpcVetRewardLevelIncoming
    {
        UINT16 opcode{ 0x218 };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct NpcVetKillRewardIncoming
    {
        UINT16 opcode{ 0x219 };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct NpcVetDeathRewardIncoming
    {
        UINT16 opcode{ 0x21A };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct AppearanceChangeIncoming
    {
        UINT16 opcode{ 0x226 };
        UINT8 bag;
        UINT8 slot;
        UINT8 hair;
        UINT8 face;
        UINT8 size;
        Sex sex;
    };
    #pragma pack(pop)
}
