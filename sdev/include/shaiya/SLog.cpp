#include "SLog.h"
using namespace shaiya;

bool SLog::PrintFileDirect(SLog* log, const char* format, ...)
{
    typedef bool(__cdecl* LPFN)(SLog*, const char*, ...);
    return (*(LPFN)0x4EFDC0)(log, format);
}
