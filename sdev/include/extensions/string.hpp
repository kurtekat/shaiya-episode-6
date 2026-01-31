#pragma once
#include <limits>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>
#include "type_traits.hpp"

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
