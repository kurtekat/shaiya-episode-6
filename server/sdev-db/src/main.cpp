#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <sdev/include/shaiya/common.h>

void Main()
{
    #ifdef SHAIYA_EP6_4_PT
    hook::character_create();
    #endif
    hook::character_list();
}
