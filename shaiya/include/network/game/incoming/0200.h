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

        ItemBagToBagIncoming() = default;

        ItemBagToBagIncoming(UINT8 srcBag, UINT8 srcSlot, UINT8 destBag, UINT8 destSlot, ULONG npcId)
            : srcBag(srcBag), srcSlot(srcSlot), destBag(destBag), destSlot(destSlot), npcId(npcId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemPickIncoming
    {
        UINT16 opcode{ 0x205 };
        ULONG zoneItemId;

        ItemPickIncoming() = default;

        ItemPickIncoming(ULONG zoneItemId)
            : zoneItemId(zoneItemId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct ItemRemoveIncoming
    {
        UINT16 opcode{ 0x206 };
        UINT8 bag;
        UINT8 slot;
        UINT8 count;

        ItemRemoveIncoming() = default;

        ItemRemoveIncoming(UINT8 bag, UINT8 slot, UINT8 count)
            : bag(bag), slot(slot), count(count)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct PortalEnableIncoming
    {
        UINT16 opcode{ 0x20A };
        UINT8 portalId;

        PortalEnableIncoming() = default;

        PortalEnableIncoming(UINT8 portalId)
            : portalId(portalId)
        {
        }
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct VetRewardLevelIncoming
    {
        UINT16 opcode{ 0x218 };

        VetRewardLevelIncoming() = default;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct VetKillRewardIncoming
    {
        UINT16 opcode{ 0x219 };

        VetKillRewardIncoming() = default;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct VetDeathRewardIncoming
    {
        UINT16 opcode{ 0x21A };

        VetDeathRewardIncoming() = default;
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

        AppearanceChangeIncoming() = default;

        AppearanceChangeIncoming(UINT8 bag, UINT8 slot, UINT8 hair, UINT8 face, UINT8 size, Sex sex)
            : bag(bag), slot(slot), hair(hair), face(face), size(size), sex(sex)
        {
        }
    };
    #pragma pack(pop)
}
