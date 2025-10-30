#include "SDatabase.h"
using namespace shaiya;

short SDatabase::BindParameter(SDatabase* db/*ecx*/, int paramNum, int columSize, int valueType, int paramType, void* data, int* cbBlob, int inoutType)
{
    typedef short(__thiscall* LPFN)(SDatabase*, int, int, int, int, void*, int*, int);
    return (*(LPFN)0x41BE40)(db, paramNum, columSize, valueType, paramType, data, cbBlob, inoutType);
}

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
