#pragma once
#include <shaiya/common.h>

namespace shaiya
{
    FWDDECL SDatabase;

    // g_DatabasePool 0x4930A8;

    struct SDatabasePool
    {
        static SDatabase* AllocDB();
        static void FreeDB(SDatabase* db);
    };
}
