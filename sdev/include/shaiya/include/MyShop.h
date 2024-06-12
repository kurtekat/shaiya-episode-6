#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct CUser;

    enum struct MyShopStatusType : UINT32
    {
        None,
        Closed,
        Open
    };

    #pragma pack(push, 1)
    struct MyShop
    {
        CUser* user;                  //0x00
        MyShopStatusType statusType;  //0x04
        Array<UINT32, 20> srcBag;     //0x08
        Array<UINT32, 20> srcSlot;    //0x58
        Array<UINT32, 20> price;      //0xA8
        UINT32 messageLength;         //0xF8
        CharArray<124> message;       //0xFC
        UINT32 userCount;             //0x178
        Array<ULONG, 16> userList;    //0x17C
        PAD(4);
        // 0x1C0

        static void Ended(MyShop* myShop);
    };
    #pragma pack(pop)
}
