#include <include/shaiya/include/SDatabase.h>
using namespace shaiya;

int SDatabase::Prepare(SDatabase* db/*ecx*/)
{
    typedef int(__thiscall* LPFN)(SDatabase*);
    return (*(LPFN)0x4F8040)(db);
}

void SDatabase::WriteErrorLog(SDatabase* db/*ecx*/)
{
    typedef void(__thiscall* LPFN)(SDatabase*);
    (*(LPFN)0x4F8620)(db);
}
