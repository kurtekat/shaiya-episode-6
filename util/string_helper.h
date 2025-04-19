#pragma once
#include <sstream>
#include <string>
#include <vector>

namespace util
{
    /// <summary>
    /// Splits a string into a maximum number of substrings based on a specified delimiting character.
    /// </summary>
    template<class CharT>
    std::vector<std::basic_string<CharT>> split(const std::basic_string<CharT>& str, CharT sep, size_t count = SIZE_MAX)
    {
        std::vector<std::basic_string<CharT>> tokens;
        if (!count)
            return tokens;

        std::basic_istringstream<CharT, std::char_traits<CharT>, std::allocator<CharT>> iss(str);
        std::basic_string<CharT> token;

        while (std::getline(iss, token, sep))
        {
            tokens.push_back(token);
            if (tokens.size() == count)
                break;
        }

        return tokens;
    }
}
