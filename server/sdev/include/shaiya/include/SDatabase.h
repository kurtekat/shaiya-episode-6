#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

#include <sdev/include/shaiya/common.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SDatabase
    {
        PAD(8);
        bool rollback;            //0x08
        PAD(3);
        int queryError;           //0x0C
        SQLINTEGER* nativeError;  //0x10
        SQLCHAR* sqlState;        //0x14
        PAD(72);
        int dbg_lc;               //0x60
        PAD(1988);
        SQLHENV env;              //0x828
        SQLHDBC dbc;              //0x82C
        SQLHSTMT stmt;            //0x830
        PAD(4);
        // 0x838

        static short Fetch(SDatabase* db/*ecx*/);
        static short GetData(SDatabase* db/*ecx*/, int paramNum, int columnSize, int paramType, void* data, long cbLen);
        static int Prepare(SDatabase* db/*ecx*/);
        static short Query(SDatabase* db/*ecx*/, const char* query);
        static void WriteErrorLog(SDatabase* db);
    };
    #pragma pack(pop)
}
