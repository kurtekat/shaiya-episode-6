#pragma once
#include <limits>
#include <locale>
#include <string>
#include <vector>

namespace util::string
{
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

    template<class CharT>
    inline std::vector<std::basic_string<CharT>> split(const std::basic_string<CharT>& str, const std::basic_string<CharT>& sep)
    {
        return split(str, sep, std::numeric_limits<size_t>::max());
    }

    template<class CharT>
    inline std::vector<std::basic_string<CharT>> split(const std::basic_string<CharT>& str, CharT sep, size_t count)
    {
        return split(str, std::basic_string<CharT>(1, sep), count);
    }

    template<class CharT>
    inline std::vector<std::basic_string<CharT>> split(const std::basic_string<CharT>& str, CharT sep)
    {
        return split(str, std::basic_string<CharT>(1, sep), std::numeric_limits<size_t>::max());
    }
}
