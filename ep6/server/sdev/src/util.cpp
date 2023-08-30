#include <chrono>
#include <fstream>
#include <string>
#include <msclr/marshal.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/util.h>

using namespace System;

#pragma unmanaged

int util::detour(Address addr, Function func, int size)
{
    constexpr int stmt_size = 5;
    constexpr unsigned char nop = 0x90;
    constexpr unsigned char jmp = 0xE9;

    if (size < stmt_size)
        return 0;

    unsigned long protect;
    if (!VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &protect))
        return 0;

    auto dest = reinterpret_cast<unsigned>(func) - reinterpret_cast<unsigned>(addr);
    dest -= stmt_size;

    memset(addr, nop, size);
    memset(addr, jmp, 1);
    __asm { inc addr }
    memcpy(addr, &dest, 4);
    __asm { dec addr }

    return VirtualProtect(addr, size, protect, &protect);
}

#pragma managed

void util::log(const std::string& text)
{
    auto time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
    std::ofstream ofs("sdev.log.txt", std::ios::app);
    
    if (ofs)
    {
        ofs << std::format("{:%Y-%m-%d %X}\n", time) << text << '\n';
        ofs.close();
    }
}

void util::log(String^ text)
{
    auto time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
    std::ofstream ofs("sdev.log.txt", std::ios::app);
    
    if (ofs)
    {
        ofs << std::format("{:%Y-%m-%d %X}\n", time) << util::marshal_string(text) << '\n';
        ofs.close();
    }
}

std::string util::marshal_string(String^ str)
{
    msclr::interop::marshal_context ctx;
    return ctx.marshal_as<const char*>(str);
}

int util::write_memory(Address addr, Buffer buffer, int size)
{
    if (size < 1)
        return 0;

    unsigned long protect;
    if (!VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &protect))
        return 0;

    if (!WriteProcessMemory(GetCurrentProcess(), addr, buffer, size, nullptr))
        return 0;

    return VirtualProtect(addr, size, protect, &protect);
}
