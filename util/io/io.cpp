#include <fstream>
#include <string>
#include <vector>
#include "io.h"

std::string util::io::readString(std::ifstream& ifs, std::size_t length)
{
    std::string str(length, 0);
    ifs.read(str.data(), str.size());
    return str;
}

void util::io::writeString(std::ofstream& ofs, const std::string& str, std::size_t length)
{
    ofs.write(str.c_str(), length);
}
