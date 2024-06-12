#pragma once
#include <strsafe.h>
#include <shaiya/include/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct LoginRequest
    {
        UINT16 opcode{ 0xA102 };
        CharArray<32> username;
        CharArray<32> password;

        LoginRequest() = default;

        LoginRequest(const char* username, const char* password)
            : username{}, password{}
        {
            StringCbCopyA(this->username.data(), this->username.size(), username);
            StringCbCopyA(this->password.data(), this->password.size(), password);
        }
    };
    #pragma pack(pop)
}
