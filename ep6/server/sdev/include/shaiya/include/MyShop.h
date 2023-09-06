#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    FWDDECL CUser;

    #pragma pack(push, 1)
    enum struct MyShopState : UINT32
    {
        None,
        Closed,
        Open
    };

    struct MyShop
    {
        CUser* user;         //0x00
        MyShopState state;   //0x04
        UINT32 srcBag[20];   //0x08
        UINT32 srcSlot[20];  //0x58
        UINT32 price[20];    //0xA8
        UINT32 msgLen;       //0xF8
        char message[124];   //0xFC
        Count users;         //0x178
        ULONG userId[16];    //0x17C
        PAD(4);
        // 0x1C0

        static void Ended(MyShop* myShop);
    };
    #pragma pack(pop)
}
