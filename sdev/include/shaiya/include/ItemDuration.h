#pragma once
#include <chrono>
#include <shaiya/include/common.h>

namespace shaiya
{
    class ItemDuration
    {
    public:

        int days;
        int hours;
        int minutes;

        ItemDuration(time_t expireTime)
            : days(0), hours(0), minutes(0)
        {
            auto tp = std::chrono::system_clock::from_time_t(expireTime);
            auto duration = tp - std::chrono::system_clock::now();

            days = std::chrono::duration_cast<std::chrono::days>(duration).count();
            hours = std::chrono::duration_cast<std::chrono::hours>(duration).count();
            minutes = std::chrono::duration_cast<std::chrono::minutes>(duration).count();

            days = (days < 0) ? 0 : days;
            hours = (hours < 0) ? 0 : hours;
            minutes = (minutes < 0) ? 0 : minutes;
        }

        constexpr bool expired() const
        {
            return !days && !hours && !minutes;
        }
    };
}
