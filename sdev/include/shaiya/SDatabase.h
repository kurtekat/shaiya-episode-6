#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <shaiya/include/common.h>
#include "SNode.h"

namespace shaiya
{
    struct SLog;

    #pragma pack(push, 1)
    struct SDatabase : SNode
    {
        bool transacting;             //0x08
        PAD(3);
        SQLINTEGER queryError;        //0x0C
        SQLINTEGER* nativeError;      //0x10
        Array<SQLCHAR, 16> sqlState;  //0x14
        String<2048> errorMessage;    //0x24
        SLog* log;                    //0x824
        SQLHENV env;                  //0x828
        SQLHDBC dbc;                  //0x82C
        SQLHSTMT stmt;                //0x830
        bool disconnectRequested;     //0x834
        bool disconnectError;         //0x835
        PAD(2);
        // 0x838

        static int Prepare(SDatabase* db/*ecx*/);
        static void WriteErrorLog(SDatabase* db/*ecx*/);
    };
    #pragma pack(pop)

    static_assert(sizeof(SDatabase) == 0x838);
}
