#pragma once
#include <string>

namespace util
{
    typedef void* Address;
    typedef void* Buffer;
    typedef void* Function;

    template<class Data>
    Data deserialize(std::uint8_t* buffer, int offset)
    {
        Data data{};
        std::memcpy(&data, &buffer[offset], sizeof(Data));
        return data;
    }

    int detour(Address addr, Function func, std::size_t size);
    void log(const std::string& text);
    int write_memory(Address addr, Buffer buffer, std::size_t size);
    int write_memory(Address addr, int value, std::size_t size);
}
