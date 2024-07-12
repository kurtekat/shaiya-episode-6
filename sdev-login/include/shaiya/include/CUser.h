#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SConnection.h>
#include <shaiya/include/user/AuthStatus.h>
#include "include/shaiya/include/CUserCrypto.h"
#include "include/shaiya/include/SDBDispatchClient.h"

namespace shaiya
{
    enum struct UserStatus : UINT32
    {
        Default,
        LoginRequest,
        GetUserSuccess,
        LoginSuccess
    };

    #pragma pack(push, 1)
    struct CUser
    {
        SConnection connection;    //0x00
        SDBDispatchClient client;  //0xD0
        ULONG userId;              //0x100
        AuthStatus authStatus;     //0x104
        PAD(3);
        // 0x105
        CharArray<32> loginRequestUsername;
        UINT64 sessionId;          //0x128
        // max: 10
        UINT32 loginRequestCount;  //0x130
        UserStatus status;         //0x134
        UINT8 serverId;            //0x138
        PAD(3);
        CUserCrypto crypto;        //0x13C
        CharArray<32> username;    //0x3C0
        CharArray<32> password;    //0x3E0
        CRITICAL_SECTION cs;       //0x400
        // 0x418
    };
    #pragma pack(pop)

    static_assert(sizeof(CUser) == 0x418);
}
