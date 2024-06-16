#pragma once
#include <fstream>
#include <string>

namespace util::io
{
    template<typename T>
    T read(std::ifstream& ifs)
    {
        T data{};
        ifs.read(reinterpret_cast<char*>(&data), sizeof(T));
        return data;
    }

    std::string readString(std::ifstream& ifs, std::size_t length);

    template<typename T>
    std::string readUcsdString(std::ifstream& ifs)
    {
        auto length = read<T>(ifs);
        return readString(ifs, length);
    }

    template<typename T>
    void write(std::ofstream& ofs, T data)
    {
        ofs.write(reinterpret_cast<char*>(&data), sizeof(T));
    }

    void writeString(std::ofstream& ofs, const std::string& str, std::size_t length);

    template<typename T>
    void writeUcsdString(std::ofstream& ofs, const std::string& str)
    {
        auto length = static_cast<T>(str.length() + 1);
        write(ofs, length);
        writeString(ofs, str, length);
    }
}
