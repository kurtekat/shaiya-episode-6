#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct CItem;
    struct CUser;

    enum struct ExchangeStatus : UINT32
    {
        None,
        RequestSent,
        RequestReceived,
        Start
    };

    #pragma pack(push, 1)
    struct ExcItem
    {
        UINT8 bag;
        UINT8 slot;
        UINT8 count;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct CExchange
    {
        ExchangeStatus status;    //0x15C0
        CUser* user;              //0x15C4
        UINT32 money;             //0x15C8
        Array<ExcItem, 8> items;  //0x15CC
        bool ready;               //0x15E4
        // custom
        bool confirmed;           //0x15E5
        PAD(2);
        // 0x28
    };
    #pragma pack(pop)

    static_assert(sizeof(CExchange) == 0x28);

    #pragma pack(push, 1)
    struct CExchangePvP
    {
        CExchange exchange;      //0x15E8
        UINT32 money;            //0x1610
        Array<CItem*, 8> items;  //0x1614
        // 0x4C
    };
    #pragma pack(pop)

    static_assert(sizeof(CExchangePvP) == 0x4C);
}
