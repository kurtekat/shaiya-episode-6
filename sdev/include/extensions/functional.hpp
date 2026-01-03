#pragma once

namespace ext {

    template<class T>
    struct unary_equal_to
    {
        explicit unary_equal_to(const T& rhs)
            : m_rhs(rhs)
        {
        }

        bool operator()(const T& lhs)
        {
            return lhs == m_rhs;
        }

    private:

        T m_rhs;
    };

} // namespace ext
