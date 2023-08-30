#include <sdev/include/shaiya/include/SDatabase.h>
using namespace shaiya;

short SDatabase::Fetch(SDatabase* db/*ecx*/)
{
    typedef short(__thiscall* LPFN)(SDatabase*);
    return (*(LPFN)0x444CC0)(db);
}

short SDatabase::GetData(SDatabase* db/*ecx*/, int paramNum, int columnSize, int paramType, void* data, long cbLen)
{
    typedef short(__thiscall* LPFN)(SDatabase*, int, int, int, void*, long);
    return (*(LPFN)0x444270)(db, paramNum, columnSize, paramType, data, cbLen);
}

int SDatabase::Prepare(SDatabase* db/*ecx*/)
{
    typedef int(__thiscall* LPFN)(SDatabase*);
    return (*(LPFN)0x4440D0)(db);
}

short SDatabase::Query(SDatabase* db/*ecx*/, const char* query)
{
    typedef short(__thiscall* LPFN)(SDatabase*, const char*);
    return (*(LPFN)0x444C80)(db, query);
}

void SDatabase::WriteErrorLog(SDatabase* db/*ecx*/)
{
    typedef void(__thiscall* LPFN)(SDatabase*);
    (*(LPFN)0x4446B0)(db);
}
