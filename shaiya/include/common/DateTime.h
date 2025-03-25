#pragma once
#include <chrono>
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

        using ulong = unsigned long;

        static std::chrono::year decode_year(ulong value)
        {
            auto year = ((value >> 26) & 63) + 2000;
            return std::chrono::year(year);
        }

        static std::chrono::month decode_month(ulong value)
        {
            auto month = (value >> 22) & 15;
            return std::chrono::month(month);
        }

        static std::chrono::day decode_day(ulong value)
        {
            auto day = (value >> 17) & 31;
            return std::chrono::day(day);
        }

        static std::chrono::hours decode_hours(ulong value)
        {
            auto hours = (value >> 12) & 31;
            return std::chrono::hours(hours);
        }

        static std::chrono::minutes decode_minutes(ulong value)
        {
            auto minutes = (value >> 6) & 63;
            return std::chrono::minutes(minutes);
        }

        static std::chrono::seconds decode_seconds(ulong value)
        {
            auto seconds = value & 63;
            return std::chrono::seconds(seconds);
        }

        static std::chrono::year_month_day decode_date(ulong value)
        {
            auto year = decode_year(value);
            auto month = decode_month(value);
            auto day = decode_day(value);
            return std::chrono::year_month_day(year / month / day);
        }

        template<class Duration>
        static std::chrono::hh_mm_ss<Duration> decode_time(ulong value)
        {
            auto hours = decode_hours(value);
            auto minutes = decode_minutes(value);
            auto seconds = decode_seconds(value);
            return std::chrono::hh_mm_ss<Duration>(hours + minutes + seconds);
        }

        static ulong encode(int year, unsigned month, unsigned day, int hours, int minutes, int seconds)
        {
            ulong value = year;
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

        template<class Duration>
        static ulong encode(const std::chrono::year_month_day& date, const std::chrono::hh_mm_ss<Duration>& time)
        {
            return encode(date.year(), date.month(), date.day(), time.hours(), time.minutes(), time.seconds());
        }

        static ulong encode(std::chrono::year year, std::chrono::month month, std::chrono::day day, 
            std::chrono::hours hours, std::chrono::minutes minutes, std::chrono::seconds seconds)
        {
            return encode(int(year), unsigned(month), unsigned(day), hours.count(), minutes.count(), int(seconds.count()));
        }

        static ulong encode(const SYSTEMTIME& st)
        {
            return encode(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
        }

        static ulong encode(const std::tm& tm)
        {
            return encode(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        }

        static ulong encode(time_t tt)
        {
            return encode(std::chrono::system_clock::from_time_t(tt));
        }

        static ulong encode(const std::chrono::system_clock::time_point& tp)
        {
            auto midnight = std::chrono::floor<std::chrono::days>(tp);
            auto date = std::chrono::year_month_day(midnight);
            auto time = std::chrono::hh_mm_ss(tp - midnight);
            return encode(date, time);
        }

        template<class Duration>
        static ulong encode(const std::chrono::local_time<Duration>& lt)
        {
            auto midnight = std::chrono::floor<std::chrono::days>(lt);
            auto date = std::chrono::year_month_day(midnight);
            auto time = std::chrono::hh_mm_ss(lt - midnight);
            return encode(date, time);
        }

        static time_t to_time_t(ulong value)
        {
            return std::chrono::system_clock::to_time_t(to_time_point(value));
        }

        static std::chrono::system_clock::time_point to_time_point(ulong value)
        {
            auto date = decode_date(value);
            auto time = decode_time<std::chrono::seconds>(value);
            return std::chrono::sys_days(date) + time.hours() + time.minutes() + time.seconds();
        }
    };
}
