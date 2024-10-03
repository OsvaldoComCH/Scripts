#include <windows.h>
#include <cstdio>
#include "AlarmClock.hpp"

void Clicker(const int Interval)
{
    char Period = 0;
    POINT Cursor;
    printf("\nClicker activated.\nClick with Numpad 0, disable with Numpad 1\n");

    while(1)
    {
        if(GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
        {
            break;
        }

        if(GetAsyncKeyState(VK_NUMPAD0) & 0x8000)
        {
            GetCursorPos(&Cursor);
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, Cursor.x, Cursor.y, 0, 0);
        }
        AlarmClockP(Interval);
    }
}

int main()
{
    float cps;
    printf("Welcome to the Autoclicker");
    while(1)
    {
        printf("\nClicks/sec (0 to exit): ");
        scanf("%f", &cps);
        if(cps < 1){break;}
        int Interval = 1000000/cps;
        if(Interval <= 0){Interval = 1;}
        Clicker(Interval);
    }
}