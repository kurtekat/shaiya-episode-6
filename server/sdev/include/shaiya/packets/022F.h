#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    enum struct ItemExpireNoticeType : UINT16
    {
        DeletedFromInventory = 883,
        DeletedFromWarehouse,
        MinutesLeftInventory,
        MinutesLeftWarehouse,
        HoursLeftInventory,
        HoursLeftWarehouse,
    };

    struct ItemExpireNoticeOutgoing
    {
        UINT16 opcode{ 0x22F };
        UINT8 type;
        UINT8 typeId;
        UINT8 timeValue;
        ItemExpireNoticeType noticeType;
    };
    #pragma pack(pop)
}
