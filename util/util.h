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
    int write_memory(void* addr, void* buffer, int size);
    int write_memory(void* addr, int value, int count);
}
