#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/main.h>
#include <include/util.h>

void Main()
{
    hook::gui();
    hook::item();
    hook::packet();
}
