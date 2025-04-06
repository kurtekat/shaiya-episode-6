#include "include/shaiya/include/SDatabase.h"
using namespace shaiya;

short SDatabase::ExecuteSql(SDatabase* db/*ecx*/)
{
    typedef short(__thiscall* LPFN)(SDatabase*);
    return (*(LPFN)0x41BF20)(db);
}

short SDatabase::PrepareSql(SDatabase* db/*ecx*/, const char* query)
{
    typedef short(__thiscall* LPFN)(SDatabase*, const char*);
    return (*(LPFN)0x41BEC0)(db, query);
}
