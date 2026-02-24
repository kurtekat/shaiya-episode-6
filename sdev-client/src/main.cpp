#include "include/main.h"
#include "include/shaiya/Configuration.h"
using namespace shaiya;

void Main()
{
    hook::main_stats();
    hook::packet();
    hook::patch();
    Configuration::Init();
}
