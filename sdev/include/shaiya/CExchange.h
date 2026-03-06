#pragma once
#include <shaiya/include/common.h>
#include "ExcItem.h"

namespace shaiya
{
    struct CUser;

    enum struct ExchangeStatus : uint32_t
    {
        None,
        RequestSent,
        RequestRecv,
        Ready,
        Confirmed
    };

    #pragma pack(push, 1)
    struct CExchange
    {
        ExchangeStatus status;    //0x15C0
        CUser* user;              //0x15C4
        uint32_t money;           //0x15C8
        Array<ExcItem, 8> items;  //0x15CC
        bool ready;               //0x15E4
        PAD(3);
        // 0x28
    };
    #pragma pack(pop)

    static_assert(sizeof(CExchange) == 0x28);
}
