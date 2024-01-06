#include <fstream>
#include <string>

#include <include/shaiya/include/DataFile.h>
using namespace shaiya;

std::string DataFile::readPascalString(std::ifstream& ifs)
{
    auto size = readNumber<LengthPrefix>(ifs);
    return readString(ifs, size);
}

std::string DataFile::readString(std::ifstream& ifs, std::size_t size)
{
    std::string str(size, 0);
    ifs.read(str.data(), str.size());
    return str;
}

void DataFile::writePascalString(std::ofstream & ofs, const std::string & str)
{
    auto size = static_cast<LengthPrefix>(str.length() + 1);
    writeNumber(ofs, size);
    writeString(ofs, str, size);
}

void DataFile::writeString(std::ofstream& ofs, const std::string& str, std::size_t size)
{
    ofs.write(str.c_str(), size);
}
