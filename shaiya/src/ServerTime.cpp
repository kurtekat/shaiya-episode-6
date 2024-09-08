#include <chrono>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shaiya/include/ServerTime.h>
using namespace shaiya;

std::chrono::year ServerTime::year() const
{
    auto value = this->timestamp;
    value >>= 26;
    value &= 63;
    value += 2000;
    return std::chrono::year(value);
}

std::chrono::month ServerTime::month() const
{
    auto value = this->timestamp;
    value >>= 22;
    value &= 15;
    return std::chrono::month(value);
}

std::chrono::day ServerTime::day() const
{
    auto value = this->timestamp;
    value >>= 17;
    value &= 31;
    return std::chrono::day(value);
}

std::chrono::hours ServerTime::hours() const
{
    auto value = this->timestamp;
    value >>= 12;
    value &= 31;
    return std::chrono::hours(value);
}

std::chrono::minutes ServerTime::minutes() const
{
    auto value = this->timestamp;
    value >>= 6;
    value &= 63;
    return std::chrono::minutes(value);
}

std::chrono::seconds ServerTime::seconds() const
{
    auto value = this->timestamp;
    value &= 63;
    return std::chrono::seconds(value);
}

Timestamp ServerTime::add(Timestamp ts, std::chrono::seconds ss)
{
    auto tt = ServerTime::to_time_t(ts);
    auto tp = std::chrono::system_clock::from_time_t(tt) + ss;
    return ServerTime::from_time_t(std::chrono::system_clock::to_time_t(tp));
}

Timestamp ServerTime::sub(Timestamp ts, std::chrono::seconds ss)
{
    auto tt = ServerTime::to_time_t(ts);
    auto tp = std::chrono::system_clock::from_time_t(tt) - ss;
    return ServerTime::from_time_t(std::chrono::system_clock::to_time_t(tp));
}

// see ps_game.004E1CF0
Timestamp ServerTime::from_SYSTEMTIME(const SYSTEMTIME& lt)
{
    Timestamp value = lt.wYear;
    value -= 16;
    value <<= 4;
    value += lt.wMonth;

    value <<= 5;
    value += lt.wDay;

    value <<= 5;
    value += lt.wHour;

    value <<= 6;
    value += lt.wMinute;

    value <<= 6;
    value += lt.wSecond;
    return value;
}

void ServerTime::to_SYSTEMTIME(Timestamp ts, SYSTEMTIME& lt)
{
    ServerTime st(ts);
    lt.wYear = int(st.year());
    lt.wMonth = unsigned(st.month());
    lt.wDay = unsigned(st.day());
    lt.wHour = st.hours().count();
    lt.wMinute = st.minutes().count();
    lt.wSecond = int(st.seconds().count());
}

Timestamp ServerTime::from_time_t(time_t tt)
{
    using namespace std::chrono;

    auto tp = current_zone()->to_local(system_clock::from_time_t(tt));
    auto dp = time_point_cast<days>(tp);

    auto date = year_month_day(dp);
    auto time = hh_mm_ss(tp - dp);

    SYSTEMTIME lt{};
    lt.wYear = int(date.year());
    lt.wMonth = unsigned(date.month());
    lt.wDay = unsigned(date.day());
    lt.wHour = time.hours().count();
    lt.wMinute = time.minutes().count();
    lt.wSecond = int(time.seconds().count());
    return ServerTime::from_SYSTEMTIME(lt);
}

time_t ServerTime::to_time_t(Timestamp ts)
{
    std::tm tm{};
    ServerTime::to_tm(ts, tm);
    return std::mktime(&tm);
}

Timestamp ServerTime::from_tm(const std::tm& tm)
{
    Timestamp value = tm.tm_year + 1900;
    value -= 16;
    value <<= 4;
    value += tm.tm_mon + 1;

    value <<= 5;
    value += tm.tm_mday;

    value <<= 5;
    value += tm.tm_hour;

    value <<= 6;
    value += tm.tm_min;

    value <<= 6;
    value += tm.tm_sec;
    return value;
}

void ServerTime::to_tm(Timestamp ts, std::tm& tm)
{
    ServerTime st(ts);
    tm.tm_year = int(st.year()) - 1900;
    tm.tm_mon = unsigned(st.month()) - 1;
    tm.tm_mday = unsigned(st.day());
    tm.tm_hour = st.hours().count();
    tm.tm_min = st.minutes().count();
    tm.tm_sec = int(st.seconds().count());
    tm.tm_isdst = -1;
}

// see ps_game.004E1A50
Timestamp ServerTime::now()
{
    SYSTEMTIME lt{};
    GetLocalTime(&lt);
    return ServerTime::from_SYSTEMTIME(lt);
}
