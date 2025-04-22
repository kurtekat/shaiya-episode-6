#pragma once
#include <limits>
#include <locale>
#include <string>
#include <vector>

namespace util
{
    /// <summary>
    /// Splits a string into a maximum number of substrings based on a specified delimiting string.
    /// </summary>
    template<class CharT>
    std::vector<std::basic_string<CharT>> split(const std::basic_string<CharT>& str, const std::basic_string<CharT>& sep, size_t count)
    {
        std::vector<std::basic_string<CharT>> tokens;
        if (!count)
            return tokens;

        std::basic_string<CharT> token;
        size_t last = 0;
        size_t next = 0;

        while ((next = str.find(sep, last)) != std::basic_string<CharT>::npos)
        {
            token = str.substr(last, next - last);
            tokens.push_back(token);

            if (tokens.size() == count)
                return tokens;

            last = next + sep.length();
        }

        tokens.push_back(str.substr(last));
        return tokens;
    }

    /// <summary>
    /// Splits a string into substrings based on a specified delimiting string.
    /// </summary>
    template<class CharT>
    std::vector<std::basic_string<CharT>> split(const std::basic_string<CharT>& str, const std::basic_string<CharT>& sep)
    {
        return split(str, sep, std::numeric_limits<size_t>::max());
    }

    /// <summary>
    /// Splits a string into a maximum number of substrings based on a specified delimiting character.
    /// </summary>
    template<class CharT>
    std::vector<std::basic_string<CharT>> split(const std::basic_string<CharT>& str, CharT sep, size_t count)
    {
        return split(str, std::basic_string<CharT>(1, sep), count);
    }

    /// <summary>
    /// Splits a string into substrings based on a specified delimiting character.
    /// </summary>
    template<class CharT>
    std::vector<std::basic_string<CharT>> split(const std::basic_string<CharT>& str, CharT sep)
    {
        return split(str, std::basic_string<CharT>(1, sep), std::numeric_limits<size_t>::max());
    }

    /// <summary>
    /// Removes all the leading white-space characters from the specified string.
    /// </summary>
    template<class CharT>
    std::basic_string<CharT> trim_start(const std::basic_string<CharT>& str, const std::locale& loc = std::locale())
    {
        auto it = str.cbegin();
        while (it != str.cend() && std::isspace(*it, loc))
            ++it;

        auto offset = std::distance(str.cbegin(), it);
        return str.substr(offset);
    }

    /// <summary>
    /// Removes all the trailing white-space characters from the specified string.
    /// </summary>
    template<class CharT>
    std::basic_string<CharT> trim_end(const std::basic_string<CharT>& str, const std::locale& loc = std::locale())
    {
        auto it = str.crbegin();
        while (it != str.crend() && std::isspace(*it, loc))
            ++it;

        auto count = std::distance(it, str.crend());
        return str.substr(0, count);
    }

    /// <summary>
    /// Removes all leading and trailing white-space characters from the specified string.
    /// </summary>
    template<class CharT>
    std::basic_string<CharT> trim(const std::basic_string<CharT>& str, const std::locale& loc = std::locale())
    {
        return trim_start(trim_end(str, loc), loc);
    }
}
