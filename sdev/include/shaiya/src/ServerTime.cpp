#include <chrono>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "include/shaiya/include/ServerTime.h"
using namespace shaiya;

Timestamp ServerTime::add(Timestamp augend, Seconds addend)
{
    using namespace std::chrono;

    auto tt = ServerTime::to_time_t(augend);
    auto tp = system_clock::from_time_t(tt) + std::chrono::seconds(addend);
    return ServerTime::from_time_t(system_clock::to_time_t(tp));
}

Timestamp ServerTime::sub(Timestamp minuend, Seconds subtrahend)
{
    using namespace std::chrono;

    auto tt = ServerTime::to_time_t(minuend);
    auto tp = system_clock::from_time_t(tt) - std::chrono::seconds(subtrahend);
    return ServerTime::from_time_t(system_clock::to_time_t(tp));
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
    return ServerTime::encoder(lt);
}

time_t ServerTime::to_time_t(Timestamp timestamp)
{
    SYSTEMTIME lt{};
    ServerTime::decoder(timestamp, lt);

    std::tm tm{};
    tm.tm_year = lt.wYear - 1900;
    tm.tm_mon = lt.wMonth - 1;
    tm.tm_mday = lt.wDay;
    tm.tm_hour = lt.wHour;
    tm.tm_min = lt.wMinute;
    tm.tm_sec = lt.wSecond;
    tm.tm_isdst = -1;
    return std::mktime(&tm);
}

// see ps_game.004E1A50
Timestamp ServerTime::now()
{
    SYSTEMTIME lt{};
    GetLocalTime(&lt);
    return ServerTime::encoder(lt);
}

// see ps_game.004E1CA0
void ServerTime::decoder(Timestamp timestamp, SYSTEMTIME& lt)
{
    auto value = timestamp;
    value >>= 26;
    value &= 63;
    value += 2000;
    lt.wYear = short(value);

    value = timestamp;
    value >>= 22;
    value &= 15;
    lt.wMonth = short(value);

    value = timestamp;
    value >>= 17;
    value &= 31;
    lt.wDay = short(value);

    value = timestamp;
    value >>= 12;
    value &= 31;
    lt.wHour = short(value);

    value = timestamp;
    value >>= 6;
    value &= 63;
    lt.wMinute = short(value);

    value = timestamp;
    value &= 63;
    lt.wSecond = short(value);
}

// see ps_game.004E1CF0
Timestamp ServerTime::encoder(const SYSTEMTIME& lt)
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
