#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;

#define IDC_BUTTON_1 101
#define IDC_BUTTON_2 102
#define IDC_TEXT_1 103
#define IDC_TEXT_2 104



const char g_szClassName[] = "myWindowClass";
const char *fonts[] = {"Tahoma", "Times New Roman", "Trebuchet MS", "Verdana", "Palatino Linotype", "Microsoft Sans Serif",
                       "Lucida Console", "Impact", "Georgia", "Comic Sans MS", "Arial", "Courier New"
                      };

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = CS_HREDRAW | CS_VREDRAW ;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
               0,
               g_szClassName,
               "Laboratory NR. 1",
               WS_OVERLAPPEDWINDOW,
               CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
               NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}



// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND button_1, button_2, text_1, text_2;
    HFONT hfont, hfont_2;
    static bool flag_1 = false;
    srand (time(NULL));

    switch(msg)
    {

    case WM_LBUTTONDOWN:
    {
        char szFileName[MAX_PATH];
        HINSTANCE hInstance = GetModuleHandle(NULL);

        GetModuleFileName(hInstance, szFileName, MAX_PATH);
        MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
    }
    break;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);

    case WM_PAINT:
    {
        RECT rect;
        GetClientRect(hwnd, &rect);
        PAINTSTRUCT ps;
        HDC hDC = BeginPaint (hwnd, &ps);
        DrawText (hDC, TEXT ("Done with Pride and Prejudice by Unnemotional Hyena"), -1, &rect,
                  DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint (hwnd, &ps);
    }
    break;

    case WM_CREATE:
    {
        button_1 = CreateWindowEx(WS_EX_CLIENTEDGE,
                                  "BUTTON",
                                  0,
                                  WS_TABSTOP | WS_VISIBLE| WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,
                                  0,
                                  0,
                                  0,
                                  0,
                                  hwnd,
                                  (HMENU)IDC_BUTTON_1,
                                  GetModuleHandle(NULL),
                                  NULL);

        button_2 = CreateWindowEx(0,
                                  "BUTTON",
                                  "HELL",
                                  WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_DEFPUSHBUTTON,
                                  0,
                                  0,
                                  0,
                                  0,
                                  hwnd,
                                  (HMENU)IDC_BUTTON_2,
                                  GetModuleHandle(NULL),
                                  NULL);
        text_1 = CreateWindowEx(WS_EX_CLIENTEDGE,
                                TEXT("EDIT"),
                                "Enter your text...",
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL |
                                ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
                                0,
                                0,
                                0,
                                0,
                                hwnd,
                                (HMENU)IDC_TEXT_1,
                                GetModuleHandle(NULL),
                                NULL);

        text_2 = CreateWindowEx(WS_EX_CLIENTEDGE,
                                TEXT("EDIT"),
                                "Enter your text...",
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL |
                                ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | BS_OWNERDRAW,
                                0,
                                0,
                                0,
                                0,
                                hwnd,
                                (HMENU)IDC_TEXT_2,
                                GetModuleHandle(NULL),
                                NULL);
        hfont = CreateFont(16,20,100,40,FW_BLACK,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,
                           CLIP_DEFAULT_PRECIS,PROOF_QUALITY, VARIABLE_PITCH,TEXT("Courier New"));
        hfont_2 = CreateFont(0, 0, 0,0,0,0,0,0,0,0,0,0,0,TEXT("Courier New"));

        SendMessage(button_1, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(FALSE, 0));
        SendMessage(text_2, WM_SETFONT, (WPARAM)hfont_2, MAKELPARAM(FALSE, 0));
    }
    break;

    case WM_COMMAND:
    {

        if (HIWORD(wParam) == EN_SETFOCUS && GetDlgCtrlID((HWND)lParam) == IDC_TEXT_1)
        {
            SetWindowText(text_1, "" );
            break;
        }
        else if (HIWORD(wParam) == EN_SETFOCUS && GetDlgCtrlID((HWND)lParam) == IDC_TEXT_2)
        {
            SetWindowText(text_2, "" );
            break;
        }

        // Switch wParam -------------------------------------------------------------------

        switch(LOWORD(wParam))
        {

        case IDC_BUTTON_1:
        {
            SetWindowText(text_1,"You clicked the button  O__O");
        }
        break;

        case IDC_BUTTON_2:
        {
            flag_1 = true;
            InvalidateRect(text_2, NULL, TRUE);
            hfont_2 = CreateFont(rand() % 42 + 5, rand() % 42 + 5, 0,0,0,0,0,0,0,0,0,0,0,TEXT(fonts[rand() % 11]));
            SendMessage(text_2, WM_SETFONT, (WPARAM)hfont_2, MAKELPARAM(FALSE, 0));
        }
        break;

        }
        break;
    }

    case WM_DRAWITEM:
        if ((UINT)wParam == IDC_BUTTON_1)
        {
            LPDRAWITEMSTRUCT lpdis = (DRAWITEMSTRUCT*)lParam;
            SIZE size;
            GetTextExtentPoint32(lpdis->hDC, "O O", 3, &size);
            SetTextColor(lpdis->hDC, RGB(10,13,45));
            SetBkColor(lpdis->hDC, RGB(128,0,128));

            ExtTextOut(
                lpdis->hDC,
                ((lpdis->rcItem.right - lpdis->rcItem.left) - size.cx) / 2 - 3,
                ((lpdis->rcItem.bottom - lpdis->rcItem.top) - size.cy) / 2 + 4,
                ETO_OPAQUE,
                &lpdis->rcItem,
                "O O",
                3,
                NULL);

            DrawEdge(
                lpdis->hDC,
                &lpdis->rcItem,
                (lpdis->itemState & ODS_SELECTED ? EDGE_SUNKEN : EDGE_RAISED ),
                BF_RECT);
            return TRUE;
        }

    case WM_SIZE:
    {
        RECT rect;
        GetClientRect(hwnd, &rect);
        int x = (rect.right - rect.left)/2 - 100;
        int y = (rect.bottom - rect.top)/2 + 20;

        MoveWindow (button_1, x-20, y, 100, 40, TRUE);
        MoveWindow(button_2, x+120, y, 100, 40, TRUE);
        MoveWindow(text_1, x - 205, y - 140, 300, 100, TRUE);
        MoveWindow(text_2, x + 110, y - 140, 300, 100, TRUE);
        break;
    }

    case WM_CTLCOLOREDIT:
    {
        static int R = 34, G = 62, B = 2;
        static int R_font = 0, G_font = 0, B_font = 0;

        HDC hdcEdit = (HDC)wParam;
        SetBkMode(hdcEdit, OPAQUE);

        if(flag_1 == true && GetDlgCtrlID((HWND)lParam) == IDC_TEXT_2)
        {
            R_font = rand() % 256;
            G_font = rand() % 256;
            B_font = rand() % 256;
            R = rand() % 256;
            G = rand() % 256;
            B = rand() % 256;

            SetTextColor(hdcEdit, RGB(R_font, G_font, B_font));
            SetBkColor(hdcEdit, RGB(R, G, B));
            flag_1 = false;
            return (INT_PTR)CreateSolidBrush(RGB(R, G, B));
        }
        else if (flag_1 == false && GetDlgCtrlID((HWND)lParam) == IDC_TEXT_2)
        {
            SetTextColor(hdcEdit, RGB(R_font, G_font, B_font));
            SetBkColor(hdcEdit, RGB(R, G, B));
            return (INT_PTR)CreateSolidBrush(RGB(R, G, B));
        }
    }
    break;

    case WM_GETMINMAXINFO:
    {
        LPMINMAXINFO winSize = (LPMINMAXINFO)lParam;
        winSize->ptMinTrackSize.x = 645;
        winSize->ptMinTrackSize.y = 300;
    }
    break;

    case WM_SYSCOMMAND:
    {
        switch(wParam)
        {
        case SC_MINIMIZE:
        {
           // SetBkColor(HDC GetDC(hwnd), RGB(240, 24, 23));
            break;
        }

        case SC_MAXIMIZE:
        {
            RECT rc;
            GetWindowRect ( hwnd, &rc ) ;
            int xPos = rand() % 800;
            int yPos = rand() % 800;
            SetWindowPos( hwnd, 0, xPos, yPos, 0, 0, SWP_NOZORDER | SWP_NOSIZE );
            break;
        }

        case SC_CLOSE:
        {
            if(MessageBox(hwnd, "Are you sure you want to quit?", "Close?", MB_YESNO | MB_ICONQUESTION) == IDYES)
            {
                exit(1);
            }
            break;
        }
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        break;
    }
    break;

    }
    return 0;
    }
