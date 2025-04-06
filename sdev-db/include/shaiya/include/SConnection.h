#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/SConnectionParam.h"
#include "include/shaiya/include/SInternetAddress.h"
#include "include/shaiya/include/SNode.h"
#include "include/shaiya/include/SSyncQueueBuffer.h"
#include "include/shaiya/include/SSyncQueueBufferSend.h"

namespace shaiya
{
    struct SAgent;

    #pragma pack(push, 1)
    struct SConnection
    {
        void* vftable;                   //0x00
        PAD(4);
        SConnectionParam param;          //0x08
        int socket;                      //0x68
        SInternetAddress address;        //0x6C
        SSyncQueueBuffer recvQueue;      //0x7C
        SSyncQueueBufferSend sendQueue;  //0xA0
        SAgent* agent;                   //0xC8
        PAD(4);
        // 0xD0

        static void Send(SConnection* connection/*ecx*/, void* packet, int length);
        static void Close(SConnection* connection/*ecx*/, int closeType);
    };
    #pragma pack(pop)

    static_assert(sizeof(SConnection) == 0xD0);
}
