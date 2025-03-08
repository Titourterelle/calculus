#ifndef TIMELIMIT_H
#define TIMELIMIT_H

#include <cstdint>

enum class TimeLimit : uint8_t
{
    No = 0,
    Low = 1,
    Normal = 2,
    High = 3
};

#endif // TIMELIMIT_H
