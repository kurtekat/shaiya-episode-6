#include <utility>
#include "RewardItemProgress.h"
using namespace shaiya;

RewardItemProgress::RewardItemProgress(const RewardItemProgress& other)
{
    *this = other;
}

RewardItemProgress::RewardItemProgress(RewardItemProgress&& other) noexcept
{
    *this = std::move(other);
}

RewardItemProgress& RewardItemProgress::operator=(const RewardItemProgress& other)
{
    if (this != &other)
    {
        index = other.index;
        timeout = other.timeout;
        completed.store(other.completed.load());
    }

    return *this;
}

RewardItemProgress& RewardItemProgress::operator=(RewardItemProgress&& other) noexcept
{
    if (this != &other)
    {
        index = std::exchange(other.index, 0);
        timeout = std::move(other.timeout);
        completed.store(other.completed.load());
    }

    return *this;
}
