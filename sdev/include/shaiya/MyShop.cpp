#include "MyShop.h"
using namespace shaiya;

void MyShop::Ended(MyShop* myShop)
{
    typedef void(__thiscall* LPFN)(MyShop*);
    (*(LPFN)0x487030)(myShop);
}
