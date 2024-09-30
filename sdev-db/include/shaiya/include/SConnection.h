#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/SInternetAddress.h"
#include "include/shaiya/include/SNode.h"
#include "include/shaiya/include/SSyncQueueBuffer.h"
#include "include/shaiya/include/SSyncQueueBufferSend.h"

namespace shaiya
{
    struct SAgent;

    #pragma pack(push, 1)
    struct SConnectionParam
    {
        SNode node;             //0x00  //0x08
        PAD(8);
        int closeType;          //0x10  //0x18
        int closeError;         //0x14  //0x1C
        UINT64 sendCount;       //0x18
        UINT64 recvCount;       //0x20
        UINT64 sendBytes;       //0x28
        UINT64 recvBytes;       //0x30
        DWORD connectTick;      //0x38
        UINT32 sendProcessing;  //0x3C
        PAD(8);
        CRITICAL_SECTION cs;    //0x48
        // 0x60
    };
    #pragma pack(pop)

    static_assert(sizeof(SConnectionParam) == 0x60);

    #pragma pack(push, 1)
    struct SConnection
    {
        void* vftable;              //0x00
        PAD(4);
        SConnectionParam param;     //0x08
        int socket;                 //0x68
        SInternetAddress address;   //0x6C
        SSyncQueueBuffer sqb;       //0x7C
        SSyncQueueBufferSend sqbs;  //0xA0
        SAgent* agent;              //0xC8
        PAD(4);
        // 0xD0

        static void Send(SConnection* connection/*ecx*/, void* packet, int length);
        static void Close(SConnection* connection/*ecx*/, int closeType, int closeErr);
    };
    #pragma pack(pop)

    static_assert(sizeof(SConnection) == 0xD0);
}
