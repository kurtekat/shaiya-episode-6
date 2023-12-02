#pragma once

namespace shaiya
{
    struct SDatabase;
    
    struct SDatabasePool
    {
        static SDatabase* AllocDB();
        static void FreeDB(SDatabase* db);
    };
}
