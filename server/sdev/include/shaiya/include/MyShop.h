#pragma once
#include <include/shaiya/common.h>

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
        CUser* user;                 //0x00
        MyShopState state;           //0x04
        Array<UINT32, 20> srcBag;    //0x08
        Array<UINT32, 20> srcSlot;   //0x58
        Array<UINT32, 20> price;     //0xA8
        UINT32 messageLength;        //0xF8
        Array<char, 124> message;    //0xFC
        UINT32 userCount;            //0x178
        Array<CharId, 16> userList;  //0x17C
        PAD(4);
        // 0x1C0

        static void Ended(MyShop* myShop);
    };
    #pragma pack(pop)
}
