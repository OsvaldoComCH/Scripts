#ifndef ALARMCLOCK
#define ALARMCLOCK

#include <windows.h>

#include <chrono>
class AlarmClockC
{
    private:
    long Error;

    public:
    AlarmClockC()
    {
        Error = 0;
    }

    void __fastcall SleepUs(int Microseconds)
    {
        using namespace std::chrono;
        time_point<high_resolution_clock, microseconds> DueTime =
        time_point_cast<microseconds>(high_resolution_clock::now() + (microseconds)(Microseconds - Error));

        if(Microseconds > 2000)
        {
            timeBeginPeriod(1);
            Sleep((Microseconds / 1000) - 1);
            timeEndPeriod(1);
        }

        while(DueTime > time_point_cast<microseconds>(high_resolution_clock::now()))
        {
            continue;
        }
        Error = (time_point_cast<microseconds>(high_resolution_clock::now()) - DueTime).count();
    }

    void __fastcall operator() (int Microseconds)
    {
        return SleepUs(Microseconds);
    }

    void Reset()
    {
        Error = 0;
    }
};

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

    while(DueTime > time_point_cast<microseconds>(high_resolution_clock::now()))
    {
        continue;
    }
}

#endif