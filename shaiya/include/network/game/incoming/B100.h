#pragma once
#include <shaiya/include/common.h>

// CUser::PacketBilling

namespace shaiya
{
    #pragma pack(push, 1)
    struct BillingItemBankToBagIncoming
    {
        UINT16 opcode{ 0xB102 };
        UINT8 srcSlot;
        ULONG npcId;

        BillingItemBankToBagIncoming() = default;

        BillingItemBankToBagIncoming(UINT8 srcSlot, ULONG npcId)
            : srcSlot(srcSlot), npcId(npcId)
        {
        }
    };
    #pragma pack(pop)
}
