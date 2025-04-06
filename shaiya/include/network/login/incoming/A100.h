#pragma once
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TPC_LOGIN
    struct LoginIncoming
    {
        uint16_t opcode{ 0xA102 };
        String<32> username;
        String<16> password;
    };
    #pragma pack(pop)
}
