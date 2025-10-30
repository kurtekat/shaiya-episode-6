#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct AdminNotice;

    #pragma pack(push, 1)
    struct AdminInfo
    {
        uint32_t questionId;        //0x580C
        uint32_t chatSendToId;      //0x5810
        bool visible;               //0x5814
        bool attackable;            //0x5815
        PAD(2);
        tick32_t enableMoveTime;    //0x5818
        tick32_t enableChatTime;    //0x581C
        uint32_t chatListenId;      //0x5820
        uint32_t chatListenIdFrom;  //0x5824
        AdminNotice* notice;        //0x5828
        // 0x20
    };
    #pragma pack(pop)

    static_assert(sizeof(AdminInfo) == 0x20);
}
