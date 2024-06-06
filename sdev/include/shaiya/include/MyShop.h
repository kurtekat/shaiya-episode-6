#pragma once
#include <array>
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
        CUser* user;                     //0x00
        MyShopStatusType statusType;     //0x04
        std::array<UINT32, 20> srcBag;   //0x08
        std::array<UINT32, 20> srcSlot;  //0x58
        std::array<UINT32, 20> price;    //0xA8
        UINT32 messageLength;            //0xF8
        std::array<char, 124> message;   //0xFC
        UINT32 userCount;                //0x178
        std::array<ULONG, 16> userList;  //0x17C
        PAD(4);
        // 0x1C0

        static void Ended(MyShop* myShop);
    };
    #pragma pack(pop)
}
