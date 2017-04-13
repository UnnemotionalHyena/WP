#include "header.h"

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("animation");

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
    wincl.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;            /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("animation"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               300,       /* Windows decides the position */
               25,       /* where the window ends up on the screen */
               700,                 /* The programs width */
               700,                 /* and height in pixels */
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


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static RECT rect;
    static HBITMAP hbmMEM;
    static HDC hdc, hdcMEM;
    static int timer_speed = 1;
    static HBRUSH hbrush;
    PAINTSTRUCT ps;
    POINT center = {100,100};
    static Object object_1(center, 10);

    switch (message)                  /* handle the messages */
    {

    case WM_CREATE:
        hdc = GetDC(hwnd);
        GetClientRect(hwnd, &rect);
        hdcMEM = CreateCompatibleDC(hdc);
        hbmMEM = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
        SelectObject(hdcMEM, hbmMEM);

        SetTimer(hwnd, ID_TIMER, timer_speed, NULL);
        break;

     case WM_LBUTTONDOWN:
     {
         static POINT coord;
         coord.x = LOWORD(lParam);
         coord.y = HIWORD(lParam);
         object_1.get_pos(coord);


         break;
     }
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rect);
        FillRect(hdcMEM, &rect,(HBRUSH)GetStockObject(WHITE_BRUSH));

        object_1.movement(hdcMEM, rect, hbrush);
        BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcMEM, 0, 0, SRCCOPY);
        EndPaint(hwnd, &ps);
        break;

    case WM_TIMER:
    {
        InvalidateRect(hwnd,NULL,FALSE);
        break;
    }
    case WM_GETMINMAXINFO:
    {
        LPMINMAXINFO winSize = (LPMINMAXINFO)lParam;
        winSize -> ptMinTrackSize.x = 700;
        winSize -> ptMinTrackSize.y = 700;
        winSize -> ptMaxTrackSize.x = 700;
        winSize -> ptMaxTrackSize.y = 700;
    }
    break;

    case WM_DESTROY:
        DeleteObject(hbmMEM);
        DeleteDC(hdcMEM);
        KillTimer(hwnd,ID_TIMER);
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
