#pragma once
#include <algorithm>
#include <limits>
#include <locale>
#include <string>
#include <vector>

namespace util::string
{
    /// <summary>
    /// Compares two strings, ignoring case.
    /// </summary>
    template<class CharT>
    inline int ilexicographical_compare(const std::basic_string<CharT>& lhs, const std::basic_string<CharT>& rhs, const std::locale& loc = std::locale())
    {
        auto result = std::lexicographical_compare_three_way(
            lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend(), [&loc](CharT lc, CharT rc) {
                return std::toupper<CharT>(lc, loc) <=> std::toupper<CharT>(rc, loc);
            });

        return std::is_lt(result) ? -1 : std::is_gt(result) ? 1 : 0;
    }

    /// <summary>
    /// Splits a string into a maximum number of substrings based on a specified delimiting string.
    /// </summary>
    template<class CharT>
    inline std::vector<std::basic_string<CharT>> split(const std::basic_string<CharT>& str, const std::basic_string<CharT>& sep, size_t count)
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
    inline std::vector<std::basic_string<CharT>> split(const std::basic_string<CharT>& str, const std::basic_string<CharT>& sep)
    {
        return split(str, sep, std::numeric_limits<size_t>::max());
    }

    /// <summary>
    /// Splits a string into a maximum number of substrings based on a specified delimiting character.
    /// </summary>
    template<class CharT>
    inline std::vector<std::basic_string<CharT>> split(const std::basic_string<CharT>& str, CharT sep, size_t count)
    {
        return split(str, std::basic_string<CharT>(1, sep), count);
    }

    /// <summary>
    /// Splits a string into substrings based on a specified delimiting character.
    /// </summary>
    template<class CharT>
    inline std::vector<std::basic_string<CharT>> split(const std::basic_string<CharT>& str, CharT sep)
    {
        return split(str, std::basic_string<CharT>(1, sep), std::numeric_limits<size_t>::max());
    }

    /// <summary>
    /// Returns a copy of the specified string converted to lowercase.
    /// </summary>
    template<class CharT>
    inline std::basic_string<CharT> to_lower(const std::basic_string<CharT>& str, const std::locale& loc = std::locale())
    {
        std::basic_string<CharT> result(str);
        std::transform(result.begin(), result.end(), result.begin(), [&loc](CharT c) {
            return std::tolower<CharT>(c, loc);
            });

        return result;
    }

    /// <summary>
    /// Returns a copy of the specified string converted to uppercase.
    /// </summary>
    template<class CharT>
    inline std::basic_string<CharT> to_upper(const std::basic_string<CharT>& str, const std::locale& loc = std::locale())
    {
        std::basic_string<CharT> result(str);
        std::transform(result.begin(), result.end(), result.begin(), [&loc](CharT c) {
            return std::toupper<CharT>(c, loc);
            });

        return result;
    }

    /// <summary>
    /// Removes all the trailing white-space characters from the specified string.
    /// </summary>
    template<class CharT>
    inline std::basic_string<CharT> trim_end(const std::basic_string<CharT>& str, const std::locale& loc = std::locale())
    {
        auto length = str.length();
        if (!length)
            return str;

        auto it = str.crbegin();
        while (it != str.crend() && std::isspace(*it, loc))
            ++it;

        auto offset = std::distance(str.crbegin(), it);
        return str.substr(0, length - offset);
    }

    /// <summary>
    /// Removes all the leading white-space characters from the specified string.
    /// </summary>
    template<class CharT>
    inline std::basic_string<CharT> trim_start(const std::basic_string<CharT>& str, const std::locale& loc = std::locale())
    {
        if (str.empty())
            return str;

        auto it = str.cbegin();
        while (it != str.cend() && std::isspace(*it, loc))
            ++it;

        auto offset = std::distance(str.cbegin(), it);
        return str.substr(offset);
    }

    /// <summary>
    /// Removes all leading and trailing white-space characters from the specified string.
    /// </summary>
    template<class CharT>
    inline std::basic_string<CharT> trim(const std::basic_string<CharT>& str, const std::locale& loc = std::locale())
    {
        if (str.empty())
            return str;

        return trim_start(trim_end(str, loc), loc);
    }
}
