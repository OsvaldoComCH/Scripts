#ifndef ALARMCLOCK
#define ALARMCLOCK

#include <windows.h>

#include <chrono>

void AlarmClockPM(int Milliseconds)
{
}

void AlarmClockP(int Microseconds)
{
    using namespace std::chrono;
    time_point<high_resolution_clock, microseconds> DueTime =
    time_point_cast<microseconds>(high_resolution_clock::now() + (microseconds)Microseconds);

    if(Microseconds > 2000)
    {
        timeBeginPeriod(1);
        Sleep((Microseconds / 1000) - 1);
        timeEndPeriod(1);
    }

    microseconds TimeLeft = DueTime - time_point_cast<microseconds>(high_resolution_clock::now());
    while(DueTime > time_point_cast<microseconds>(high_resolution_clock::now()))
    {
        continue;
    }
}

#endif