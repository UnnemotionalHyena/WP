#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include "header.h"


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DialogProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);

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
    wincl.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = MAKEINTRESOURCE(IDM_MENU);                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

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
               500,                 /* The programs width */
               400,                 /* and height in pixels */
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
    static HINSTANCE hInstance;
    static HWND scrollbar1, scrollbar2;
    static int iVscrollPos = 500;
    static int x, y;
    x = GetSystemMetrics(SM_CXSCREEN);
    y = GetSystemMetrics(SM_CYSCREEN);

    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
    {
        scrollbar1 = CreateWindowEx(NULL,

                                    TEXT("SCROLLBAR"),
                                    0,
                                    WS_CHILD | WS_VISIBLE | SBS_HORZ,
                                    100,
                                    40,
                                    200,
                                    20,
                                    hwnd,
                                    (HMENU)IDM_SCROLL_BAR1,
                                    GetModuleHandle(NULL),
                                    NULL);

        RegisterHotKey(hwnd, IDM_EXIT_KEY, MOD_CONTROL, 0x57);
        RegisterHotKey(hwnd, IDM_MAXIMIZE_KEY, MOD_SHIFT, VK_RETURN);


        SetScrollRange (scrollbar1, SB_CTL, 500, y, FALSE);
        //SetScrollPos(scrollbar1, SB_CTL, iVscrollPos, TRUE);
    }

    case WM_COMMAND:
    {
        switch(LOWORD((wParam)))
        {
        case IDM_FILE_THIS:
        {
            char szFileName[MAX_PATH];
            HINSTANCE hInstance = GetModuleHandle(NULL);
            GetModuleFileName(hInstance, szFileName, MAX_PATH);
            MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
            break;
        }
        case IDM_FILE_CLOSE:
        {
            if(MessageBox(hwnd, "Are you sure you want to quit?", "Close?", MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                exit(1);
            }
        }
        break;
        case IDM_FILE_INFO:
        {
            DialogBox(hInstance, MAKEINTRESOURCE(IDM_DLGBOX),hwnd, DialogProc);
            break;
        }
        break;
        }
    }
    break;

    case WM_HOTKEY:
    {
        switch(wParam)
        {
        case IDM_EXIT_KEY:
        {
            if(MessageBox(hwnd, "Are you sure you want to quit?", "Close?", MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                exit(1);
            }
            break;
        }
        case IDM_MAXIMIZE_KEY:
        {
            MoveWindow (hwnd, 0, 0, x, y - 40, TRUE);
            break;
        }
        break;
        }
    }
    break;

    case WM_HSCROLL:
        switch (LOWORD (wParam))
        {
        case SB_LINELEFT:
            iVscrollPos -= 10 ;
            break ;
        case SB_LINERIGHT:
            iVscrollPos += 10 ;
            break ;
        case SB_THUMBPOSITION:
            iVscrollPos = HIWORD (wParam) ;
            break ;
        default :
            break ;
        }
        iVscrollPos = max (0, min (iVscrollPos, y));
        if (iVscrollPos != GetScrollPos (hwnd, SB_VERT))
        {
            SetScrollPos (hwnd, SB_VERT, iVscrollPos, TRUE) ;
            InvalidateRect (hwnd, NULL, TRUE) ;
        }
        SetScrollPos(scrollbar1, SB_CTL, iVscrollPos, TRUE);
        MoveWindow (hwnd, 0, 0, iVscrollPos*(1.77778), iVscrollPos, TRUE);
        break;

    case WM_GETMINMAXINFO:
    {
        LPMINMAXINFO winSize = (LPMINMAXINFO)lParam;
        winSize->ptMinTrackSize.x = 645;
        winSize->ptMinTrackSize.y = 300;
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

BOOL CALLBACK DialogProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        switch(wParam)
        {
        case IDOK:
            EndDialog(hwndDlg, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;
}
