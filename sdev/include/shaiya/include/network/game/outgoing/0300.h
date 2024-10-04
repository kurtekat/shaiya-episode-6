#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Country.h>
#include <shaiya/include/common/CraftName.h>
#include <shaiya/include/common/Equipment.h>
#include <shaiya/include/common/Family.h>
#include <shaiya/include/common/Grow.h>
#include <shaiya/include/common/Gems.h>
#include <shaiya/include/common/Job.h>
#include <shaiya/include/common/PartyType.h>
#include <shaiya/include/common/Sex.h>

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
        PartyType partyType;
        Grow grow;
        UINT32 kills;
        ShapeEquipment<8> equipment;
        CharArray<21> charName;
        CloakBadge cloakBadge;
        CharArray<25> guildName;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 17 items (6.4 PT)
    struct GetInfoUserShapeOutgoing2
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
        PartyType partyType;
        Grow grow;
        UINT32 kills;
        ShapeEquipment<17> equipment;
        CharArray<21> charName;
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
    struct GetInfoInspectOutgoing
    {
        UINT16 opcode{ 0x307 };
        UINT8 itemCount;
        Array<Item0307, 12> itemList;

        constexpr int size_without_list() { return 3; }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // 17 items (6.4 PT)
    struct GetInfoInspectOutgoing2
    {
        UINT16 opcode{ 0x307 };
        UINT8 itemCount;
        Array<Item0307, 17> itemList;

        constexpr int size_without_list() { return 3; }
    };
    #pragma pack(pop)
}
