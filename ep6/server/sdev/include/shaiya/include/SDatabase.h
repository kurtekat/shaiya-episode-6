#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    FWDDECL SLog;

    #pragma pack(push, 1)
    struct SDatabase
    {
        PAD(8);
        bool rollback;            //0x08
        PAD(3);
        int sqlError;             //0x0C
        SQLINTEGER* nativeError;  //0x10
        SQLCHAR* sqlState;        //0x14
        PAD(2060);
        SLog* log;                //0x824
        SQLHENV env;              //0x828
        SQLHDBC dbc;              //0x82C
        SQLHSTMT stmt;            //0x830
        PAD(4);
        // 0x838
    };
    #pragma pack(pop)
}
