#include "include/shaiya/include/SDatabase.h"
using namespace shaiya;

short SDatabase::ExecuteSql(SDatabase* db/*ecx*/)
{
    typedef short(__thiscall* LPFN)(SDatabase*);
    return (*(LPFN)0x444E20)(db);
}

int SDatabase::Prepare(SDatabase* db/*ecx*/)
{
    typedef int(__thiscall* LPFN)(SDatabase*);
    return (*(LPFN)0x4440D0)(db);
}

short SDatabase::PrepareSql(SDatabase* db/*ecx*/, const char* query)
{
    typedef short(__thiscall* LPFN)(SDatabase*, const char*);
    return (*(LPFN)0x444DC0)(db, query);
}

void SDatabase::WriteErrorLog(SDatabase* db/*ecx*/)
{
    typedef void(__thiscall* LPFN)(SDatabase*);
    (*(LPFN)0x4446B0)(db);
}
