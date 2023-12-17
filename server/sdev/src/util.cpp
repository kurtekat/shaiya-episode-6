#include <chrono>
#include <fstream>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <include/util.h>

int util::detour(Address addr, Function func, std::size_t size)
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

    std::memset(addr, nop, size);
    std::memset(addr, jmp, 1);
    __asm { inc addr }
    std::memcpy(addr, &dest, 4);
    __asm { dec addr }

    return VirtualProtect(addr, size, protect, &protect);
}

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

std::string util::read_pascal_string(std::ifstream& ifs)
{
    auto size = util::read_number<LengthPrefix>(ifs);
    return util::read_string(ifs, size);
}

std::string util::read_string(std::ifstream& ifs, std::size_t size)
{
    std::string str(size, 0);
    ifs.read(str.data(), str.size());
    return str;
}

int util::write_memory(Address addr, Buffer buffer, std::size_t size)
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
