#include <windows.h>
#include "drawcubic.h"
#include "gamemessage.h"
#include "gamestruct.h"
#include <stdio.h>

LRESULT CALLBACK CubicWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    PGAMESTRUCT pgs;
    char buf[20];
    int id;

    switch (message)
    {
    case WM_CREATE:
       return 0;

    case WM_LBUTTONDOWN:
        hdc = GetDC(hwnd);
        pgs = GetPGS();
        pgs->fLeftButtonPressed = TRUE;

        SendMessage(pgs->hwndFace, WM_FACECHANGE, 0, 0);
        DrawCubicClicked(hwnd, hdc);

        ReleaseDC(hwnd, hdc);
        ReleasePGS(pgs);
        return 0;

    case WM_LBUTTONUP:
        //left for another choice
        hdc = GetDC(hwnd);
        pgs = GetPGS();
        pgs->fLeftButtonPressed = FALSE;
        //MessageBox(NULL, "cubicwndproc line:35", "debug", MB_OK);
        SendMessage(pgs->hwndFace, WM_FACECHANGE, 0, 0);
        if (pgs->iGameStatus == game_ready)
        {
            //MessageBox(NULL, "cubicwndproc line:39 game_ing", "debug", MB_OK);
            pgs->iGameStatus = game_ing;
            SendMessage(pgs->hwndTimeScreen, WM_GAMESTART, 0, 0);
        }

        //get id
        id = GetDlgCtrlID(hwnd);
        if (pgs->pcAroundMine[id] == -1)
        {
            DrawCubicMine(hwnd, hdc);
        }
        else
        {
            DrawCubicDigit(hwnd, hdc, pgs->pcAroundMine[id]);
        }
        ReleaseDC(hwnd, hdc);
        ReleasePGS(pgs);
        return 0;

    case WM_RBUTTONUP:
        pgs = GetPGS();
        if (pgs->iGameStatus == game_ing)
        {
            pgs->iGameStatus = game_win;
            SendMessage(pgs->hwndTimeScreen, WM_GAMEEND, 0, 0);
        }
        ReleasePGS(pgs);
        return 0;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        DrawCubicOrigin(hwnd, hdc);
        EndPaint(hwnd, &ps);
        return 0;

    case WM_DESTROY:
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}