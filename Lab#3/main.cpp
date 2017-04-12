#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
#include "header.h"
void show_collor(HDC hdc, COLORREF rgb, int xLeft, int yTop);

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;             /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)LTGRAY_BRUSH;//(HBRUSH)(COLOR_WINDOW+1);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               0,       /* Windows decides the position */
               0,       /* where the window ends up on the screen */
               800,                 /* The programs width */
               600,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );


    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);
    UpdateWindow(hwnd);
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

static int scroll_pos[] = {0,0,0};

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    static HDC hdc, hdcmem;
    static bool flag_3, flag_4, flag_5, flag_6;
    static PAINTSTRUCT ps;
    HINSTANCE hInstance;

    RECT rect, rect_2 = {70, 480, 130, 530};
    static HWND button_1, button_2, button_3, button_4, button_5, button_6, scrollbar1, scrollbar2, scrollbar3;
    static HPEN hpen, hpen_gradient, hpen_white;
    static POINT rectangle_line[2], bezier[4];
    static int i = 0, contor = 0;

    BITMAP bitmap;
    HGDIOBJ oldBitmap;
    HBITMAP hbmpImage = NULL;
    hbmpImage = (HBITMAP)LoadImage(hInstance, "wolf2.bmp", IMAGE_BITMAP, 90, 110, LR_LOADFROMFILE);
    GetObject(hbmpImage, sizeof(bitmap), &bitmap);

    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
        button_1 = CreateWindowEx(WS_EX_CLIENTEDGE,
                                  "BUTTON",
                                  "size +",
                                  WS_TABSTOP | WS_VISIBLE| WS_CHILD | BS_DEFPUSHBUTTON,
                                  10,
                                  10,
                                  60,
                                  30,
                                  hwnd,
                                  (HMENU)ID_BUTTON_1,
                                  GetModuleHandle(NULL),
                                  NULL);
        button_2 = CreateWindowEx(WS_EX_CLIENTEDGE,
                                  "BUTTON",
                                  "size -",
                                  WS_TABSTOP | WS_VISIBLE| WS_CHILD | BS_DEFPUSHBUTTON,
                                  80,
                                  10,
                                  60,
                                  30,
                                  hwnd,
                                  (HMENU)ID_BUTTON_2,
                                  GetModuleHandle(NULL),
                                  NULL);
        button_3 = CreateWindowEx(WS_EX_CLIENTEDGE,
                                  "BUTTON",
                                  "Rectangle",
                                  WS_TABSTOP | WS_VISIBLE| WS_CHILD | BS_DEFPUSHBUTTON,
                                  10,
                                  50,
                                  130,
                                  25,
                                  hwnd,
                                  (HMENU)ID_BUTTON_3,
                                  GetModuleHandle(NULL),
                                  NULL);
        button_4 = CreateWindowEx(WS_EX_CLIENTEDGE,
                                  "BUTTON",
                                  "Line",
                                  WS_TABSTOP | WS_VISIBLE| WS_CHILD | BS_DEFPUSHBUTTON,
                                  10,
                                  85,
                                  50,
                                  25,
                                  hwnd,
                                  (HMENU)ID_BUTTON_4,
                                  GetModuleHandle(NULL),
                                  NULL);
        button_5 = CreateWindowEx(WS_EX_CLIENTEDGE,
                                  "BUTTON",
                                  "Bezier",
                                  WS_TABSTOP | WS_VISIBLE| WS_CHILD | BS_DEFPUSHBUTTON,
                                  85,
                                  85,
                                  55,
                                  25,
                                  hwnd,
                                  (HMENU)ID_BUTTON_5,
                                  GetModuleHandle(NULL),
                                  NULL);
        button_6 = CreateWindowEx(WS_EX_CLIENTEDGE,
                                  "BUTTON",
                                  "Eraser",
                                  WS_TABSTOP | WS_VISIBLE| WS_CHILD | BS_DEFPUSHBUTTON,
                                  10,
                                  120,
                                  130,
                                  25,
                                  hwnd,
                                  (HMENU)ID_BUTTON_6,
                                  GetModuleHandle(NULL),
                                  NULL);
        scrollbar1 = CreateWindowEx(0,
                                    TEXT("SCROLLBAR"),
                                    0,
                                    WS_CHILD | WS_VISIBLE | SBS_HORZ,
                                    10,
                                    150,
                                    130,
                                    20,
                                    hwnd,
                                    (HMENU)ID_SCROLL_BAR1,
                                    GetModuleHandle(NULL),
                                    NULL);
        scrollbar2 = CreateWindowEx(0,
                                    TEXT("SCROLLBAR"),
                                    0,
                                    WS_CHILD | WS_VISIBLE | SBS_HORZ,
                                    10,
                                    180,
                                    130,
                                    20,
                                    hwnd,
                                    (HMENU)ID_SCROLL_BAR2,
                                    GetModuleHandle(NULL),
                                    NULL);
        scrollbar3 = CreateWindowEx(0,
                                    TEXT("SCROLLBAR"),
                                    0,
                                    WS_CHILD | WS_VISIBLE | SBS_HORZ,
                                    10,
                                    210,
                                    130,
                                    20,
                                    hwnd,
                                    (HMENU)ID_SCROLL_BAR3,
                                    GetModuleHandle(NULL),
                                    NULL);

        SetScrollRange (scrollbar1, SB_CTL, 0, 255, FALSE);
        SetScrollRange (scrollbar2, SB_CTL, 0, 255, FALSE);
        SetScrollRange (scrollbar3, SB_CTL, 0, 255, FALSE);

        RegisterHotKey(hwnd, ID_RECTANGLE_KEY, MOD_CONTROL, 0x52);
        RegisterHotKey(hwnd, ID_LINE_KEY, MOD_CONTROL, 0x4C);

        break;

    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case ID_BUTTON_1:
            i +=1;
            hpen = CreatePen(PS_SOLID, i, RGB(scroll_pos[0],scroll_pos[1],scroll_pos[2]));
            break;
        case ID_BUTTON_2:
            i -=1;
            if (i<0)
            {
                i = 0;
            }
            hpen = CreatePen(PS_SOLID, i, RGB(scroll_pos[0],scroll_pos[1],scroll_pos[2]));
            break;
        case ID_BUTTON_3:
            flag_3 = true;
            flag_4 = false;
            flag_5 = false;
            flag_6 = false;
            break;

        case ID_BUTTON_4:
            flag_4 = true;
            flag_3 = false;
            flag_5 = false;
            flag_6 = false;
            break;

        case ID_BUTTON_5:
            flag_5 = true;
            flag_3 = false;
            flag_4 = false;
            flag_6 = false;
            break;
        case ID_BUTTON_6:
            flag_6 = true;
            flag_3 = false;
            flag_4 = false;
            flag_5 = false;
            break;
        }
        break;

    case WM_LBUTTONDOWN:
        hdc = GetDC(hwnd);
        if (LOWORD(lParam) < 800 and LOWORD(lParam) > 150 and HIWORD(lParam) < 600 and HIWORD(lParam) > 10)
        {
            if (flag_3 or flag_4)
            {
                hpen = CreatePen(PS_SOLID, i, RGB(scroll_pos[0],scroll_pos[1],scroll_pos[2]));
                SelectObject(hdc, hpen);
                rectangle_line[0].x = LOWORD(lParam);
                rectangle_line[0].y = HIWORD(lParam);
            }
            if (flag_5)
            {
                hpen = CreatePen(PS_SOLID, i, RGB(scroll_pos[0],scroll_pos[1],scroll_pos[2]));
                SelectObject(hdc, hpen);
                bezier[0].x = LOWORD(lParam);
                bezier[0].y = HIWORD(lParam);
            }
        }
        break;

    case WM_LBUTTONUP:
        hdc = GetDC(hwnd);
        if (LOWORD(lParam) < 800 and LOWORD(lParam) > 150 and HIWORD(lParam) < 600 and HIWORD(lParam) > 10)
        {
            if (flag_3 or flag_4)
            {
                rectangle_line[1].x = LOWORD(lParam);
                rectangle_line[1].y = HIWORD(lParam);
            }
            if (flag_5)
            {
                bezier[1].x = LOWORD(lParam);
                bezier[1].y = HIWORD(lParam);
            }
            if (flag_3)
            {
                SelectObject(hdc, hpen);
                Rectangle (hdc, rectangle_line[0].x, rectangle_line[0].y, rectangle_line[1].x, rectangle_line[1].y) ;
            }
            else if (flag_4)
            {
                SelectObject (hdc, hpen);
                MoveToEx(hdc, rectangle_line[0].x, rectangle_line[0].y, NULL);
                LineTo(hdc, rectangle_line[1].x, rectangle_line[1].y);
            }
        }
        DeleteDC(hdc);
        DeleteObject(SelectObject(hdc, hpen));
        break;
    case WM_MOUSEMOVE:
        hdc = GetDC(hwnd);

        if (wParam & MK_LBUTTON & flag_6)
        {
            if (LOWORD(lParam) < 800 and LOWORD(lParam) > 150 and HIWORD(lParam) < 600 and HIWORD(lParam) > 10)
            {
                hdc = GetDC(hwnd);
                hpen_white = CreatePen(PS_SOLID, i, RGB(255,255,255));
                SelectObject(hdc, hpen_white);
                MoveToEx(hdc, LOWORD(lParam), HIWORD(lParam), NULL);
                LineTo(hdc, LOWORD(lParam), HIWORD(lParam));
            }
        }
        DeleteDC(hdc);
        DeleteObject(SelectObject(hdc, hpen_white));
        break;

    case WM_RBUTTONDOWN:
        if (LOWORD(lParam) < 800 and LOWORD(lParam) > 150 and HIWORD(lParam) < 600 and HIWORD(lParam) > 10)
        {
            if (flag_5)
            {
                bezier[3].x = LOWORD(lParam);
                bezier[3].y = HIWORD(lParam);
            }
        }
        break;

    case WM_RBUTTONUP:
        hdc = GetDC(hwnd);
        if (LOWORD(lParam) < 800 and LOWORD(lParam) > 150 and HIWORD(lParam) < 600 and HIWORD(lParam) > 10)
        {
            if (flag_5)
            {
                bezier[2].x = LOWORD(lParam);
                bezier[2].y = HIWORD(lParam);
                SelectObject(hdc, hpen);
                PolyBezier(hdc, bezier, 4) ;
            }
        }
        DeleteDC(hdc);
        break;

    case WM_PAINT:
        InvalidateRect (hwnd, NULL, TRUE) ;
        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rect);
        rect.bottom -= 10;
        rect.left += 150;
        rect.right -= 10;
        rect.top += 10;
        FillRect(hdc, &rect, (HBRUSH)WHITE_BRUSH);




        for (int i = 0; i < 30; i++)
        {
            int temp = i;
            hpen_gradient = CreatePen(PS_SOLID, 1, RGB(int(max(255 - temp * 30, 0)), int(max(255 - 10 * temp, 0)), int(max(temp * 8, 0))));
            SelectObject(hdc, hpen_gradient);
            MoveToEx(hdc, 10, 310 + i, NULL);
            LineTo(hdc, 60, 310 + i);
            hpen_gradient = CreatePen(PS_SOLID, 1, RGB(int(max(temp * 8, 0)),int(max(255 - temp * 30, 0)), int(max(255 - 10 * temp, 0))));
            SelectObject(hdc, hpen_gradient);
            MoveToEx(hdc, 60, 310 + i, NULL);
            LineTo(hdc, 110, 310 + i);
            DeleteObject(hpen_gradient);
        }
        Ellipse (hdc, 10, 410, 60, 460) ;
        POINT bezier_2[4];
        bezier_2[0].x = 130;
        bezier_2[0].y = 300;
        bezier_2[1].x = 170;
        bezier_2[1].y = 320;
        bezier_2[2].x = 80;
        bezier_2[2].y = 340;
        bezier_2[3].x = 130;
        bezier_2[3].y = 360;

        PolyBezier(hdc, bezier_2, 4) ;

        for (int i = 0; i < 5; i++)
        {
            hpen_gradient = CreatePen(PS_SOLID, i+2, RGB(i* 50, 0,  255 - i*20));
            SelectObject(hdc, hpen_gradient);
            MoveToEx(hdc, 10, 350 + (i+ 1)*10, NULL);
            LineTo(hdc, 110, 350 + (i+ 1)*10);
            DeleteObject(hpen_gradient);
        }
        RoundRect (hdc, 70, 410, 120, 460,
                   30, 40) ;
        hpen_gradient = CreatePen(PS_DOT, 1, RGB(128, 0, 153));
        SelectObject(hdc, hpen_gradient);
        Pie(hdc, 10, 480, 60, 530, 40, 500, 60, 530);
        DeleteObject(SelectObject(hdc, hpen_gradient));

        FillRect(hdc, &rect_2, (HBRUSH)GRAY_BRUSH);


        hpen_gradient = CreatePen(PS_SOLID, 1, RGB(0,0,0));
        SelectObject(hdc, hpen_gradient);
        show_collor(hdc, RGB(scroll_pos[0], scroll_pos[1], scroll_pos[2]), 10, 240);
        DeleteObject(SelectObject(hdc, hpen_gradient));

        hdcmem = CreateCompatibleDC(hdc);
        SelectObject(hdcmem, hbmpImage);
        BitBlt(hdc, 25, 540, bitmap.bmWidth, bitmap.bmHeight, hdcmem, 0, 0, SRCCOPY);
        DeleteDC(hdcmem);

        EndPaint (hwnd, &ps) ;
        return 0 ;

    case WM_HSCROLL:
    {
        hdc = GetDC(hwnd);
        if (GetDlgCtrlID((HWND)lParam) == ID_SCROLL_BAR1)
        {
            contor = 0;
            SetScrollPos (scrollbar1, SB_CTL, scroll_pos[contor], TRUE) ;
            show_collor(hdc, RGB(scroll_pos[0], scroll_pos[1], scroll_pos[2]), 10, 240);

        }

        if (GetDlgCtrlID((HWND)lParam) == ID_SCROLL_BAR2)
        {
            contor = 1;
            SetScrollPos (scrollbar2, SB_CTL, scroll_pos[contor], TRUE) ;
            show_collor(hdc, RGB(scroll_pos[0], scroll_pos[1], scroll_pos[2]), 10, 240);
        }
        if (GetDlgCtrlID((HWND)lParam) == ID_SCROLL_BAR3)
        {
            contor = 2;
            SetScrollPos (scrollbar3, SB_CTL, scroll_pos[contor], TRUE) ;
            show_collor(hdc, RGB(scroll_pos[0], scroll_pos[1], scroll_pos[2]), 10, 240);
        }
        switch (LOWORD (wParam))
        {
        case SB_LINELEFT:
            scroll_pos[contor] -= 10 ;
            break ;
        case SB_LINERIGHT:
            scroll_pos[contor] += 10 ;
            break ;
        case SB_PAGELEFT:
            scroll_pos[contor] -= 30;
            break;
        case SB_PAGERIGHT:
            scroll_pos[contor] += 30;
            break;
        case SB_THUMBPOSITION:
            scroll_pos[contor] = HIWORD (wParam) ;
            break ;
        default :
            break ;
        }

        if (scroll_pos[contor] > 255)
        {
            scroll_pos[contor] = 255;
        }
        else if (scroll_pos[contor] < 0)
        {
            scroll_pos[contor] = 0;
        }
        break;


    }
    break;

    case WM_HOTKEY:
    {
        switch(wParam)
        {
        case ID_RECTANGLE_KEY:
        {
            flag_3 = true;
            flag_4 = false;
            flag_5 =false;
            break;
        }
        case ID_LINE_KEY:
        {
            flag_4 = true;
            flag_3 = false;
            flag_5 = false;
            break;
        }
        }
        break;
    }
    break;


    case WM_GETMINMAXINFO:
    {
        LPMINMAXINFO winSize = (LPMINMAXINFO)lParam;
        winSize -> ptMinTrackSize.x = 1000;
        winSize -> ptMinTrackSize.y = 700;
        winSize -> ptMaxTrackSize.x = 1000;
        winSize -> ptMaxTrackSize.y = 700;
    }
    break;

    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

void show_collor(HDC hdc, COLORREF rgb, int xLeft, int yTop)
{
    HBRUSH hBrush = CreateSolidBrush(rgb);
    SelectObject(hdc, hBrush);
    Rectangle(hdc, xLeft, yTop, xLeft + 130, yTop + 50);
    DeleteObject(hBrush);
}
