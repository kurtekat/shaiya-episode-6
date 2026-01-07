#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TP_MGR_PREBUYPRODUCT
    struct SessionMgrPreBuyProductIncoming
    {
        uint16_t opcode{ 0x1B03 };
        uint32_t billingId;
        String<32> username;
        String<21> productCode;
        String<21> targetName;
        uint32_t purchasePoints;
        uint32_t ipv4;
    };
    #pragma pack(pop)

    static_assert(sizeof(SessionMgrPreBuyProductIncoming) == 0x58);
}
