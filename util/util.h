#pragma once
#include <string>

namespace util
{
    template<class Data>
    Data deserialize(unsigned char* buffer, int offset)
    {
        Data data{};
        std::memcpy(&data, &buffer[offset], sizeof(Data));
        return data;
    }

    int detour(void* addr, void* func, int size);
    int write_memory(void* addr, void* buffer, int size);
    int write_memory(void* addr, int value, int count);
}
