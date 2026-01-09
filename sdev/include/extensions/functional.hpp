#pragma once
#include <string>

namespace ext {

    template<class T>
    struct unary_equal_to
    {
        explicit unary_equal_to(const T& rhs)
            : m_rhs(rhs)
        {
        }

        bool operator()(const T& lhs) const
        {
            return lhs == m_rhs;
        }

    private:

        T m_rhs;
    };

    struct string_to_int
    {
        explicit string_to_int(int base = 10)
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

} // namespace ext
