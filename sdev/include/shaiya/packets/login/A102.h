#pragma once
#include <bitset>
#include <include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct LoginRequest
    {
        UINT16 opcode{ 0xA102 };
        Username username;
        Password password;
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct LoginResponse
    {
        UINT16 opcode{ 0xA102 };
        UINT8 status;
        UserId userId;
        AuthStatus authStatus;
        std::bitset<128> identity;
    };
    #pragma pack(pop)
}
