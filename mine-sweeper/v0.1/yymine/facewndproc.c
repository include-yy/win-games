#include <windows.h>
#include "drawface.h"
#include "gamemessage.h"
#include "gamestruct.h"
#include "gamewindow.h"
#include "Resource.h"

LRESULT CALLBACK FaceWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int fownLbuttonPressed = FALSE;
    HDC hdc;
    PAINTSTRUCT ps;
    PGAMESTRUCT pgs;
    TRACKMOUSEEVENT tme;

    switch (message)
    {
    case WM_CREATE:
        return 0;

    case WM_GAMESTART: //fall through
    case WM_FACECHANGE:
        hdc = GetDC(hwnd);
        pgs = GetPGS();
        if (GSGetGameStatus(pgs) == game_lose)
        {
            DrawFaceDead(hwnd, hdc);
        }
        else
        {
            if (GSGetLBP(pgs) == TRUE)
            {
                DrawFaceAmaze(hwnd, hdc);
            }
            else
            {
                DrawFaceSmile(hwnd, hdc);
            }
        }
        ReleasePGS(pgs);
        ReleaseDC(hwnd, hdc);
        return 0;

    case WM_LBUTTONDOWN:
        fownLbuttonPressed = TRUE; //l-button click on it
        hdc = GetDC(hwnd);
        DrawFaceSmileClicked(hwnd, hdc);
        ReleaseDC(hwnd, hdc);

        tme.cbSize = sizeof(TRACKMOUSEEVENT); //used for leave with l-button not release
        tme.hwndTrack = hwnd;
        tme.dwFlags = TME_LEAVE;
        TrackMouseEvent(&tme);
        return 0;

    case WM_LBUTTONUP:
        pgs = GetPGS();
        GSSetLBP(pgs, FALSE);
        //pgs->fLeftButtonPressed = FALSE; // release extern l-button
        SendMessage(hwnd, WM_FACECHANGE, 0, 0);
        ReleasePGS(pgs);

        hdc = GetDC(hwnd);
        DrawFaceSmile(hwnd, hdc);
        ReleaseDC(hwnd, hdc);
        if (fownLbuttonPressed == TRUE)
        {
            SendMessage(GetParent(hwnd), WM_COMMAND, IDM_GAME_NEW, 0);
        }
        fownLbuttonPressed = FALSE;
        return 0;

    case WM_MOUSELEAVE: //line : 42
        if (fownLbuttonPressed == TRUE)
        {
            fownLbuttonPressed = FALSE;
            SendMessage(hwnd, WM_FACECHANGE, 0, 0);
        }
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        DrawFaceSmile(hwnd, hdc);
        EndPaint(hwnd, &ps);
        return 0;

    case WM_GAMEEND: //game end, win or lose
        pgs = GetPGS();
        hdc = GetDC(hwnd);
        if (GSGetGameStatus(pgs) == game_win)
        {
            DrawFaceWin(hwnd, hdc);
        }
        else if (GSGetGameStatus(pgs) == game_lose)
        {
            DrawFaceDead(hwnd, hdc);
        }
        else
        {
            MessageBox(NULL, TEXT("facewndproc"), TEXT("game status error"), MB_ICONERROR);
            exit(1);
        }
        ReleasePGS(pgs);
        ReleaseDC(hwnd, hdc);
        return 0;

    case WM_DESTROY:
        break;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}