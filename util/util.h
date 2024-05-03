#pragma once
#include <string>

namespace util
{
    template<typename T>
    T deserialize(unsigned char* buffer, int offset)
    {
        T data{};
        std::memcpy(&data, &buffer[offset], sizeof(T));
        return data;
    }
    
    int detour(void* addr, void* func, int size);
    int read_memory(void* addr, void* dest, int size);
    int write_memory(void* addr, void* src, int size);
    int write_memory(void* addr, int value, int count);
}
