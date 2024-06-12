#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <shaiya/include/common.h>
#include <shaiya/include/common/SNode.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SDatabase
    {
        SNode node;               //0x00
        PAD(4);
        SQLINTEGER qerr;          //0x0C
        PAD(4);
        SQLCHAR* state;           //0x14
        PAD(2064);
        SQLHENV env;              //0x828
        SQLHDBC dbc;              //0x82C
        SQLHSTMT stmt;            //0x830
        PAD(4);
        // 0x838

        static short ExecuteSql(SDatabase* db/*ecx*/);
        static int Prepare(SDatabase* db/*ecx*/);
        static short PrepareSql(SDatabase* db/*ecx*/, const char* query);
        static void WriteErrorLog(SDatabase* db/*ecx*/);
    };
    #pragma pack(pop)
}
