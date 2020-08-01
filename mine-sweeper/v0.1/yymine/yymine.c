#include <Windows.h>
#include <stdlib.h>
#include <ctype.h>
#include "Resource.h"
#include "gamestruct.h"
#include "gamewindow.h"
#include "gamemessage.h"

const TCHAR szAppname[] = TEXT("yymine");
const TCHAR szCubicClass[] = TEXT("yyCubic");
const TCHAR szFaceClass[] = TEXT("yyFace");
const TCHAR szCounterScreenClass[] = TEXT("yyCounter");
const TCHAR szTimeScreenClass[] = TEXT("yytime");


HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK CustomDlgProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    hInst = hInstance; 

    WNDCLASS wc;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINE));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = szAppname;
    wc.lpszClassName = szAppname;
    RegisterClass(&wc);

    GameWindowRegisterCubic(szCubicClass);
    GameWindowRegisterFace(szFaceClass);
    GameWindowRegisterCounterScreen(szCounterScreenClass);
    GameWindowRegisterTimeScreen(szTimeScreenClass);

    PGAMESTRUCT pgs = GetPGS();
    GameStructInit(pgs, 9, 9, 10);
    ReleasePGS(pgs);

    HWND hWnd = GameWindowCreateFrame();

    if (!hWnd)
    {
        MessageBox(NULL, TEXT("Create main window fail"), szAppname, MB_OK);
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    //HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_YYMINE));
    //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))


    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int iSelection = IDM_GAME_BEGINNER;
    static int iCustom[3];
    HDC hdc;
    PAINTSTRUCT ps;
    HMENU hMenu;
    PGAMESTRUCT pgs;
    HWND hwndtemp;

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

    case WM_LBUTTONDOWN: 
        pgs = GetPGS();
        //game end
        if (GSGetGameStatus(pgs) == game_win ||
            GSGetGameStatus(pgs) == game_lose)
        {
            ReleasePGS(pgs);
            return 0;
        }

        GSSetLBP(pgs, TRUE);
        hwndtemp = GSGetFaceH(pgs);
        SendMessage(hwndtemp, WM_FACECHANGE, 0, 0); //to be surprised
        ReleasePGS(pgs);
        return 0;

    case WM_LBUTTONUP: //fLeftButtonPressed off
        pgs = GetPGS();
        //game end
        if (GSGetGameStatus(pgs) == game_win ||
            GSGetGameStatus(pgs) == game_lose)
        {
            ReleasePGS(pgs);
            return 0;
        }

        GSSetLBP(pgs, FALSE);
        hwndtemp = GSGetFaceH(pgs);
        SendMessage(hwndtemp, WM_FACECHANGE, 0, 0);
        ReleasePGS(pgs);
        return 0;

    case WM_RBUTTONDOWN: //modify fRightButtonPressed: fRightButtonPressed on
        pgs = GetPGS();
        //game end
        if (GSGetGameStatus(pgs) == game_win ||
            GSGetGameStatus(pgs) == game_lose)
        {
            ReleasePGS(pgs);
            return 0;
        }

        GSSetRBP(pgs, TRUE);
        ReleasePGS(pgs);
        return 0;

    case WM_RBUTTONUP: //fRightButtonPressed off
        pgs = GetPGS();
        //game end
        if (GSGetGameStatus(pgs) == game_win ||
            GSGetGameStatus(pgs) == game_lose)
        {
            ReleasePGS(pgs);
            return 0;
        }

        GSSetRBP(pgs, FALSE);
        ReleasePGS(pgs);
        return 0;

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
            return 0;

        case IDM_GAME_SKILLED:
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
            return 0;

        case IDM_GAME_EXPERT:
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
            return 0;

        case IDM_GAME_CUSTOM:
            if (DialogBoxParam(hInst, TEXT("CustomDlg"), hwnd, CustomDlgProc, (LPARAM)iCustom))
            {
                pgs = GetPGS();
                if (GSGetRow(pgs) == iCustom[0] &&
                    GSGetCol(pgs) == iCustom[1] &&
                    GSGetMine(pgs) == iCustom[2]) //all equal
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
            if (GSGetQuestion(pgs) == TRUE)
            {
                CheckMenuItem(hMenu, IDM_GAME_MARK, MF_UNCHECKED);
                GSSetQuestion(pgs, FALSE);
            }
            else
            {
                CheckMenuItem(hMenu, IDM_GAME_MARK, MF_CHECKED);
                GSSetQuestion(pgs, TRUE);
            }
            ReleasePGS(pgs);
            return 0;

        case IDM_GAME_SOUND:
            pgs = GetPGS();
            if (GSGetSound(pgs) == TRUE)
            {
                CheckMenuItem(hMenu, IDM_GAME_SOUND, MF_UNCHECKED);
                GSSetSound(pgs, FALSE);
            }
            else
            {
                CheckMenuItem(hMenu, IDM_GAME_SOUND, MF_CHECKED);
                GSSetSound(pgs, TRUE);
            }
            ReleasePGS(pgs);
            return 0;

        case IDM_HELP_ABOUT:
            DialogBox(hInst, TEXT("AboutBox"), hwnd, AboutDlgProc);
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


INT_PTR CALLBACK AboutDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
