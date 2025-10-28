#pragma once
#include <chrono>
#include <cstdint>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace shaiya
{
    /*
        Example:
        2063-12-31 23:59:59

        Encoded:
        4282351355
    */
    class DateTime
    {
    public:

        using value_type = uint32_t;

        static std::chrono::year decode_year(value_type value)
        {
            auto year = ((value >> 26) & 63) + 2000;
            return std::chrono::year(year);
        }

        static std::chrono::month decode_month(value_type value)
        {
            auto month = (value >> 22) & 15;
            return std::chrono::month(month);
        }

        static std::chrono::day decode_day(value_type value)
        {
            auto day = (value >> 17) & 31;
            return std::chrono::day(day);
        }

        static std::chrono::hours decode_hours(value_type value)
        {
            auto hours = (value >> 12) & 31;
            return std::chrono::hours(hours);
        }

        static std::chrono::minutes decode_minutes(value_type value)
        {
            auto minutes = (value >> 6) & 63;
            return std::chrono::minutes(minutes);
        }

        static std::chrono::seconds decode_seconds(value_type value)
        {
            auto seconds = value & 63;
            return std::chrono::seconds(seconds);
        }

        static std::chrono::year_month_day decode_date(value_type value)
        {
            auto year = decode_year(value);
            auto month = decode_month(value);
            auto day = decode_day(value);
            return std::chrono::year_month_day(year / month / day);
        }

        template<class DurationT>
        static std::chrono::hh_mm_ss<DurationT> decode_time(value_type value)
        {
            auto hours = decode_hours(value);
            auto minutes = decode_minutes(value);
            auto seconds = decode_seconds(value);
            return std::chrono::hh_mm_ss<DurationT>(hours + minutes + seconds);
        }

        static value_type encode(int year, unsigned month, unsigned day, int hours, int minutes, int seconds)
        {
            value_type value = year;
            value -= 16;
            value <<= 4;
            value += month;

            value <<= 5;
            value += day;

            value <<= 5;
            value += hours;

            value <<= 6;
            value += minutes;

            value <<= 6;
            value += seconds;
            return value;
        }

        template<class DurationT>
        static value_type encode(const std::chrono::year_month_day& date, const std::chrono::hh_mm_ss<DurationT>& time)
        {
            return encode(date.year(), date.month(), date.day(), time.hours(), time.minutes(), time.seconds());
        }

        static value_type encode(std::chrono::year year, std::chrono::month month, std::chrono::day day, 
            std::chrono::hours hours, std::chrono::minutes minutes, std::chrono::seconds seconds)
        {
            return encode(int(year), unsigned(month), unsigned(day), hours.count(), minutes.count(), int(seconds.count()));
        }

        static value_type encode(const std::tm& tm)
        {
            return encode(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        }

        static value_type encode(time_t tt)
        {
            return encode(std::chrono::system_clock::from_time_t(tt));
        }

        static value_type encode(const std::chrono::system_clock::time_point& tp)
        {
            auto midnight = std::chrono::floor<std::chrono::days>(tp);
            auto date = std::chrono::year_month_day(midnight);
            auto time = std::chrono::hh_mm_ss(tp - midnight);
            return encode(date, time);
        }

        static value_type encode(const SYSTEMTIME& st)
        {
            return encode(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
        }

        static time_t to_time_t(value_type value)
        {
            return std::chrono::system_clock::to_time_t(to_time_point(value));
        }

        static std::chrono::system_clock::time_point to_time_point(value_type value)
        {
            auto date = decode_date(value);
            auto time = decode_time<std::chrono::seconds>(value);
            return std::chrono::sys_days(date) + time.hours() + time.minutes() + time.seconds();
        }
    };
}
