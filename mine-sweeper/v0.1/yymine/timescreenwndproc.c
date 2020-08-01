#pragma comment(lib,"winmm.lib")

#include <windows.h>
#include "gamemessage.h"
#include "drawscreen.h"
#include "gamestruct.h"
#include "resource.h"

extern HINSTANCE hInst;

LRESULT CALLBACK TimeScreenWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int fTimerExist = FALSE;
    HDC hdc;
    PAINTSTRUCT ps;
    PGAMESTRUCT pgs;
    HWND hwndtemp;

    switch (message)
    {
    case WM_CREATE:
        return 0;

    case WM_LBUTTONDOWN: //modify the extern value :fLeftButtonPressed on
        pgs = GetPGS();
        if (GSGetGameStatus(pgs) == game_lose || GSGetGameStatus(pgs) == game_win)
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
        if (GSGetGameStatus(pgs) == game_lose || GSGetGameStatus(pgs) == game_win)
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
        if (GSGetGameStatus(pgs) == game_lose || GSGetGameStatus(pgs) == game_win)
        {
            ReleasePGS(pgs);
            return 0;
        }
        GSSetRBP(pgs, TRUE);
        ReleasePGS(pgs);
        return 0;

    case WM_RBUTTONUP: //fRightButtonPressed off
        pgs = GetPGS();
        if (GSGetGameStatus(pgs) == game_lose || GSGetGameStatus(pgs) == game_win)
        {
            ReleasePGS(pgs);
            return 0;
        }

        GSSetRBP(pgs, FALSE);
        ReleasePGS(pgs);
        return 0;

    case WM_GAMESTART:
        SetTimer(hwnd, 1, 1000, NULL);
        fTimerExist = TRUE;
        return 0;

    case WM_TIMER:
        pgs = GetPGS();
        if (GSGetTotalTime(pgs) == 999) //about to exceed screen range
        {
            KillTimer(hwnd, 1);
            fTimerExist = FALSE;
            return 0;
        }
        hdc = GetDC(hwnd);
        if (GSGetGameStatus(pgs) == game_ing) //game ing
        {
            GSSetTotalTime(pgs, GSGetTotalTime(pgs) + 1);
        }

        DrawScreenDigit(hwnd, hdc, GSGetTotalTime(pgs));

        if (GSGetGameStatus(pgs) == game_ing) //game ing
        if (GSGetSound(pgs) == TRUE)
        {
            PlaySound(MAKEINTRESOURCE(IDV_TIMER), hInst, SND_ASYNC | SND_RESOURCE);
        }
        ReleasePGS(pgs);
        ReleaseDC(hwnd, hdc);

        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        pgs = GetPGS();
        DrawScreenDigit(hwnd, hdc, GSGetTotalTime(pgs));
        EndPaint(hwnd, &ps);
        ReleasePGS(pgs);
        return 0;

    case WM_GAMEEND:
        if (fTimerExist)
        {
            KillTimer(hwnd, 1);
            fTimerExist = FALSE;
        }
        return 0;

    case WM_DESTROY:
        break;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}