#pragma once
#include <include/shaiya/common.h>
#include <include/shaiya/include/SNode.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct CTrap
    {
        PAD(52);
        Country country;  //0x34
        PAD(11);
        // 0x40

        static void GetCountry(CTrap* trap/*eax*/);
        static void SetCountry(CTrap* trap/*eax*/, int country);
    };
    #pragma pack(pop)
}
