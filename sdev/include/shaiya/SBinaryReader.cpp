#include <cstddef>
#include <cstdint>
#include <fstream>
#include <string>
#include "SBinaryReader.h"
using namespace shaiya;

void SBinaryReader::close()
{
    if (!m_stream)
        return;

    if (m_stream.is_open())
        m_stream.close();
}

void SBinaryReader::ignore(size_t count)
{
    m_stream.ignore(count);
}

int SBinaryReader::peek()
{
    return m_stream.peek();
}

std::string SBinaryReader::readChars(size_t count)
{
    std::string buffer(count, 0);
    m_stream.read(buffer.data(), buffer.size());
    return buffer;
}

std::string SBinaryReader::readString()
{
    uint32_t count{};
    m_stream.read(reinterpret_cast<char*>(&count), 4);

    std::string buffer(count, 0);
    m_stream.read(buffer.data(), buffer.size());
    return buffer;
}

int8_t SBinaryReader::readInt8()
{
    int8_t value{};
    m_stream.read(reinterpret_cast<char*>(&value), 1);
    return value;
}

int16_t SBinaryReader::readInt16()
{
    int16_t value{};
    m_stream.read(reinterpret_cast<char*>(&value), 2);
    return value;
}

int32_t SBinaryReader::readInt32()
{
    int32_t value{};
    m_stream.read(reinterpret_cast<char*>(&value), 4);
    return value;
}

int64_t SBinaryReader::readInt64()
{
    int64_t value{};
    m_stream.read(reinterpret_cast<char*>(&value), 8);
    return value;
}

uint8_t SBinaryReader::readUInt8()
{
    uint8_t value{};
    m_stream.read(reinterpret_cast<char*>(&value), 1);
    return value;
}

uint16_t SBinaryReader::readUInt16()
{
    uint16_t value{};
    m_stream.read(reinterpret_cast<char*>(&value), 2);
    return value;
}

uint32_t SBinaryReader::readUInt32()
{
    uint32_t value{};
    m_stream.read(reinterpret_cast<char*>(&value), 4);
    return value;
}

uint64_t SBinaryReader::readUInt64()
{
    uint64_t value{};
    m_stream.read(reinterpret_cast<char*>(&value), 8);
    return value;
}

float SBinaryReader::readSingle()
{
    float value{};
    m_stream.read(reinterpret_cast<char*>(&value), 4);
    return value;
}

double SBinaryReader::readDouble()
{
    double value{};
    m_stream.read(reinterpret_cast<char*>(&value), 8);
    return value;
}
