#pragma once
#include <ranges>

namespace ext {
namespace ranges {
namespace views {

    template<std::ranges::viewable_range Range>
    inline constexpr auto enumerate_n(Range&& range, std::ranges::range_difference_t<Range> count)
    {
        return std::views::enumerate(range) | std::views::take(count);
    }

    template<class Container, std::ranges::viewable_range Range, class Pattern>
    inline constexpr auto split(Range&& range, Pattern&& pattern)
    {
        return std::ranges::to<Container>(std::views::split(range, pattern));
    }

    template<class Container, std::ranges::viewable_range Range, class Pattern>
    inline constexpr auto split(Range&& range, Pattern&& pattern, std::ranges::range_difference_t<Range> count)
    {
        return std::ranges::to<Container>(
            std::views::split(range, pattern) | std::views::take(count));
    }

} // namespace views
} // namespace ranges

namespace views = ranges::views;

} // namespace ext
