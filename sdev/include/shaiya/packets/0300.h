#pragma once
#include <include/shaiya/common.h>

// CUser::PacketGetInfo

namespace shaiya
{
    #pragma pack(push, 1)
    struct GetInfoTargetIncoming
    {
        UINT16 opcode{ 0x302 };
        CharId targetId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GetInfoTargetOutgoing
    {
        UINT16 opcode{ 0x302 };
        CharId targetId;
        UINT32 maxHealth;
        UINT32 health;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct Equipment0303
    {
        UINT8 type;
        UINT8 typeId;
        UINT8 enchantStep;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GetInfoUserShapeOutgoing
    {
        UINT16 opcode{ 0x303 };
        ULONG charId;
        bool dead;
        bool sitting;
        Country country;
        Family family;
        UINT8 hair;
        UINT8 face;
        UINT8 size;
        Job job;
        Sex sex;
        UINT8 partyType;
        Grow grow;
        UINT32 kills;
#ifdef SHAIYA_EP6_4_PT
        Array<Equipment0303, 17> equipment;
#else
        Array<Equipment0303, 8> equipment;
#endif
        CharName charName;
        CloakBadge cloakBadge;
        GuildName guildName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct Item0307
    {
        UINT8 slot;
        UINT8 type;
        UINT8 typeId;
        UINT16 quality;
        Gems gems;
        CraftName craftName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GetInfoInspectIncoming
    {
        UINT16 opcode{ 0x307 };
        ULONG charId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GetInfoInspectOutgoing
    {
        UINT16 opcode{ 0x307 };
        UINT8 itemCount;
#ifdef SHAIYA_EP6_4_PT
        Array<Item0307, 17> itemList;
#else
        Array<Item0307, 12> itemList;
#endif
    };
    #pragma pack(pop)
}
