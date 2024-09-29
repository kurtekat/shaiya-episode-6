#pragma once
#include <shaiya/include/common.h>
#include "include/shaiya/include/SSyncList.h"

namespace shaiya
{
    struct SDatabase;
    struct SLog;

    #pragma pack(push, 1)
    struct SDatabasePool
    {
        SDatabase* connection;      //0x00
        SSyncList<SDatabase> pool;  //0x04
        HANDLE semaphore;           //0x30
        long semaphoreCount;        //0x34
        ULONG queryTimeout;         //0x38
        ULONG connectionTimeout;    //0x3C
        // e.g., 127.0.0.1
        CharArray<256> server;      //0x40
        CharArray<256> database;    //0x140
        CharArray<256> username;    //0x240
        CharArray<256> password;    //0x340
        // 0: SQLDriverConnect
        // 1: SQLConnect
        UINT8 connectionType;       //0x440
        PAD(3);
        CRITICAL_SECTION cs;        //0x444
        SLog* log;                  //0x45C
        // 0x460

        static SDatabase* AllocDB();
        static void FreeDB(SDatabase* db);
    };
    #pragma pack(pop)

    static_assert(sizeof(SDatabasePool) == 0x460);
}
