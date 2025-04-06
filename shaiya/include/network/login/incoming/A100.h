#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/UserTypes.h>

namespace shaiya
{
    #pragma pack(push, 1)
    // TPC_LOGIN
    struct LoginIncoming
    {
        uint16_t opcode{ 0xA102 };
        Username username;
        Password password;
    };
    #pragma pack(pop)
}
