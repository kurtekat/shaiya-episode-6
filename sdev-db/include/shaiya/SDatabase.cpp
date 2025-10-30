#include "SDatabase.h"
using namespace shaiya;

short SDatabase::BindParameter(SDatabase* db/*ecx*/, int paramNum, int columSize, int valueType, int paramType, void* data, int* cbBlob, int inoutType)
{
    typedef short(__thiscall* LPFN)(SDatabase*, int, int, int, int, void*, int*, int);
    return (*(LPFN)0x444D40)(db, paramNum, columSize, valueType, paramType, data, cbBlob, inoutType);
}

short SDatabase::CountRow(SDatabase* db/*ecx*/, int* rows)
{
    typedef short(__thiscall* LPFN)(SDatabase*, int*);
    return (*(LPFN)0x4442B0)(db, rows);
}

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
