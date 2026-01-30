#include <windows.h>
#include <stdio.h>
#include <time.h>

void Clicker(const int Interval)
{
    POINT Cursor;
    printf("\nClicker activated.\nClick with Numpad 0, disable with Numpad 1\n");

    while(1)
    {
        if(GetAsyncKeyState(VK_NUMPAD1) & 0x8000){break;}

        if(GetAsyncKeyState(VK_NUMPAD0) & 0x8000)
        {
            GetCursorPos(&Cursor);
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, Cursor.x, Cursor.y, 0, 0);
        }
        Sleep(Interval);
    }
}

int main()
{
    float cps;
    printf("Welcome to the Autoclicker");
    while(1)
    {
        printf("\nSecs/Click (0 to exit): ");
        scanf("%f", &cps);
        if(cps < 1){break;}
        int Interval = 1000 * cps;
        if(Interval <= 0){Interval = 1;}
        Clicker(Interval);
    }
}