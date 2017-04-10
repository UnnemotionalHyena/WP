#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>

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
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               1000,                 /* The programs width */
               600,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

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
    static HDC hdc;
    HPEN hpen;
    static POINT apt[4], triangle[2];//, pt;
    int cxClient, cyClient;
    PAINTSTRUCT ps ;


    switch (message)                  /* handle the messages */
    {
    case WM_SIZE:
        cxClient = LOWORD (lParam) ;
        cyClient = HIWORD (lParam) ;
        apt[0].x = 110;
        apt[0].y = 20 ;
        apt[1].x = 50 ;
        apt[1].y = 0 ;
        apt[2].x = 70;
        apt[2].y = 40;
        apt[3].x = 20;
        apt[3].y = 20;
        return 0 ;

    case WM_MOUSEMOVE:
    {

        //DrawBezier (hdc, apt) ;
        if (wParam & MK_LBUTTON || wParam & MK_RBUTTON)
        {
            hdc = GetDC (hwnd) ;
            SelectObject (hdc, GetStockObject (WHITE_PEN)) ;
            //triangle[0].x = 100;
            //triangle[0].y = 100;

            if (wParam & MK_LBUTTON)
            {
                triangle[1].x = LOWORD(lParam);
                triangle[1].y = HIWORD(lParam);
                ///triangle[0].x = pt.x;
                //triangle[0].y = pt.y;
            }

            SelectObject (hdc, GetStockObject (BLACK_PEN)) ;
            Rectangle (hdc, triangle[0].x, triangle[0].y, triangle[1].x, triangle[1].y) ;
            ReleaseDC (hwnd, hdc) ;


        }
        /*if (wParam & MK_LBUTTON || wParam & MK_RBUTTON)
        {
            hdc = GetDC (hwnd) ;
            SelectObject (hdc, GetStockObject (WHITE_PEN)) ;
            PolyBezier (hdc, apt, 1 + 3 * 1) ;
            if (wParam & MK_LBUTTON)
            {
                apt[1].x = LOWORD (lParam) ;
                apt[1].y = HIWORD (lParam) ;
            }
            if (wParam & MK_RBUTTON)
            {
                apt[2].x = LOWORD (lParam) ;
                apt[2].y = HIWORD (lParam) ;
            }
            SelectObject (hdc, GetStockObject (BLACK_PEN)) ;
            PolyBezier (hdc, apt, 1 + 3 * 1) ;
            ReleaseDC (hwnd, hdc) ;
        }
        return 0 ;*/


        break;
    }
    case WM_PAINT:
    {
        InvalidateRect (hwnd, NULL, TRUE) ;
        hdc = BeginPaint (hwnd, &ps) ;
        PolyBezier (hdc, apt, 1 + 3 * 1) ;
        EndPaint (hwnd, &ps) ;
        /*hdc = GetDC(hwnd);
        for (int i = 0; i < 5; i++)
        {
            hpen = CreatePen (PS_SOLID, i * 3, RGB (i* 50, i * 15, i * 10)) ;
            SelectObject (hdc, hpen) ;
            MoveToEx (hdc, 10,(i + 1) * 15, NULL) ;
            LineTo (hdc, 50, (i + 1) * 15) ;
        }*/
        break;
    }
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
