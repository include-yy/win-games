#include <windows.h>
#include "gamemessage.h"

#include "drawscreen.h"
#include "gamestruct.h"
#include "resource.h"

extern HINSTANCE hInst;

LRESULT CALLBACK TimeScreenWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static int iCount;
    PGAMESTRUCT pgs;
    static int fTimerExist;

    switch (message)
    {
    case WM_CREATE:
        return 0;

    case WM_LBUTTONDOWN: //modify the extern value :fLeftButtonPressed on
        pgs = GetPGS();
        pgs->fLeftButtonPressed = TRUE;
        SendMessage(pgs->hwndFace, WM_FACECHANGE, 0, 0); //to be surprised
        ReleasePGS(pgs);
        return 0;

    case WM_LBUTTONUP: //fLeftButtonPressed off
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

    case WM_GAMESTART:
        //debug info
        MessageBox(NULL, "start", "S", MB_OK);
        SetTimer(hwnd, 1, 1000, NULL);
        fTimerExist = TRUE;
        return 0;

    case WM_TIMER:
        pgs = GetPGS();
        if (pgs->iTotalTime == 999) //about to exceed screen range
        {
            KillTimer(hwnd, 1);
            fTimerExist = FALSE;
            return 0;
        }
        hdc = GetDC(hwnd);
        if (pgs->iGameStatus == game_ing) //game ing
        {
            pgs->iTotalTime += 1; //time passed one second
        }

        DrawScreenDigit(hwnd, hdc, pgs->iTotalTime);

        if (pgs->iGameStatus == game_ing) //game ing
        if (pgs->fPlaySound)
        {
            PlaySound(MAKEINTRESOURCE(IDV_TIMER), hInst, SND_ASYNC | SND_RESOURCE);
        }
        ReleasePGS(pgs);
        ReleaseDC(hwnd, hdc);

        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        pgs = GetPGS();
        DrawScreenDigit(hwnd, hdc, pgs->iTotalTime);
        EndPaint(hwnd, &ps);
        ReleasePGS(pgs);
        return 0;

    case WM_GAMEEND:
        if (fTimerExist)
        {
            KillTimer(hwnd, 1);
        }
        return 0;

    case WM_DESTROY:
        break;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}