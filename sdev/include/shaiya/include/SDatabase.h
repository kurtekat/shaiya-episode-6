#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

#include <sdev/include/shaiya/common.h>
#include <sdev/include/shaiya/include/SNode.h>

namespace shaiya
{
    #pragma pack(push, 1)
    struct SDatabase
    {
        SNode node;               //0x00
        bool rollback;            //0x08
        PAD(3);
        int queryError;           //0x0C
        SQLINTEGER* nativeError;  //0x10
        SQLCHAR* state;           //0x14
        PAD(2064);
        SQLHENV env;              //0x828
        SQLHDBC dbc;              //0x82C
        SQLHSTMT stmt;            //0x830
        PAD(4);
        // 0x838

        static int Prepare(SDatabase* db/*ecx*/);
        static void WriteErrorLog(SDatabase* db);
    };
    #pragma pack(pop)
}
