#pragma once
#include <ranges>

namespace ext {
    namespace ranges {
        namespace views {

            template<std::ranges::viewable_range Range, class N>
            inline constexpr auto enumerate_n(Range&& range, const N count)
            {
                return std::views::enumerate(range) | std::views::take(count);
            }

            template<class Container, std::ranges::viewable_range Range, class Pattern>
            inline constexpr auto split(Range&& range, Pattern&& pattern)
            {
                return std::ranges::to<Container>(std::views::split(range, pattern));
            }

        } // namespace views
    } // namespace ranges

    namespace views = ranges::views;

} // namespace ext
