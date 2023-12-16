#include <include/shaiya/include/SDatabasePool.h>
using namespace shaiya;

SDatabase* SDatabasePool::AllocDB()
{
    typedef SDatabase* (__thiscall* LPFN)(void*);
    return (*(LPFN)0x441370)((void*)0x4930A8);
}

void SDatabasePool::FreeDB(SDatabase* db)
{
    typedef void(__thiscall* LPFN)(void*, SDatabase*);
    (*(LPFN)0x441430)((void*)0x4930A8, db);
}
