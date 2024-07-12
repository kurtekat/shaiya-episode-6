#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct CUser;

    enum struct MyShopStatus : UINT32
    {
        None,
        Closed,
        Open
    };

    #pragma pack(push, 1)
    struct MyShop
    {
        CUser* user;                //0x1634  0x00
        MyShopStatus status;        //0x1638  0x04
        Array<UINT32, 20> srcBag;   //0x163C  0x08
        Array<UINT32, 20> srcSlot;  //0x168C  0x58
        Array<UINT32, 20> price;    //0x16DC  0xA8
        UINT32 messageLength;       //0x172C  0xF8
        CharArray<124> message;     //0x1730  0xFC
        UINT32 userCount;           //0x17AC  0x178
        Array<ULONG, 16> users;     //0x17B0  0x17C
        ULONG viewMarketCharId;     //0x17F0  0x1BC
        // 0x1C0

        static void Ended(MyShop* myShop);
    };
    #pragma pack(pop)

    static_assert(sizeof(MyShop) == 0x1C0);
}
