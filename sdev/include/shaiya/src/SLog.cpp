#include <shaiya/include/SLog.h>
using namespace shaiya;

bool SLog::PrintFileDirect(SLog* log, const char* fmt, ...)
{
    typedef bool(__cdecl* LPFN)(SLog*, const char*, ...);
    return (*(LPFN)0x4EFDC0)(log, fmt);
}
