#pragma once
#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // not implemented
    struct SaveBankMoney
    {
        UINT16 opcode{ 0x60B };
        UserId userId;
        UINT32 bankMoney;
    };
    #pragma pack(pop)
}
