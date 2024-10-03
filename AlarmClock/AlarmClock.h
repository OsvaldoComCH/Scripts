#ifndef ALARMCLOCK
#define ALARMCLOCK

#include <windows.h>

int __FREQ_TO_US__ = 10;
int __FREQ_TO_MS__ = 10000;

int AlarmClockInit()
{
    LARGE_INTEGER Freq;
    if(QueryPerformanceFrequency(&Freq))
    {
        __FREQ_TO_US__ = Freq.QuadPart / 1000000;
        __FREQ_TO_MS__ = Freq.QuadPart / 1000;
        return 0;
    }
    __FREQ_TO_US__ = 0;
    __FREQ_TO_MS__ = 0;
    return 1;
}

void AlarmClockPM(int Milliseconds)
{
    if(__FREQ_TO_MS__)
    {
        LARGE_INTEGER Time;
        QueryPerformanceCounter(&Time);
        long long DueTime = Milliseconds * __FREQ_TO_MS__ + Time.QuadPart;
        long long TimeLeft = DueTime;
        while(TimeLeft > 0)
        {
            if(TimeLeft > __FREQ_TO_MS__ * 17)
            {
                Sleep(1);
            }else
            if(TimeLeft > __FREQ_TO_MS__ * 2)
            {
                timeBeginPeriod(1);
                Sleep(1);
                timeEndPeriod(1);
            }
            QueryPerformanceCounter(&Time);
            TimeLeft = DueTime - Time.QuadPart;
        }
    }else
    {
        timeBeginPeriod(1);
        Sleep(Milliseconds);
        timeEndPeriod(1);
    }
}

void AlarmClockP(int Microseconds)
{
    if(__FREQ_TO_US__)
    {
        LARGE_INTEGER Time;
        QueryPerformanceCounter(&Time);
        long long DueTime = Microseconds * __FREQ_TO_US__ + Time.QuadPart;
        long long TimeLeft = DueTime;
        while(TimeLeft > 0)
        {
            if(TimeLeft > __FREQ_TO_US__ * 17000)
            {
                Sleep(1);
            }else
            if(TimeLeft > __FREQ_TO_US__ * 2000)
            {
                timeBeginPeriod(1);
                Sleep(1);
                timeEndPeriod(1);
            }
            QueryPerformanceCounter(&Time);
            TimeLeft = DueTime - Time.QuadPart;
        }
    }else
    {
        AlarmClockPM(Microseconds / 1000);
    }
}

#endif