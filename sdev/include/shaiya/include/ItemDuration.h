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

        ItemDuration(time_t toDate)
            : days(0), hours(0), minutes(0)
        {
            using namespace std::chrono;

            auto tp = current_zone()->to_local(system_clock::from_time_t(toDate));
            auto now = current_zone()->to_local(system_clock::now());

            if (tp <= now)
                return;

            auto duration = tp - now;
            this->days = duration_cast<std::chrono::days>(duration).count();
            this->hours = duration_cast<std::chrono::hours>(duration).count();
            this->minutes = duration_cast<std::chrono::minutes>(duration).count();
        }

        constexpr bool expired() const
        {
            return !days && !hours && !minutes;
        }
    };
}
