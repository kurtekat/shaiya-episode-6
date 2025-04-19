#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "util.h"

int util::detour(void* addr, void* func, size_t size)
{
    constexpr int nop = 0x90;
    constexpr int jmp = 0xE9;
    auto dest = (unsigned(func) - unsigned(addr)) - 5;

    if (size < 5)
        return 0;

    unsigned long protect;
    if (!VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &protect))
        return 0;

    std::memset(addr, nop, size);
    std::memset(addr, jmp, 1);
    __asm { inc addr }
    std::memcpy(addr, &dest, 4);
    __asm { dec addr }

    return VirtualProtect(addr, size, protect, &protect);
}

int util::read_memory(void* addr, void* dest, size_t size)
{
    if (size < 1)
        return 0;

    unsigned long protect;
    if (!VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &protect))
        return 0;

    if (!ReadProcessMemory(GetCurrentProcess(), addr, dest, size, nullptr))
        return 0;

    return VirtualProtect(addr, size, protect, &protect);
}

int util::write_memory(void* addr, void* src, size_t size)
{
    if (size < 1)
        return 0;

    unsigned long protect;
    if (!VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &protect))
        return 0;

    if (!WriteProcessMemory(GetCurrentProcess(), addr, src, size, nullptr))
        return 0;

    return VirtualProtect(addr, size, protect, &protect);
}

int util::write_memory(void* addr, int value, size_t size)
{
    if (size < 1)
        return 0;

    unsigned long protect;
    if (!VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &protect))
        return 0;

    std::memset(addr, value, size);
    return VirtualProtect(addr, size, protect, &protect);
}
