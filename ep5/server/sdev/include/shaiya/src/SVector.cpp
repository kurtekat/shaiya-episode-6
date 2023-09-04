#include <shaiya/include/SVector.h>
using namespace shaiya;

double SVector::Distance2(SVector* pos1/*ecx*/, SVector* pos2/*eax*/)
{
    Address u0x41B8C0 = 0x41B8C0;

    __asm
    {
        mov eax,pos2
        mov ecx,pos1
        call u0x41B8C0
    }
}
