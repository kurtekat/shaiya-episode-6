#pragma once
#include <algorithm>
#include <limits>
#include <locale>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>
#include "type_traits.hpp"

namespace ext {
namespace string {
namespace detail {

    template<class Char>
    struct equal_to
    {
        explicit equal_to(const Char rhs)
            : m_rhs(rhs)
        {
        }

        constexpr bool operator()(const Char lhs) const
        {
            return std::char_traits<Char>::eq(lhs, m_rhs);
        }

    private:

        Char m_rhs;
    };

    template<class Char>
    struct equal_to_any_of
    {
        explicit equal_to_any_of(const std::basic_string_view<Char> sv)
            : m_sv(sv)
        {
        }

        bool operator()(const Char ch) const
        {
            return std::any_of(
                std::cbegin(m_sv), std::cend(m_sv), equal_to(ch));
        }

    private:

        std::basic_string_view<Char> m_sv;
    };

    struct is_space
    {
        explicit is_space(const std::locale& loc = std::locale())
            : m_loc(loc)
        {
        }

        template<class Char>
        bool operator()(const Char lhs) const
        {
            return std::isspace<Char>(lhs, m_loc);
        }

    private:

        std::locale m_loc;
    };

} // namespace detail
} // namespace string
} // namespace ext

namespace ext {
namespace string {

    struct to_int
    {
        explicit to_int(int base = 10)
            : m_base(base)
        {
        }

        int operator()(const std::string& str) const
        {
            return std::stoi(str, nullptr, m_base);
        }

        int operator()(const std::wstring& str) const
        {
            return std::stoi(str, nullptr, m_base);
        }

    private:

        int m_base;
    };

} // namespace string
} // namespace ext

namespace ext {
namespace string {

    template<class Char, class UnaryPred>
    inline void ltrim_if(std::basic_string<Char>& str, UnaryPred pred)
    {
        str.erase(
            std::begin(str),
            std::find_if_not(std::begin(str), std::end(str), pred));
    }

    template<class Char, class UnaryPred>
    inline void rtrim_if(std::basic_string<Char>& str, UnaryPred pred)
    {
        str.erase(
            std::find_if_not(std::rbegin(str), std::rend(str), pred).base(),
            std::end(str));
    }

    template<class Char, class UnaryPred>
    inline void trim_if(std::basic_string<Char>& str, UnaryPred pred)
    {
        rtrim_if(str, pred);
        ltrim_if(str, pred);
    }

    template<class Char>
    inline void ltrim(std::basic_string<Char>& str, const std::locale& loc = std::locale())
    {
        ltrim_if(str, detail::is_space(loc));
    }

    template<class Char>
    inline void ltrim(std::basic_string<Char>& str, const Char rhs)
    {
        ltrim_if(str, detail::equal_to(rhs));
    }

    template<class Char>
    inline void ltrim(std::basic_string<Char>& str, const Char* const rhs)
    {
        ltrim_if(str, detail::equal_to_any_of(std::basic_string_view(rhs)));
    }

    template<class Char>
    inline void ltrim(std::basic_string<Char>& str, const std::basic_string_view<non_deduced_t<Char>> rhs)
    {
        ltrim_if(str, detail::equal_to_any_of(rhs));
    }

    template<class Char>
    inline void rtrim(std::basic_string<Char>& str, const std::locale& loc = std::locale())
    {
        rtrim_if(str, detail::is_space(loc));
    }

    template<class Char>
    inline void rtrim(std::basic_string<Char>& str, const Char rhs)
    {
        rtrim_if(str, detail::equal_to(rhs));
    }

    template<class Char>
    inline void rtrim(std::basic_string<Char>& str, const Char* const rhs)
    {
        rtrim_if(str, detail::equal_to_any_of(std::basic_string_view(rhs)));
    }

    template<class Char>
    inline void rtrim(std::basic_string<Char>& str, const std::basic_string_view<non_deduced_t<Char>> rhs)
    {
        rtrim_if(str, detail::equal_to_any_of(rhs));
    }

    template<class Char>
    inline void trim(std::basic_string<Char>& str, const std::locale& loc = std::locale())
    {
        trim_if(str, detail::is_space(loc));
    }

    template<class Char>
    inline void trim(std::basic_string<Char>& str, const Char rhs)
    {
        trim_if(str, detail::equal_to(rhs));
    }

    template<class Char>
    inline void trim(std::basic_string<Char>& str, const Char* const rhs)
    {
        trim_if(str, detail::equal_to_any_of(std::basic_string_view(rhs)));
    }

    template<class Char>
    inline void trim(std::basic_string<Char>& str, const std::basic_string_view<non_deduced_t<Char>> rhs)
    {
        trim_if(str, detail::equal_to_any_of(rhs));
    }

    template<class Char, class UnaryPred>
    inline auto ltrim_copy_if(const std::basic_string<Char>& str, UnaryPred pred)
    {
        std::basic_string<Char> output(str);
        ltrim_if(output, pred);
        return output;
    }

    template<class Char, class UnaryPred>
    inline auto rtrim_copy_if(const std::basic_string<Char>& str, UnaryPred pred)
    {
        std::basic_string<Char> output(str);
        rtrim_if(output, pred);
        return output;
    }

    template<class Char, class UnaryPred>
    inline auto trim_copy_if(const std::basic_string<Char>& str, UnaryPred pred)
    {
        std::basic_string<Char> output(str);
        rtrim_if(output, pred);
        ltrim_if(output, pred);
        return output;
    }

    template<class Char>
    inline auto ltrim_copy(const std::basic_string<Char>& str, const std::locale& loc = std::locale())
    {
        return ltrim_copy_if(str, detail::is_space(loc));
    }

    template<class Char>
    inline auto ltrim_copy(const std::basic_string<Char>& str, const Char rhs)
    {
        return ltrim_copy_if(str, detail::equal_to(rhs));
    }

    template<class Char>
    inline auto ltrim_copy(const std::basic_string<Char>& str, const Char* const rhs)
    {
        return ltrim_copy_if(str, detail::equal_to_any_of(std::basic_string_view(rhs)));
    }

    template<class Char>
    inline auto ltrim_copy(const std::basic_string<Char>& str, const std::basic_string_view<non_deduced_t<Char>> rhs)
    {
        return ltrim_copy_if(str, detail::equal_to_any_of(rhs));
    }

    template<class Char>
    inline auto rtrim_copy(const std::basic_string<Char>& str, const std::locale& loc = std::locale())
    {
        return rtrim_copy_if(str, detail::is_space(loc));
    }

    template<class Char>
    inline auto rtrim_copy(const std::basic_string<Char>& str, const Char rhs)
    {
        return rtrim_copy_if(str, detail::equal_to(rhs));
    }

    template<class Char>
    inline auto rtrim_copy(const std::basic_string<Char>& str, const Char* const rhs)
    {
        return rtrim_copy_if(str, detail::equal_to_any_of(std::basic_string_view(rhs)));
    }

    template<class Char>
    inline auto rtrim_copy(const std::basic_string<Char>& str, const std::basic_string_view<non_deduced_t<Char>> rhs)
    {
        return rtrim_copy_if(str, detail::equal_to_any_of(rhs));
    }

    template<class Char>
    inline auto trim_copy(const std::basic_string<Char>& str, const std::locale& loc = std::locale())
    {
        return trim_copy_if(str, detail::is_space(loc));
    }

    template<class Char>
    inline auto trim_copy(const std::basic_string<Char>& str, const Char rhs)
    {
        return trim_copy_if(str, detail::equal_to(rhs));
    }

    template<class Char>
    inline auto trim_copy(const std::basic_string<Char>& str, const Char* const rhs)
    {
        return trim_copy_if(str, detail::equal_to_any_of(std::basic_string_view(rhs)));
    }

    template<class Char>
    inline auto trim_copy(const std::basic_string<Char>& str, const std::basic_string_view<non_deduced_t<Char>> rhs)
    {
        return trim_copy_if(str, detail::equal_to_any_of(rhs));
    }

} // namespace string
} // namespace ext

namespace ext {
namespace string {

    template<class Char>
    inline auto split(const std::basic_string<Char>& str, const std::basic_string_view<non_deduced_t<Char>> sep, int max)
    {
        auto view = std::views::split(str, sep) | std::views::take(max);
        std::vector<std::basic_string<Char>> output;

        for (const auto& range : view)
        {
            output.push_back({ std::begin(range), std::end(range) });
        }

        return output;
    }

    template<class Char>
    inline auto split(const std::basic_string<Char>& str, const std::basic_string_view<non_deduced_t<Char>> sep)
    {
        return split(str, sep, std::numeric_limits<int>::max());
    }

    template<class Char>
    inline auto split(const std::basic_string<Char>& str, const Char sep, int max)
    {
        return split(str, std::basic_string(1, sep), max);
    }

    template<class Char>
    inline auto split(const std::basic_string<Char>& str, const Char sep)
    {
        return split(str, std::basic_string(1, sep), std::numeric_limits<int>::max());
    }

    template<class Char>
    inline auto split(const std::basic_string<Char>& str, const Char* const sep, int max)
    {
        return split(str, std::basic_string_view(sep), max);
    }

    template<class Char>
    inline auto split(const std::basic_string<Char>& str, const Char* const sep)
    {
        return split(str, std::basic_string_view(sep), std::numeric_limits<int>::max());
    }

} // namespace string
} // namespace ext
