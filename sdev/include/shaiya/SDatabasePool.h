#pragma once
#include <shaiya/include/common.h>
#include "SSyncList.h"

namespace shaiya
{
    struct SDatabase;
    struct SLog;

    #pragma pack(push, 1)
    struct SDatabasePool
    {
        SDatabase* db;               //0x00
        SSyncList<SDatabase> pool;   //0x04
        HANDLE semaphore;            //0x30
        int32_t connectionCount;     //0x34
        uint32_t connectionTimeout;  //0x38
        uint32_t queryTimeout;       //0x3C
        // e.g., 127.0.0.1
        String<256> serverName;      //0x40
        String<256> dbName;          //0x140
        String<256> username;        //0x240
        String<256> password;        //0x340
        // 0: SQLDriverConnect
        // 1: SQLConnect
        bool connectionString;       //0x440
        PAD(3);
        CRITICAL_SECTION cs;         //0x444
        SLog* log;                   //0x45C
        // 0x460

        static SDatabase* AllocDB();
        static void FreeDB(SDatabase* db);
        static bool Connect(
            int connectionCount,
            const char* serverName,
            const char* dbName,
            const char* username,
            const char* password,
            unsigned queryTimeout,
            unsigned connectionTimeout
        );
        static void Disconnect();
        static void Release();
    };
    #pragma pack(pop)

    static_assert(sizeof(SDatabasePool) == 0x460);
}
