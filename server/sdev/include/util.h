#pragma once
#include <fstream>
#include <string>

namespace util
{
    typedef void* Address;
    typedef void* Buffer;
    typedef unsigned char* ByteArray;
    typedef void* Function;
    typedef unsigned int LengthPrefix;

    int detour(Address addr, Function func, std::size_t size);
    void log(const std::string& text);

    template<class T>
    auto read_bytes(ByteArray buffer, int offset)
    {
        T value{};
        std::memcpy(&value, &buffer[offset], sizeof(T));
        return value;
    }

    template<class T>
    T read_number(std::ifstream& ifs)
    {
        T value{};
        ifs.read(reinterpret_cast<char*>(&value), sizeof(T));
        return value;
    }

    std::string read_pascal_string(std::ifstream& ifs);
    std::string read_string(std::ifstream& ifs, std::size_t size);
    int write_memory(Address addr, Buffer buffer, std::size_t size);
}
