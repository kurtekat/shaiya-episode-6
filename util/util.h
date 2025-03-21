#pragma once
#include <string>
#include <vector>

namespace util
{
    template<typename T>
    T deserialize(uint8_t* buffer, size_t offset)
    {
        T data{};
        std::memcpy(&data, &buffer[offset], sizeof(T));
        return data;
    }
    
    int detour(void* addr, void* func, size_t size);
    int read_memory(void* addr, void* dest, size_t size);
    int write_memory(void* addr, void* src, size_t size);
    int write_memory(void* addr, int value, size_t size);

    std::vector<std::string> split(const std::string& str, char sep, size_t count = SIZE_MAX);
    std::vector<std::wstring> split(const std::wstring& str, wchar_t sep, size_t count = SIZE_MAX);
    
    std::string wcstos(const std::wstring& str);
    std::wstring stowcs(const std::string& str);
}
