#include <windows.h>
#include "drawscreen.h"
#include "gamemessage.h"
#include "gamestruct.h"

LRESULT CALLBACK CounterScreenWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    PGAMESTRUCT pgs;
    HWND hwndtemp;

    switch (message)
    {
    case WM_CREATE:
        return 0;

    case WM_LBUTTONDOWN:
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

    case WM_LBUTTONUP:
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

    case WM_RBUTTONDOWN:
        pgs = GetPGS();
        if (GSGetGameStatus(pgs) == game_lose || GSGetGameStatus(pgs) == game_win)
        {
            ReleasePGS(pgs);
            return 0;
        }
        GSSetRBP(pgs, TRUE);
        ReleasePGS(pgs);
        return 0;

    case WM_RBUTTONUP:
        pgs = GetPGS();
        if (GSGetGameStatus(pgs) == game_lose || GSGetGameStatus(pgs) == game_win)
        {
            ReleasePGS(pgs);
            return 0;
        }
        GSSetRBP(pgs, FALSE);
        ReleasePGS(pgs);
        return 0;


    case WM_GAMESTART: //fall through
    case WM_FLAGCHANGE:
        pgs = GetPGS();
        hdc = GetDC(hwnd);
        //draw digit accoridng to iFlagUsed
        DrawScreenDigit(hwnd, hdc, GSGetMine(pgs) - GSGetFlagUsed(pgs));
        ReleaseDC(hwnd, hdc);
        ReleasePGS(pgs);
        return 0;

    case WM_GAMEEND: //game end, it depends on win or lose
        pgs = GetPGS();
        hdc = GetDC(hwnd);
        if (GSGetGameStatus(pgs) == game_win)
        {
            DrawScreenDigit(hwnd, hdc, 0);
        }
        else if (GSGetGameStatus(pgs) == game_lose)
        {
            DrawScreenDigit(hwnd, hdc, GSGetMine(pgs) - GSGetFlagUsed(pgs));
        }
        else
        {
            MessageBox(NULL, TEXT("counterscreenwndproc, bad game status"), TEXT("debug"), MB_ICONERROR);
            exit(1);
        }
        ReleasePGS(pgs);
        ReleaseDC(hwnd, hdc);
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        pgs = GetPGS();
        DrawScreenDigit(hwnd, hdc, GSGetMine(pgs) - GSGetFlagUsed(pgs));
        ReleasePGS(pgs);
        EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
        break;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
