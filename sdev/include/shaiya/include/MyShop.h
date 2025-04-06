#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    struct CUser;

    enum struct MyShopStatus : int32_t
    {
        None,
        Closed,
        Open
    };

    #pragma pack(push, 1)
    struct MyShop
    {
        CUser* user;                  //0x1634  0x00
        MyShopStatus status;          //0x1638  0x04
        Array<int32_t, 20> srcBag;    //0x163C  0x08
        Array<int32_t, 20> srcSlot;   //0x168C  0x58
        Array<int32_t, 20> money;     //0x16DC  0xA8
        int32_t messageLength;        //0x172C  0xF8
        String<121> message;          //0x1730  0xFC
        PAD(3);
        int32_t usingCount;           //0x17AC  0x178
        Array<uint32_t, 16> userIds;  //0x17B0  0x17C
        uint32_t usingMyShopUserId;   //0x17F0  0x1BC
        // 0x1C0

        static void Ended(MyShop* myShop);
    };
    #pragma pack(pop)

    static_assert(sizeof(MyShop) == 0x1C0);
}
