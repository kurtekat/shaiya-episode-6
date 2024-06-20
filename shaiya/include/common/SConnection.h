#pragma once
#include <shaiya/include/common.h>
#include <shaiya/include/common/SInternetAddress.h>
#include <shaiya/include/common/SNode.h>
#include <shaiya/include/common/SSyncQueueBuffer.h>
#include <shaiya/include/common/SSyncQueueBufferSend.h>

namespace shaiya
{
    struct SAgent;

    #pragma pack(push, 1)
    struct SConnectionParam
    {
        PAD(16);
        int closeType;          //0x10  //0x18
        int closeErr;           //0x14  //0x1C
        UINT64 sent;            //0x18
        UINT64 received;        //0x20
        UINT64 bytesSent;       //0x28
        UINT64 bytesReceived;   //0x30
        DWORD connectTick;      //0x38
        UINT32 sendProcessing;  //0x3C
        PAD(8);
        CRITICAL_SECTION cs;    //0x48
        // 0x60
    };
    #pragma pack(pop)

    #pragma pack(push, 1)
    struct SConnection
    {
        PAD(8);
        SConnectionParam param;     //0x08
        int socket;                 //0x68
        SInternetAddress address;   //0x6C
        SSyncQueueBuffer sqb;       //0x7C
        SSyncQueueBufferSend sqbs;  //0xA0
        SAgent* agent;              //0xC8
        PAD(4);
        // 0xD0

        static void Send(SConnection* connection/*ecx*/, void* buf, int len);
        static void Close(SConnection* connection/*ecx*/, int closeType, int closeErr);
    };
    #pragma pack(pop)
}
