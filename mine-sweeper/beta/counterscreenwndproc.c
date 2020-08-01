#include <windows.h>
#include "drawscreen.h"
#include "gamemessage.h"
#include "gamestruct.h"

LRESULT CALLBACK CounterScreenWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    PGAMESTRUCT pgs;

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


    case WM_GAMESTART: //fall through
    case WM_FLAGCHANGE:
        pgs = GetPGS();
        hdc = GetDC(hwnd);
        //draw digit accoridng to iFlagUsed
        DrawScreenDigit(hwnd, hdc, pgs->icMines - pgs->iFlagUsed);
        ReleaseDC(hwnd, hdc);
        ReleasePGS(pgs);
        return 0;

    case WM_GAMEEND: //game end, it depends on win or lose
        pgs = GetPGS();
        hdc = GetDC(hwnd);
        if (pgs->iGameStatus == game_win)
        {
            DrawScreenDigit(hwnd, hdc, 0);
        }
        else
        {
            DrawScreenDigit(hwnd, hdc, pgs->icMines - pgs->iFlagUsed);
        }
        ReleasePGS(pgs);
        ReleaseDC(hwnd, hdc);
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        pgs = GetPGS();
        DrawScreenDigit(hwnd, hdc, pgs->icMines - pgs->iFlagUsed);
        ReleasePGS(pgs);
        EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
        break;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
