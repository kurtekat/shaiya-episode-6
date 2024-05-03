#pragma once
#include <bitset>
#include <shaiya/include/common.h>
#include <shaiya/include/common/AuthStatus.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct LoginResponse
    {
        UINT16 opcode{ 0xA102 };
        UINT8 userStatus;
        ULONG userId;
        AuthStatus authStatus;
        Array<UINT8, 16> sessionKey;
    };
    #pragma pack(pop)
}
