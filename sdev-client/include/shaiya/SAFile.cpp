#include "SAFile.h"
using namespace shaiya;

int SAFile::Open(const char* fileName, const char* mode)
{
    typedef int(__cdecl* LPFN)(const char*, const char*);
    return (*(LPFN)0x40D6B0)(fileName, mode);
}

void SAFile::Close(int handle)
{
    typedef void(__cdecl* LPFN)(int);
    (*(LPFN)0x40D2D0)(handle);
}

void SAFile::Read(char* buffer, int elemSize, int elemCount, int handle)
{
    typedef void(__cdecl* LPFN)(char*, int, int, int);
    (*(LPFN)0x40D2A0)(buffer, elemSize, elemCount, handle);
}
