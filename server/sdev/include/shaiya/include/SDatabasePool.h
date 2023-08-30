#pragma once

namespace shaiya
{
    FWDDECL SDatabase;
    
    struct SDatabasePool
    {
        static SDatabase* AllocDB();
        static void FreeDB(SDatabase* db);
    };
}
