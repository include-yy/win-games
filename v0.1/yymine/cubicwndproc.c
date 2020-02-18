#pragma comment(lib,"winmm.lib")
#include <windows.h>
#include "drawcubic.h"
#include "gamemessage.h"
#include "gamestruct.h"
#include <stdio.h>
#include <stdlib.h>
#include "Resource.h"

extern HINSTANCE hInst;

LRESULT CALLBACK CubicWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    PGAMESTRUCT pgs;
    int ipt;
    int itemp;
    int id;
    int irow, icol;
    
    static int currId = -1;

    //used for click mine
    PINT pArray;
    int iArrLength;
    int flose;

    switch (message)
    {
    case WM_CREATE:
        return 0;

    case WM_GAMESTART:
        pgs = GetPGS();
        GSSetGameStatus(pgs, game_ing);
        SendMessage(GSGetFaceH(pgs), WM_GAMESTART, 0, 0);
        SendMessage(GSGetTimeH(pgs), WM_GAMESTART, 0, 0);
        SendMessage(GSGetCounterH(pgs), WM_GAMESTART, 0, 0);
        ReleasePGS(pgs);
        return 0;

    case WM_MOUSEMOVE:
        pgs = GetPGS();
        if (GetDlgCtrlID(hwnd) != currId)
        {
            if (currId >= 0 && currId < GSGetCubic(pgs))
            {
                SendMessage(GSGetCubicH(pgs, currId), WM_MSLEAVE, 0, 0);
            }

            currId = GetDlgCtrlID(hwnd);
            if (GSGetLBP(pgs) == TRUE)
            {
                if (GSGetRBP(pgs) == FALSE)
                {
                    if (GSGetCheckKind(pgs, currId) == click_no ||
                        GSGetCheckKind(pgs, currId) == click_mark)
                    {
                        hdc = GetDC(hwnd);
                        DrawCubicClicked(hwnd, hdc);
                        ReleaseDC(hwnd, hdc);
                    }
                }
                else
                {
                    irow = currId / GSGetCol(pgs);
                    icol = currId % GSGetCol(pgs);
                    for (int i = irow - 1; i <= irow + 1; i++)
                    {
                        for (int j = icol - 1; j <= icol + 1; j++)
                        {
                            if (i < 0 || i >= GSGetRow(pgs) ||
                                j < 0 || j >= GSGetCol(pgs))
                                continue;
                            int kid = i * GSGetCol(pgs) + j;
                            SendMessage(GSGetCubicH(pgs, kid), WM_TEMCLICK, 0, 0);
                        }
                    }
                }
            }
        }
        ReleasePGS(pgs);
        return 0;

    case WM_MSLEAVE:
        pgs = GetPGS();
        irow = currId / GSGetCol(pgs);
        icol = currId % GSGetCol(pgs);
        for (int i = irow - 1; i <= irow + 1; i++)
        {
            for (int j = icol - 1; j <= icol + 1; j++)
            {
                if (i < 0 || i >= GSGetRow(pgs) ||
                    j < 0 || j >= GSGetCol(pgs))
                    continue;
                int kid = i * GSGetCol(pgs) + j;
                InvalidateRect(GSGetCubicH(pgs, kid), NULL, TRUE);
                SendMessage(GSGetCubicH(pgs, kid), WM_PAINT, 0, 0);
            }
        }
        ReleasePGS(pgs);
        return 0;

    case WM_TEMCLICK:
        pgs = GetPGS();
        if (GSGetCheckKind(pgs, GetDlgCtrlID(hwnd)) == click_no ||
            GSGetCheckKind(pgs, GetDlgCtrlID(hwnd)) == click_mark)
        {
            hdc = GetDC(hwnd);
            DrawCubicClicked(hwnd, hdc);
            ReleaseDC(hwnd, hdc);
        }
        ReleasePGS(pgs);
        return 0;

    case WM_LBUTTONDOWN:
        pgs = GetPGS();
        //game end
        if (GSGetGameStatus(pgs) == game_lose ||
            GSGetGameStatus(pgs) == game_win)
        {
            ReleasePGS(pgs);
            return 0;
        }

        GSSetLBP(pgs, TRUE);
        SendMessage(GSGetFaceH(pgs), WM_FACECHANGE, 0, 0);
        itemp = GetDlgCtrlID(hwnd);
        if (GSGetRBP(pgs) == FALSE)
        {
            if ((GSGetCheckKind(pgs, itemp) != click_no) && 
                (GSGetCheckKind(pgs, itemp) != click_mark))
            {
                ;
            }
            else
            {
                hdc = GetDC(hwnd);
                DrawCubicClicked(hwnd, hdc);
                ReleaseDC(hwnd, hdc);
                ReleasePGS(pgs);
            }
        }
        else
        {
            irow = GetDlgCtrlID(hwnd) / GSGetCol(pgs);
            icol = GetDlgCtrlID(hwnd) % GSGetCol(pgs);
            for (int i = irow - 1; i <= irow + 1; i++)
            {
                for (int j = icol - 1; j <= icol + 1; j++)
                {
                    if (i < 0 || i >= GSGetRow(pgs) ||
                        j < 0 || j >= GSGetCol(pgs))
                        continue;
                    int kid = i * GSGetCol(pgs) + j;
                    SendMessage(GSGetCubicH(pgs, kid), WM_TEMCLICK, 0, 0);
                    
                }
            }
        }
        ReleasePGS(pgs);
        return 0;

    case WM_LBUTTONUP:
        pgs = GetPGS();
        //game end
        if (GSGetGameStatus(pgs) == game_lose ||
            GSGetGameStatus(pgs) == game_win)
        {
            ReleasePGS(pgs);
            return 0;
        }

        GSSetLBP(pgs, FALSE);
        SendMessage(GSGetFaceH(pgs), WM_FACECHANGE, 0, 0);

        if (GSGetGameStatus(pgs) == game_ready) //game start
        {
            SendMessage(hwnd, WM_GAMESTART, 0, 0);
        }

        //get id
        id = GetDlgCtrlID(hwnd);
        if (GSGetRBP(pgs) == TRUE)
        {
            SendMessage(hwnd, WM_MSLEAVE, 0, 0);
        }

        if (GSGetRBP(pgs) == TRUE)
        {
            if (GSGetCheckKind(pgs, id) == click_yes)
            {
                SendMessage(hwnd, WM_CLICKBOOM, 0, 0);
            }
        }
        else if (GSGetCheckKind(pgs, id) == click_flag)
        {
            ;
        }
        else 
        {
            SendMessage(hwnd, WM_CLICKBOOM, 0, 0);
        }
        ReleasePGS(pgs);
        return 0;

    case WM_RBUTTONDOWN:
        pgs = GetPGS();
        //game end
        if (GSGetGameStatus(pgs) == game_lose ||
            GSGetGameStatus(pgs) == game_win)
        {
            ReleasePGS(pgs);
            return 0;
        }

        GSSetRBP(pgs, TRUE);
        itemp = GetDlgCtrlID(hwnd);
        if (GSGetLBP(pgs) == TRUE)
        {
            irow = currId / GSGetCol(pgs);
            icol = currId % GSGetCol(pgs);
            for (int i = irow - 1; i <= irow + 1; i++)
            {
                for (int j = icol - 1; j <= icol + 1; j++)
                {
                    if (i < 0 || i >= GSGetRow(pgs) ||
                        j < 0 || j >= GSGetCol(pgs))
                        continue;
                    int kid = i * GSGetCol(pgs) + j;
                    SendMessage(GSGetCubicH(pgs, kid), WM_TEMCLICK, 0, 0);
                }
            }
        }
        else
        {
            if (GSGetCheckKind(pgs, itemp) == click_yes)
            {
                ReleasePGS(pgs);
                return 0;
            }
            else if (GSGetCheckKind(pgs, itemp) == click_no)
            {
                GSSetCheckKind(pgs, itemp, click_flag);
                GSSetFlagUsed(pgs, GSGetFlagUsed(pgs) + 1);
                SendMessage(GSGetCounterH(pgs), WM_FLAGCHANGE, 0, 0);
                
                InvalidateRect(hwnd, NULL, TRUE);

                //logic rest mine
                if (GSIsHaveMine(pgs, itemp) == TRUE)
                {
                    GSSetRestMine(pgs, GSGetRestMine(pgs) - 1);
                }

                //game win
                if (GameStructIsWin(pgs))
                {
                    SendMessage(hwnd, WM_GAMEEND, GAMEEND_WIN, 0);
                    return 0;
                }
            }
            else if (GSGetCheckKind(pgs, itemp) == click_flag)
            {
                if (GSGetQuestion(pgs) == TRUE)
                    GSSetCheckKind(pgs, itemp, click_mark);
                else
                    GSSetCheckKind(pgs, itemp, click_no);
                InvalidateRect(hwnd, NULL, TRUE);
                GSSetFlagUsed(pgs, GSGetFlagUsed(pgs) - 1);
                SendMessage(GSGetCounterH(pgs), WM_FLAGCHANGE, 0, 0);

                //logic rest mine
                if (GSIsHaveMine(pgs, itemp) == TRUE)
                {
                    GSSetRestMine(pgs, GSGetRestMine(pgs) - 1);
                }
            }
            else if (GSGetCheckKind(pgs, itemp) == click_mark)
            {
                GSSetCheckKind(pgs, itemp, click_no);
                InvalidateRect(hwnd, NULL, TRUE);
            }
            else
            {
                MessageBox(NULL, TEXT("click error WM_RBUTTON cubicwndproc"), TEXT("debug"), MB_ICONERROR);
                exit(1);
            }
        }
        ReleasePGS(pgs);
        return 0;

    case WM_RBUTTONUP:
        pgs = GetPGS();
        //game end
        if (GSGetGameStatus(pgs) == game_lose ||
            GSGetGameStatus(pgs) == game_win)
        {
            ReleasePGS(pgs);
            return 0;
        }

        GSSetRBP(pgs, FALSE);
        if (GSGetLBP(pgs) == TRUE)
        {
            SendMessage(hwnd, WM_MSLEAVE, 0, 0);

            if (GSGetGameStatus(pgs) == game_ready)
            {
                SendMessage(hwnd, WM_GAMESTART, 0, 0);
            }

            id = GetDlgCtrlID(hwnd);

            if (GSGetCheckKind(pgs, id) == click_yes)
            {
                SendMessage(hwnd, WM_CLICKBOOM, 0, 0);
            }
        }
        ReleasePGS(pgs);
        return 0;

    case WM_PAINT:
        pgs = GetPGS();
        hdc = BeginPaint(hwnd, &ps);
        ipt = GetDlgCtrlID(hwnd);
        if (GSGetCheckKind(pgs, ipt) == click_no)
            DrawCubicOrigin(hwnd, hdc);
        else if (GSGetCheckKind(pgs, ipt) == click_yes)
        {
            /*if (GSAroundMine(pgs, ipt) == -1)
            {
                if (GSGetMineStatus(pgs, ipt) == mine_normal)
                    DrawCubicMine(hwnd, hdc);
                else if (GSGetMineStatus(pgs, ipt) == mine_mistake)
                    DrawCubicMistakeMine(hwnd, hdc);
                else if (GSGetMineStatus(pgs, ipt) == mine_click)
                    DrawCubicFailMine(hwnd, hdc);
                else
                {
                    MessageBox(NULL, TEXT("error cubicwndproc mine"), TEXT("debug"), MB_ICONERROR);
                    exit(1);
                }
            }*/
            if (GSGetMineStatus(pgs, ipt) == mine_click)
                DrawCubicFailMine(hwnd, hdc);
            else if (GSGetMineStatus(pgs, ipt) == mine_mistake)
                DrawCubicMistakeMine(hwnd, hdc);
            else if (GSGetMineStatus(pgs, ipt) == mine_normal)
                DrawCubicMine(hwnd, hdc);
            else if (GSGetMineStatus(pgs, ipt) == mine_no)
                DrawCubicDigit(hwnd, hdc, GSAroundMine(pgs, ipt));
            else
            {
                MessageBox(NULL, TEXT("mine status error"), TEXT("cubic: WM_PAINT"), MB_ICONERROR);
                exit(1);
            }
        }
        else if (GSGetCheckKind(pgs, ipt) == click_flag)
            DrawCubicFlag(hwnd, hdc);
        else if (GSGetCheckKind(pgs, ipt) == click_mark)
            DrawCubicQuestion(hwnd, hdc);
        else
        {
            MessageBox(NULL, TEXT("error cubicwndproc click"), TEXT("debug"), MB_ICONERROR);
            exit(1);
        }
        EndPaint(hwnd, &ps);
        ReleasePGS(pgs);
        return 0;

    case WM_CLICKBOOM:
        pgs = GetPGS();
        pArray = (int*)malloc(sizeof(int) * GSGetCubic(pgs));
        if (pArray == NULL)
        {
            MessageBox(NULL, TEXT("alloc error"), TEXT("WM_CLICKBOOM"), MB_ICONERROR);
            exit(1);
        }

        flose = GameStructClick(pgs, GetDlgCtrlID(hwnd), pArray, &iArrLength);

        for (int i = 0; i < iArrLength; i++)
        {
            InvalidateRect(GSGetCubicH(pgs, pArray[i]), NULL, TRUE);
        }
        
        //free memory
        //if i use this, the program will crash soon. but i don't know how to fix it.
        //so let the memory leak.
        //free(pArray);

        if (flose == TRUE)
        {
            SendMessage(hwnd, WM_GAMEEND, GAMEEND_LOSE, 0);
        }
        else
        {
            if (GameStructIsWin(pgs))
            {
                SendMessage(hwnd, WM_GAMEEND, GAMEEND_WIN, 0);
            }
        }
        //MessageBox(NULL, TEXT("Get click"), TEXT("CLICKBOOM"), MB_OK);
        ReleasePGS(pgs);
        return 0;

    case WM_GAMEEND:
        pgs = GetPGS();
        if (wParam == GAMEEND_WIN)
        {
            GSSetGameStatus(pgs, game_win);
            if (GSGetSound(pgs) == TRUE)
                PlaySound(MAKEINTRESOURCE(IDV_WIN), hInst, SND_ASYNC | SND_RESOURCE);
        }
        else if (wParam == GAMEEND_LOSE)
        {
            GSSetGameStatus(pgs, game_lose);
            if (GSGetSound(pgs) == TRUE)
                PlaySound(MAKEINTRESOURCE(IDV_LOSE), hInst, SND_ASYNC | SND_RESOURCE);

            for (int i = 0; i < GSGetCubic(pgs); i++)
            {
                if (GSGetMineStatus(pgs, i) == mine_normal &&
                    GSGetCheckKind(pgs, i) == click_no)
                {
                    GSSetCheckKind(pgs, i, click_yes);
                    InvalidateRect(GSGetCubicH(pgs, i), NULL, TRUE);
                }
            }
        }
        else
        {
            MessageBox(NULL, TEXT("gameend arg error"), TEXT("WM_GAMEEND"), MB_ICONERROR);
            exit(1);
        }
        SendMessage(GSGetFaceH(pgs), WM_GAMEEND, 0, 0);
        SendMessage(GSGetCounterH(pgs), WM_GAMEEND, 0, 0);
        SendMessage(GSGetTimeH(pgs), WM_GAMEEND, 0, 0);

        return 0;

    case WM_DESTROY:
        break;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}