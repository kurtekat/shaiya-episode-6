#pragma once
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>

namespace shaiya
{
    class SBinaryReader final
    {
    public:

        explicit SBinaryReader(const std::filesystem::path& path)
            : m_stream(path, std::ios::binary)
        {
            if (!m_stream)
            {
                throw std::system_error(
                    errno, std::system_category(), path.string());
            }
        }

        SBinaryReader() = delete;
        SBinaryReader(const SBinaryReader&) = delete;
        SBinaryReader& operator=(const SBinaryReader&) = delete;

        SBinaryReader(SBinaryReader&& other) noexcept
        {
            *this = std::move(other);
        }

        SBinaryReader& operator=(SBinaryReader&& other) noexcept
        {
            if (this != &other)
            {
                m_stream = std::move(other.m_stream);
            }

            return *this;
        }

        ~SBinaryReader()
        {
            close();
        }

        /// <summary>
        /// Closes the underlying stream.
        /// </summary>
        void close();

        /// <summary>
        /// Reads the specified number of characters from the stream and discards them.
        /// </summary>
        void ignore(size_t count);

        /// <summary>
        /// Returns the next character and does not advance the stream position.
        /// </summary>
        int peek();

        /// <summary>
        /// Reads the specified number of characters from the stream.
        /// </summary>
        std::string readChars(size_t count);

        /// <summary>
        /// Reads a length-prefixed string from the stream. 
        /// This method first reads the length of the string as a 4-byte unsigned integer, 
        /// and then reads that many characters from the stream.
        /// </summary>
        std::string readString();

        /// <summary>
        /// Reads a 1-byte signed integer from the stream.
        /// </summary>
        int8_t readInt8();

        /// <summary>
        /// Reads a 2-byte signed integer from the stream.
        /// </summary>
        int16_t readInt16();

        /// <summary>
        /// Reads a 4-byte signed integer from the stream.
        /// </summary>
        int32_t readInt32();

        /// <summary>
        /// Reads an 8-byte signed integer from the stream.
        /// </summary>
        int64_t readInt64();

        /// <summary>
        /// Reads a 1-byte unsigned integer from the stream.
        /// </summary>
        uint8_t readUInt8();

        /// <summary>
        /// Reads a 2-byte unsigned integer from the stream.
        /// </summary>
        uint16_t readUInt16();

        /// <summary>
        /// Reads a 4-byte unsigned integer from the stream.
        /// </summary>
        uint32_t readUInt32();

        /// <summary>
        /// Reads an 8-byte unsigned integer from the stream.
        /// </summary>
        uint64_t readUInt64();

        /// <summary>
        /// Reads a 4-byte floating point value from the stream.
        /// </summary>
        float readSingle();

        /// <summary>
        /// Reads an 8-byte floating point value from the stream.
        /// </summary>
        double readDouble();

    private:

        std::ifstream m_stream;
    };
}
