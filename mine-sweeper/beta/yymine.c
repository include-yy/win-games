#include <windows.h>
#include <stdlib.h>
#include <ctype.h>
#include "gamestruct.h"
#include "drawcubic.h"
#include "gamewindow.h"
#include "winstart.h"
#include "resource.h"
#include "gamemessage.h"

HINSTANCE hInst;

const char szAppname[] = "yymine";

const char szCubicClass[] = "yyCubic";
const char szScreenClass[] = "yyScreen";

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK CustomDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreHinstance,
                   PSTR szCmdLine, int iCmdShow)
{
    HWND hwnd;
    WNDCLASS wndclass;
    MSG msg;

    hInst = hInstance;

    HBRUSH hBr = CreateSolidBrush(RGB(0xE0, 0xE0, 0xE0));

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_MINE));
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = hBr;
    wndclass.lpszClassName = szAppname;
    wndclass.lpszMenuName = szAppname;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, "wnd class register error", szAppname, MB_ICONERROR);
        return 0;
    }

    //play sound test
    //PlaySound(MAKEINTRESOURCE(IDV_WIN), hInst, SND_ASYNC | SND_RESOURCE);

    GameWindowRegisterCubic(szCubicClass);
    GameWindowRegisterScreen(szScreenClass);

    //Init game structure and start with beginner level
    PGAMESTRUCT pgs = GetPGS();
    GameStructInit(pgs, 9, 9, 10);
    ReleasePGS(pgs);

    //create main window
    hwnd = GameWindowCreateFrame();
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    /* debug info
    MessageBox(NULL, "hello", "Hello", MB_OK);
    */

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DeleteObject(hBr);
    return msg.wParam;

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int iSelection = IDM_GAME_BEGINNER;
    static int iCustom[3];
    HDC hdc;
    PAINTSTRUCT ps;
    HMENU hMenu;
    PGAMESTRUCT pgs;

    //the next variables is used for judge cursor for face
    static int cxSize; //client width
    static int cySize; //client height
    static BOOL fInscreen; //if Cursor is in screen, TRUE
    static BOOL fCaptured; //if Cursor is captured, TRUE
    POINT ScreenPt; //used for GetCursorPos
    TRACKMOUSEEVENT tme; //leave judge

	switch (message)
	{
    case WM_CREATE:
        GameWindowCreateChild(hwnd);
        return 0;

    case WM_SIZE:
        cxSize = LOWORD(lParam);
        cySize = HIWORD(lParam);
        return 0;

    case WM_LBUTTONDOWN: //modify the extern value :fLeftButtonPressed on
        //MessageBox(NULL, "yymine.c line:110", "debug", MB_OK);
        pgs = GetPGS();
        pgs->fLeftButtonPressed = TRUE;
        SendMessage(pgs->hwndFace, WM_FACECHANGE, 0, 0); //to be surprised
        ReleasePGS(pgs);
        return 0;

    case WM_LBUTTONUP: //fLeftButtonPressed off
        /*
        if (fCaptured)
        {
            fCaptured = FALSE;
            ReleaseCapture();
        }
        */
        //MessageBox(NULL, "yymine.c line:116", "debug", MB_OK);
        pgs = GetPGS();
        pgs->fLeftButtonPressed = FALSE;
        SendMessage(pgs->hwndFace, WM_FACECHANGE, 0, 0);
        ReleasePGS(pgs);
        return 0;

    case WM_RBUTTONDOWN: //modify fRightButtonPressed: fRightButtonPressed on
        pgs = GetPGS();
        pgs->fRightButtonPressed = TRUE;
        ReleasePGS(pgs);
        return 0;

    case WM_RBUTTONUP: //fRightButtonPressed off
        pgs = GetPGS();
        pgs->fRightButtonPressed = FALSE;
        ReleasePGS(pgs);
        return 0;

        /*
    case WM_MOUSEMOVE:
        if (fInscreen == FALSE && fCaptured == FALSE)
        {
            fInscreen = TRUE;
            tme.cbSize = sizeof(TRACKMOUSEEVENT);
            tme.hwndTrack = hwnd;
            tme.dwFlags = TME_LEAVE;
            TrackMouseEvent(&tme);
        }
        GetCursorPos(&ScreenPt);
        ScreenToClient(hwnd, &ScreenPt);
        if ((ScreenPt.x > 0 && ScreenPt.x < cxSize) &&
            (ScreenPt.y > 0 && ScreenPt.y < cySize))
        {
            if (fCaptured == TRUE)
            {
                ReleaseCapture();
                fCaptured = FALSE;
            }
        }
        return 0;

    case WM_MOUSELEAVE:
        pgs = GetPGS();
        fInscreen = FALSE; //out of client
        GetCursorPos(&ScreenPt);
        ScreenToClient(hwnd, &ScreenPt); //to client
        if (ScreenPt.x <= 0 || ScreenPt.x >= cxSize ||
            ScreenPt.y <= 0 || ScreenPt.y >= cySize)
        {
            if (pgs->fLeftButtonPressed)
            {
                fCaptured = TRUE; //yes, setcapture
                SetCapture(hwnd);
            }
        }
        ReleasePGS(pgs);
        return 0;
        */
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        GameWindowDrawFrame(hwnd, hdc);
        EndPaint(hwnd, &ps);
        return 0;

    case WM_COMMAND:
        hMenu = GetMenu(hwnd);
        switch (LOWORD(wParam))
        {
        case IDM_GAME_NEW:
            GameWindowRestart(hwnd);
            return 0;

        case IDM_GAME_BEGINNER:
            pgs = GetPGS();
            if (iSelection == IDM_GAME_BEGINNER)
            {
                GameWindowRestart(hwnd);
            }
            else
            {
                GameWindowNewGame(hwnd, 9, 9, 10);
                CheckMenuItem(hMenu, iSelection, MF_UNCHECKED);
                iSelection = IDM_GAME_BEGINNER;
                CheckMenuItem(hMenu, iSelection, MF_CHECKED);
            }
            ReleasePGS(pgs);
            return 0;

        case IDM_GAME_SKILLED:
            pgs = GetPGS();
            if (iSelection == IDM_GAME_SKILLED)
            {
                GameWindowRestart(hwnd);
            }
            else
            {
                GameWindowNewGame(hwnd, 16, 16, 40);
                CheckMenuItem(hMenu, iSelection, MF_UNCHECKED);
                iSelection = IDM_GAME_SKILLED;
                CheckMenuItem(hMenu, iSelection, MF_CHECKED);
            }
            ReleasePGS(pgs);
            return 0;

        case IDM_GAME_EXPERT:
            pgs = GetPGS();
            if (iSelection == IDM_GAME_EXPERT)
            {
                GameWindowRestart(hwnd);
            }
            else
            {
                GameWindowNewGame(hwnd, 16, 30, 99);
                CheckMenuItem(hMenu, iSelection, MF_UNCHECKED);
                iSelection = IDM_GAME_EXPERT;
                CheckMenuItem(hMenu, iSelection, MF_CHECKED);
            }
            ReleasePGS(pgs);
            return 0;

        case IDM_GAME_CUSTOM:
            if(DialogBoxParam(hInst, "CustomDlg", hwnd, CustomDlgProc, (LPARAM)iCustom))
            {
                pgs = GetPGS();
                if (pgs->icRow == iCustom[0] &&
                    pgs->icCol == iCustom[1] &&
                    pgs->icMines == iCustom[2]) //all equal
                {
                    GameWindowRestart(hwnd);
                }
                else
                {
                    GameWindowNewGame(hwnd, iCustom[0], iCustom[1], iCustom[2]);
                }
                CheckMenuItem(hMenu, iSelection, MF_UNCHECKED);
                iSelection = IDM_GAME_CUSTOM;
                CheckMenuItem(hMenu, iSelection, MF_CHECKED);

                ReleasePGS(pgs);
            }
            return 0;

        case IDM_GAME_MARK:
            pgs = GetPGS();
            if (pgs->fQuestionMark)
            {
                CheckMenuItem(hMenu, IDM_GAME_MARK, MF_UNCHECKED);
                pgs->fQuestionMark = FALSE;
            }
            else
            {
                CheckMenuItem(hMenu, IDM_GAME_MARK, MF_CHECKED);
                pgs->fQuestionMark = TRUE;
            }
            ReleasePGS(pgs);
            return 0;

        case IDM_GAME_SOUND:
            pgs = GetPGS();
            if (pgs->fPlaySound)
            {
                CheckMenuItem(hMenu, IDM_GAME_SOUND, MF_UNCHECKED);
                pgs->fPlaySound = FALSE;
            }
            else
            {
                CheckMenuItem(hMenu, IDM_GAME_SOUND, MF_CHECKED);
                pgs->fPlaySound = TRUE;
            }
            ReleasePGS(pgs);
            return 0;

        case IDM_HELP_ABOUT:
            DialogBox(hInst, "AboutBox", hwnd, AboutDlgProc);
            return 0;
        }
        break;

    case WM_DESTROY:
        //destroy windows
        GameWindowDestroy();

        //MessageBox(NULL, "yymine.c 217", "debug", MB_OK); //debug
        //destroy game structure
        pgs = GetPGS();
        GameStructDestroy(pgs);
        ReleasePGS(pgs);

        PostQuitMessage(0);
		return 0;
	}
    return DefWindowProc(hwnd, message, wParam, lParam);
}

//just used for CustomDlgProc
void CustomGetNumber(int * threesome, char * buffer, int length, int index);

BOOL CALLBACK CustomDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndEditH;
    static HWND hwndEditW;
    static HWND hwndEditM;
    static int * ptint;
    PGAMESTRUCT pgs;
    char buffer[20];
    char * pbuf;
    int length;

    switch (message)
    {
    case WM_INITDIALOG:
        hwndEditH = GetDlgItem(hDlg, IDC_EDITH);
        hwndEditW = GetDlgItem(hDlg, IDC_EDITW);
        hwndEditM = GetDlgItem(hDlg, IDC_EDITM);
        pgs = GetPGS();
        //three argument
        itoa(pgs->icRow, buffer, 10);
        SetWindowText(hwndEditH, buffer);
        itoa(pgs->icCol, buffer, 10);
        SetWindowText(hwndEditW, buffer);
        itoa(pgs->icMines, buffer, 10);
        SetWindowText(hwndEditM, buffer);

        //get the number array
        ptint = (PINT)lParam;

        //release pgs
        ReleasePGS(pgs);
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            //deal with the input number
            //height
            *((PWORD)buffer) = 10;
            length = SendMessage(hwndEditH, EM_GETLINE, 0, (LPARAM)buffer);
            buffer[length] = '\0';
            CustomGetNumber(ptint, buffer, length, 0); //here use 0 to get height
            //width
            *((PWORD)buffer) = 10;
            buffer[length] = '\0';
            length = SendMessage(hwndEditW, EM_GETLINE, 0, (LPARAM)buffer);
            CustomGetNumber(ptint, buffer, length, 1); //here use 1 to get width
            //mines
            *((PWORD)buffer) = 10;
            length = SendMessage(hwndEditM, EM_GETLINE, 0, (LPARAM)buffer);
            buffer[length] = '\0';
            CustomGetNumber(ptint, buffer, length, 2); // 2

            //finish
            EndDialog(hDlg, 1);
            return TRUE;
        case IDCANCEL:
            EndDialog(hDlg, 0);
        }
        break;
    }
    return FALSE;
}

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            EndDialog(hDlg, 1);
            return TRUE;
        }
        break;
    }
    return FALSE;
}


//CustomGetNumber
void CustomGetNumber(int * threesome, char * buf, int length, int index)
{
    int i;
    int itemp;
    if (buf == NULL || threesome == NULL)
    {
        MessageBox(NULL, "null pointer", "CustomGetNumber", MB_ICONERROR);
        exit(0);
    }

    if (index == 0 || index == 1) //deal with height or width
    {
        if (isdigit(buf[0])) //require digit
        {
            for (i = 0; i < length; i++)
            {
                if (!isdigit(buf[i]))
                {
                    break;
                }
            }

            if (i < length) //not all digit i.e. error input
            {
                threesome[index] = 9; // the default value: 9
            }
            else
            {
                buf[length] = '\0';
                itemp = atoi(buf);
                if (index == 0) //height
                {
                    if (itemp < 9)
                    {
                        threesome[index] = 9;
                    }
                    else if (itemp > 30)
                    {
                        threesome[index] = 30;
                    }
                    else
                    {
                        threesome[index] = itemp;
                    }
                }
                else //width
                {
                    if (itemp < 9)
                    {
                        threesome[index] = 9;
                    }
                    else if (itemp > 24)
                    {
                        threesome[index] = 24;
                    }
                    else
                    {
                        threesome[index] = itemp;
                    }
                }
            }
        }
        else
        {
            threesome[index] = 9; //default value
        }
    }
    else
    {
        if (length == 0)
        {
            threesome[index] = 10; //no string; default value 10
            return;
        }
        for (i = 0; i < length; i++)
        {
            if (!isdigit(buf[i]))
            {
                break;
            }
        }

        if (i < length) //not a number
        {
            threesome[index] = 10; //default mine value
        }
        else
        {
            buf[length] = '\0';
            itemp = atoi(buf);

            if (itemp < 10)
            {
                threesome[index] = itemp;
            }
            else //this situation depends on the row and col
            {
                if (itemp > (threesome[0] - 1) * (threesome[1] - 1))
                {
                    threesome[index] = (threesome[0] -1) * (threesome[1] - 1);
                }
                else
                {
                    threesome[index] = itemp;
                }
            }
        }
    }
}