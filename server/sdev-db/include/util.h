#pragma once
#include <fstream>
#include <string>

namespace util
{
    typedef void* Address;
    typedef void* Buffer;
    typedef unsigned char* ByteArray;
    typedef void* Function;

    int detour(Address addr, Function func, std::size_t size);
    void log(const std::string& text);

    template<class T>
    auto read_bytes(ByteArray buffer, int offset)
    {
        T value{};
        std::memcpy(&value, &buffer[offset], sizeof(T));
        return value;
    }

    int write_memory(Address addr, Buffer buffer, std::size_t size);
}
