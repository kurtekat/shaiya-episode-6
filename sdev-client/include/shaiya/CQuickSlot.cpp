#include "CQuickSlot.h"
using namespace shaiya;

CQuickSlot* CQuickSlot::Create(void* block, int id)
{
    typedef CQuickSlot* (__thiscall* LPFN)(void*, int);
    return (*(LPFN)0x4FE4A0)(block, id);
}

int CQuickSlot::BagToBag(CQuickSlot* quickSlot, int bag, int slot)
{
    typedef int(__thiscall* LPFN)(CQuickSlot*, int, int);
    return (*(LPFN)0x4FDFA0)(quickSlot, bag, slot);
}

CQuickSlot* CQuickSlot::Reset(CQuickSlot* quickSlot, bool free)
{
    typedef CQuickSlot* (__thiscall* LPFN)(CQuickSlot*, bool);
    return (*(LPFN)0x4FE710)(quickSlot, free);
}
