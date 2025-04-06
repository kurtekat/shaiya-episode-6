#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/UserTypes.h>

namespace shaiya
{
    enum struct LoginResult : uint8_t
    {
    };

    #pragma pack(push, 1)
    // TP_LOGIN
    struct LoginOutgoing
    {
        uint16_t opcode{ 0xA102 };
        LoginResult result;
        uint32_t billingId;
        AuthStatus authStatus;
        Array<uint8_t, 16> sessionKey;
    };
    #pragma pack(pop)
}
