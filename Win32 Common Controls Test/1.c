#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <stdio.h>
#include <wchar.h>

HWND Btn, PushBtn, Radio1, Radio2, Radio3, GroupBox, SplitBtn;
WNDPROC DefBtnProc;

int Count = 0;

LRESULT CALLBACK CustomBtn(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            SelectObject(hdc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hdc, RGB(255,0,0));
            Ellipse(hdc, 0, 0, 300, 300);

            wchar_t Text[10];
            wmemset(Text, 0, 10);
            swprintf(Text, L"%i", Count);
            TextOut(hdc, 130, 130, Text, 10);

            EndPaint(hwnd, &ps);
        }
        break;
        case WM_LBUTTONDOWN:
        {
            TRACKMOUSEEVENT tme;
            tme.cbSize = sizeof(TRACKMOUSEEVENT);
            tme.dwFlags = TME_LEAVE;
            tme.hwndTrack = hwnd;
            TrackMouseEvent(&tme);

            HDC hdc = GetDC(hwnd);
            SelectObject(hdc, GetStockObject(DC_BRUSH));
            if(SendMessage(Radio1, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
                SetDCBrushColor(hdc, RGB(0,255,0));
            }else
            if(SendMessage(Radio2, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
                SetDCBrushColor(hdc, RGB(0,0,255));
            }else
            if(SendMessage(Radio3, BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
                SetDCBrushColor(hdc, RGB(255,255,0));
            }
            Ellipse(hdc, 0, 0, 300, 300);

            ++Count;
            wchar_t Text[10];
            wmemset(Text, 0, 10);
            swprintf(Text, L"%i", Count);
            TextOut(hdc, 130, 130, Text, 10);

            ReleaseDC(hwnd, hdc);
        }
        break;
        case WM_MOUSELEAVE:
        case WM_LBUTTONUP:
        {
            HDC hdc = GetDC(hwnd);
            SelectObject(hdc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hdc, RGB(255,0,0));
            Ellipse(hdc, 0, 0, 300, 300);
            
            wchar_t Text[10];
            wmemset(Text, 0, 10);
            swprintf(Text, L"%i", Count);
            TextOut(hdc, 130, 130, Text, 10);

            ReleaseDC(hwnd, hdc);
        }
        break;
        case WM_LBUTTONDBLCLK:
        {
            SendMessage(hwnd, WM_LBUTTONDOWN, 0, 0);
        }
        break;
        case WM_MOUSEMOVE:
        break;
        default:
            CallWindowProc(DefBtnProc,hwnd,uMsg,wParam,lParam);
        break;
    }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
        {
            HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE);
            Btn = CreateWindowEx
            (
                0, L"BUTTON", L"Button",
                WS_VISIBLE | WS_CHILD | BS_FLAT,
                10, 10, 300, 300,
                hwnd, NULL, hInstance, NULL
            );
            DefBtnProc = (WNDPROC)SetWindowLongPtr(Btn, GWLP_WNDPROC, (LONG_PTR)CustomBtn);
            SetWindowRgn(Btn, CreateEllipticRgn(0,0,300,300), 1);

            GroupBox = CreateWindowEx
            (
                0, L"BUTTON", L"Group Box",
                WS_VISIBLE | WS_CHILD | BS_GROUPBOX,
                350, 10, 300, 300,
                hwnd, NULL, hInstance, NULL
            );

            Radio1 = CreateWindowEx
            (
                0, L"BUTTON", L"Green",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 50, 80, 20,
                GroupBox, NULL, hInstance, NULL
            );
            SendMessage(Radio1, BM_SETCHECK, BST_CHECKED, 0);
            Radio2 = CreateWindowEx
            (
                0, L"BUTTON", L"Blue",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 80, 80, 20,
                GroupBox, NULL, hInstance, NULL
            );
            Radio3 = CreateWindowEx
            (
                0, L"BUTTON", L"Yellow",
                WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
                10, 110, 80, 20,
                GroupBox, NULL, hInstance, NULL
            );

        }
        break;

        case WM_COMMAND:
        {
            printf("foi\n");
            short Notification = HIWORD(wParam);
            switch(Notification)
            {
                case BN_CLICKED:
                {
                    if((HWND)lParam == Btn)
                    {
                        wchar_t Text[30];
                        GetWindowText(Btn, Text, 30);
                        HDC hdc = GetDC(hwnd);
                        TextOut(hdc, 400, 400, Text, 30);
                        ReleaseDC(hwnd, hdc);
                    }
                }
                break;
            }
        }
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        break;
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Window";
    
    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx
    (
        0,
        CLASS_NAME,
        L"BOTÃO",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,   
        NULL,
        hInstance,
        NULL
    );

    if(hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}