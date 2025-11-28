#include "SDatabasePool.h"
using namespace shaiya;

SDatabase* SDatabasePool::AllocDB()
{
    typedef SDatabase* (__thiscall* LPFN)(void*);
    return (*(LPFN)0x4F4E20)((void*)0x109BED0);
}

void SDatabasePool::FreeDB(SDatabase* db)
{
    typedef void(__thiscall* LPFN)(void*, SDatabase*);
    (*(LPFN)0x4F4EE0)((void*)0x109BED0, db);
}

bool SDatabasePool::Connect(
    int connectionCount, 
    const char* serverName, 
    const char* dbName, 
    const char* username, 
    const char* password, 
    unsigned queryTimeout,
    unsigned connectionTimeout
)
{
    typedef bool(__thiscall* LPFN)(void*, int, const char*, const char*, const char*, const char*, unsigned, unsigned);
    return (*(LPFN)0x4F4A10)((void*)0x109BED0, connectionCount, serverName, dbName, username, password, queryTimeout, connectionTimeout);
}

void SDatabasePool::Disconnect()
{
    typedef void(__thiscall* LPFN)(void*);
    (*(LPFN)0x4F45A0)((void*)0x109BED0);
}

void SDatabasePool::Release()
{
    typedef void(__thiscall* LPFN)(void*);
    (*(LPFN)0x4F47A0)((void*)0x109BED0);
}
