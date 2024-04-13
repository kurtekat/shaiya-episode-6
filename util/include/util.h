#pragma once

namespace util
{
    typedef void* Address;
    typedef void* Buffer;
    typedef unsigned char Byte;
    typedef void* Function;

    template<class Data>
    Data deserialize(Byte* buffer, int offset)
    {
        Data data{};
        memcpy(&data, &buffer[offset], sizeof(Data));
        return data;
    }

    int detour(Address addr, Function func, int size);
    int write_memory(Address addr, Buffer buffer, int size);
    int write_memory(Address addr, Byte value, int count);
}
