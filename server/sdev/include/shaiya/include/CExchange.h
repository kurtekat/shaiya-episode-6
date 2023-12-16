#pragma once
#include <include/shaiya/common.h>

namespace shaiya
{
    struct CItem;
    struct CUser;

    #pragma pack(push, 1)
    struct ExcItem
    {
        UINT8 bag;
        UINT8 slot;
        UINT8 count;
    };

    struct CExchange
    {
        PAD(4);              //0x15C0
        CUser* user;         //0x15C4
        UINT32 money;        //0x15C8
        // 0x15CC
        Array<ExcItem, 8> itemList;
        bool ready;          //0x15E4
        // custom
        bool confirmed;      //0x15E5
        PAD(2);
        // 0x28
    };

    struct CExchangePvP
    {
        CExchange exchange;  //0x15E8
        UINT32 money;        //0x1610
        // 0x1614
        Array<CItem*, 8> itemList;
        // 0x4C
    };
    #pragma pack(pop)
}
