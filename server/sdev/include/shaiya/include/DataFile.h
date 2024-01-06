#pragma once
#include <fstream>
#include <string>

namespace shaiya
{
    struct DataFile
    {
        using LengthPrefix = std::uint_least32_t;

        template<class Data>
        static Data readNumber(std::ifstream& ifs)
        {
            Data data{};
            ifs.read(reinterpret_cast<char*>(&data), sizeof(Data));
            return data;
        }

        static std::string readPascalString(std::ifstream& ifs);
        static std::string readString(std::ifstream& ifs, std::size_t size);

        template<class Data>
        static void writeNumber(std::ofstream& ofs, Data data)
        {
            ofs.write(reinterpret_cast<char*>(&data), sizeof(Data));
        }

        static void writePascalString(std::ofstream& ofs, const std::string& str);
        static void writeString(std::ofstream& ofs, const std::string& str, std::size_t size);
    };
}
