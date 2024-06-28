#pragma once
#include <bitset>
#include <shaiya/include/common.h>
#include <shaiya/include/user/AuthStatus.h>

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

        LoginResponse() = default;

        LoginResponse(UINT8 userStatus, ULONG userId, AuthStatus authStatus, Array<UINT8, 16>& sessionKey)
            : userStatus(userStatus), userId(userId), authStatus(authStatus), sessionKey(sessionKey)
        {
        }
    };
    #pragma pack(pop)
}
