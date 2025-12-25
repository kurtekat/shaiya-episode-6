#include <cstdint>
#include <cstring>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "util.h"

int util::detour(void* addr, void* dest, size_t size)
{
    #pragma pack(push, 1)
    struct {
        uint8_t opcode{ 0xE9 };
        uint32_t operand;
    } insn{};
    #pragma pack(pop)

    static_assert(sizeof(insn) == 5);

    if (size < sizeof(insn))
        return 0;

    unsigned long protect;
    if (!VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &protect))
        return 0;

    auto address = (uintptr_t(dest) - uintptr_t(addr)) - sizeof(insn);
    insn.operand = address;

    std::memset(addr, 0x90, size);
    std::memcpy(addr, &insn, sizeof(insn));
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

int util::write_memory(void* addr, const void* src, size_t size)
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
