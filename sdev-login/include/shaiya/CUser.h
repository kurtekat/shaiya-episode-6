#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/UserTypes.h>
#include "CUserCrypto.h"
#include "SConnection.h"
#include "SDBDispatchClient.h"

namespace shaiya
{
    enum struct UserStatus : int32_t
    {
        Default,
        LoginRequest,
        GetUserSuccess,
        LoginSuccess
    };

    #pragma pack(push, 1)
    struct CUser : SConnection, SDBDispatchClient
    {
        uint32_t billingId;         //0x100
        AuthStatus authStatus;      //0x104
        PAD(3);
        String<32> username;        //0x108
        uint64_t sessionId;         //0x128
        int32_t loginAttemptCount;  //0x130
        UserStatus status;          //0x134
        uint8_t serverId;           //0x138
        PAD(3);
        CUserCrypto crypto;         //0x13C
        String<32> recvUsername;    //0x3C0
        String<32> recvPassword;    //0x3E0
        CRITICAL_SECTION cs;        //0x400
        // 0x418
    };
    #pragma pack(pop)

    static_assert(sizeof(CUser) == 0x418);
}
