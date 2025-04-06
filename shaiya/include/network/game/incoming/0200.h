#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/Sex.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TPC_ITEM_BAGTOBAG
    struct GameItemBagToBagIncoming
    {
        uint16_t opcode{ 0x204 };
        uint8_t srcBag;
        uint8_t srcSlot;
        uint8_t destBag;
        uint8_t destSlot;
        // warehouse
        uint32_t npcId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameItemGetIncoming
    {
        uint16_t opcode{ 0x205 };
        uint32_t objectId;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_ITEM_DROP
    struct GameItemDropIncoming
    {
        uint16_t opcode{ 0x206 };
        uint8_t bag;
        uint8_t slot;
        uint8_t count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameUserStatusUpIncoming
    {
        uint16_t opcode{ 0x208 };
        uint16_t strength;
        uint16_t dexterity;
        uint16_t reaction;
        uint16_t intelligence;
        uint16_t wisdom;
        uint16_t luck;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_USER_GETSKILL
    struct GameUserSkillGetIncoming
    {
        uint16_t opcode{ 0x209 };
        uint16_t skillId;
        uint8_t skillLv;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_USER_USEPORTAL
    struct GameUserPortalUseIncoming
    {
        uint16_t opcode{ 0x20A };
        uint8_t portalIndex;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_USER_USEGATENPC
    struct GameUserGateKeeperUseIncoming
    {
        uint16_t opcode{ 0x20C };
        uint32_t npcId;
        uint8_t gateIndex;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameStatusResultInfoIncoming
    {
        uint16_t opcode{ 0x218 };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameStatusResultKillIncoming
    {
        uint16_t opcode{ 0x219 };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct GameStatusResultDeathIncoming
    {
        uint16_t opcode{ 0x21A };
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    // TPC_BODYCHG
    struct GameUserBodyChangeIncoming
    {
        uint16_t opcode{ 0x226 };
        uint8_t bag;
        uint8_t slot;
        uint8_t hair;
        uint8_t face;
        uint8_t size;
        Sex sex;
    };
    #pragma pack(pop)
}
