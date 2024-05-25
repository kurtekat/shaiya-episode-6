#include <include/static.h>
using namespace shaiya;

void Static::GetMsg(int type, int line, int unknown)
{
    typedef void(__cdecl* LPFN)(int, int, int);
    (*(LPFN)0x423150)(type, line, unknown);
}
