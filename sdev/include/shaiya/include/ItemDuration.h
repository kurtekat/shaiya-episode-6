#pragma once
#include <chrono>
#include <shaiya/include/common.h>

namespace shaiya
{
    class ItemDuration
    {
    public:

        std::chrono::seconds seconds;

        ItemDuration(time_t toDate)
            : seconds(0)
        {
            using namespace std::chrono;

            auto tp = current_zone()->to_local(system_clock::from_time_t(toDate));
            auto now = current_zone()->to_local(system_clock::now());

            if (tp <= now)
                return;

            auto duration = tp - now;
            this->seconds = duration_cast<std::chrono::seconds>(duration);
        }

        constexpr bool expired() const noexcept
        {
            return !seconds.count();
        }

        constexpr std::chrono::days days() const noexcept
        {
            return duration_cast<std::chrono::days>(this->seconds);
        }

        constexpr std::chrono::hours hours() const noexcept
        {
            return duration_cast<std::chrono::hours>(this->seconds);
        }

        constexpr std::chrono::minutes minutes() const noexcept
        {
            return duration_cast<std::chrono::minutes>(this->seconds);
        }
    };
}
