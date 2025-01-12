#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/ItemTypes.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/PartyTypes.h>
#include <shaiya/include/common/Sex.h>
#include <shaiya/include/common/UserTypes.h>

// CUser::PacketGetInfo

namespace shaiya
{
    #pragma pack(push, 1)
    struct GetInfoTargetUserOutgoing
    {
        UINT16 opcode{ 0x302 };
        ULONG objectId;
        UINT32 maxHealth;
        UINT32 health;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 8 items (5.4, 6.0)
    struct GetInfoUserShapeOutgoing_EP5
    {
        UINT16 opcode{ 0x303 };
        ULONG objectId;
        bool dead;
        bool sitting;
        Country country;
        Family family;
        UINT8 hair;
        UINT8 face;
        UINT8 size;
        Job job;
        Sex sex;
        PartyType partyType;
        Grow grow;
        UINT32 kills;
        Equipment<8> equipment;
        CharName charName;
        CloakBadge cloakBadge;
        CharArray<25> guildName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 17 items (6.4)
    struct GetInfoUserShapeOutgoing_EP6_4
    {
        UINT16 opcode{ 0x303 };
        ULONG objectId;
        bool dead;
        bool sitting;
        Country country;
        Family family;
        UINT8 hair;
        UINT8 face;
        UINT8 size;
        Job job;
        Sex sex;
        PartyType partyType;
        Grow grow;
        UINT32 kills;
        Equipment<17> equipment;
        CharName charName;
        CloakBadge cloakBadge;
        CharArray<25> guildName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GetInfoTargetMobOutgoing
    {
        UINT16 opcode{ 0x305 };
        ULONG objectId;
        UINT32 health;
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
    // 12 items (5.4, 6.0)
    struct GetInfoInspectOutgoing_EP5
    {
        UINT16 opcode{ 0x307 };
        UINT8 itemCount;
        Array<Item0307, 12> itemList;

        constexpr static int baseLength = 3;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 17 items (6.4)
    struct GetInfoInspectOutgoing_EP6_4
    {
        UINT16 opcode{ 0x307 };
        UINT8 itemCount;
        Array<Item0307, 17> itemList;

        constexpr static int baseLength = 3;
    };
    #pragma pack(pop)
}
