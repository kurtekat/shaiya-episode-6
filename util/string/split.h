#pragma once
#include <limits>
#include <locale>
#include <string>
#include <vector>

namespace util
{
    namespace string
    {
        template<class CharT>
        using StringT = std::basic_string<CharT>;

        template<class CharT>
        inline std::vector<StringT<CharT>> split(const StringT<CharT>& str, const StringT<CharT>& sep, size_t count)
        {
            std::vector<StringT<CharT>> tokens;
            if (!count)
                return tokens;

            StringT<CharT> token;
            size_t last = 0;
            size_t next = 0;

            while ((next = str.find(sep, last)) != StringT<CharT>::npos)
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
        inline std::vector<StringT<CharT>> split(const StringT<CharT>& str, const StringT<CharT>& sep)
        {
            return split(str, sep, std::numeric_limits<size_t>::max());
        }

        template<class CharT>
        inline std::vector<StringT<CharT>> split(const StringT<CharT>& str, CharT sep, size_t count)
        {
            return split(str, StringT<CharT>(1, sep), count);
        }

        template<class CharT>
        inline std::vector<StringT<CharT>> split(const StringT<CharT>& str, CharT sep)
        {
            return split(str, StringT<CharT>(1, sep), std::numeric_limits<size_t>::max());
        }
    }
}
