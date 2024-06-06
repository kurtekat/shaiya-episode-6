#pragma once
#include <array>
#include <shaiya/include/common.h>
#include <shaiya/include/common/SSyncList.h>

namespace shaiya
{
    struct SDatabase;
    struct SLog;

    #pragma pack(push, 1)
    struct SDatabasePool
    {
        SDatabase* db;                   //0x00
        SSyncList<SDatabase> dbList;     //0x04
        HANDLE semaphore;                //0x30
        long semaphoreCount;             //0x34
        ULONG queryTimeout;              //0x38
        ULONG connectionTimeout;         //0x3C
        // e.g. 127.0.0.1
        std::array<char, 256> server;    //0x40
        std::array<char, 256> dbName;    //0x140
        std::array<char, 256> username;  //0x240
        std::array<char, 256> password;  //0x340
        bool unknown;                    //0x440
        PAD(3);
        CRITICAL_SECTION cs444;          //0x444
        SLog* log;                       //0x45C
        // 0x460

        static SDatabase* AllocDB();
        static void FreeDB(SDatabase* db);
        static bool Connect(
            int numConnection,
            const char* server,
            const char* dbName,
            const char* username,
            const char* password,
            ULONG queryTimeout,
            ULONG connectionTimeout
        );
        static void Disconnect();
        static void Release();
    };
    #pragma pack(pop)
}
