#pragma once
#include <shaiya/include/common.h>
#include "SConnectionParam.h"
#include "SInternetAddress.h"
#include "SNode.h"
#include "SSyncQueueBuffer.h"
#include "SSyncQueueBufferSend.h"

namespace shaiya
{
    struct SAgent;

    #pragma pack(push, 1)
    struct SConnection_vtbl
    {
        void* vftable;
        PAD(4);
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct SConnection : SConnection_vtbl, SConnectionParam
    {
        int socket;                      //0x68
        SInternetAddress address;        //0x6C
        SSyncQueueBuffer recvQueue;      //0x7C
        SSyncQueueBufferSend sendQueue;  //0xA0
        SAgent* agent;                   //0xC8
        PAD(4);
        // 0xD0

        static void Send(SConnection* connection/*ecx*/, void* packet, int length);
        static void Close(SConnection* connection/*ecx*/, int closeType, int closeError);
    };
    #pragma pack(pop)

    static_assert(sizeof(SConnection) == 0xD0);
}
