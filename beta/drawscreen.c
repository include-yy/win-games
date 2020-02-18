#include <windows.h>
#include "drawscreen.h"

void DrawScreenOrigin(HWND hwnd, HDC hdc)
{
    static POINT RedLine[][2] = { {1, 2, 4, 5}, {1, 4, 4, 7},
                                  {1, 6, 4, 9}, {1, 8, 4, 5},
                                  {1, 10, 4, 7},

                                  {1, 12, 4, 15}, {1, 14, 4, 17},
                                  {1, 16, 4, 19}, {1, 18, 4, 15},
                                  {1, 20, 4, 17},

                                  {3, 1, 6, 4}, {5, 1, 8, 4},
                                  {7, 1, 9, 3}, {9, 1, 6, 4},

                                  {3, 11, 5, 9}, {4, 12, 7, 9},
                                  {6, 12, 9, 9}, {8, 12, 10, 10},

                                  {3, 21, 6, 18}, {5, 21, 8, 18},
                                  {7, 21, 9, 19}, {9, 21, 6, 18},

                                  {9, 4, 12, 1}, {9, 6, 12, 3},
                                  {9, 8, 12, 5}, {9, 6, 12, 9},
                                  {9, 8, 12, 11},

                                  {9, 14, 12, 11}, {9, 16, 12, 13},
                                  {9, 18, 12, 15}, {9, 16, 12, 19},
                                  {9, 18, 12, 21} };

    HBRUSH hBrBlack = CreateSolidBrush(RGB(0, 0, 0));
    HPEN hPenRed = CreatePen(PS_SOLID, 1, RGB(0x80, 0x00, 0x00));
    HPEN hPenTemp;
    POINT ptTemp;
    RECT rect;

    GetClientRect(hwnd, &rect);
    FillRect(hdc, &rect, hBrBlack);

    hPenTemp = SelectObject(hdc, hPenRed);
    MoveToEx(hdc, 0, 0, &ptTemp);

    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < sizeof RedLine / (sizeof (POINT) * 2); i++)
        {
            MoveToEx(hdc, RedLine[i][0].x + 13 * j, RedLine[i][0].y, NULL);
            LineTo(hdc, RedLine[i][1].x + 13 * j, RedLine[i][1].y);
        }
    }

    SelectObject(hdc, hPenTemp);
    MoveToEx(hdc, ptTemp.x, ptTemp.y, NULL);

    //release
    DeleteObject(hBrBlack);
    DeleteObject(hPenRed);

    return;
}

void DrawScreenSymbol(HWND hwnd, HDC hdc, int iSymbol)
{
    static POINT ptSegment[7][6] = {
        2, 1, 4, 3, 8, 3, 10, 1, 0, 0, 0, 0,
        1, 2, 3, 4, 3, 8, 1, 10, 0, 0, 0, 0,
        9, 4, 11, 2, 11, 10, 9, 8, 0, 0, 0, 0,
        2, 11, 3, 10, 9, 10, 10, 11, 9, 12, 3, 12,
        1, 12, 3, 14, 3, 18, 1, 20, 0, 0, 0, 0,
        9, 14, 11, 12, 11, 20, 9, 18, 0, 0, 0, 0,
        2, 21, 4, 19, 8, 19, 10, 21, 0, 0, 0, 0 };
    static int ptNumber[7] = { 4, 4, 4, 6, 4, 4, 4 };

    static BOOL fSegment[10][7] = {
        1, 1, 1, 0, 1, 1, 1, //0
        0, 0, 1, 0, 0, 1, 0, //1
        1, 0, 1, 1, 1, 0, 1, //2
        1, 0, 1, 1, 0, 1, 1, //3
        0, 1, 1, 1, 0, 1, 0, //4
        1, 1, 0, 1, 0, 1, 1, //5
        1, 1, 0, 1, 1, 1, 1, //6
        1, 0, 1, 0, 0, 1, 0, //7
        1, 1, 1, 1, 1, 1, 1, //8
        1, 1, 1, 1, 0, 1, 1, //9
    };

    HPEN hPenRed = CreatePen(PS_SOLID, 1, RGB(0xFF, 0, 0));
    HBRUSH hBrRed = CreateSolidBrush(RGB(0xFF, 0, 0));
    HPEN hPenTemp;
    HBRUSH hBrTemp;

    if (iSymbol < -1 || iSymbol > 9)
    {
        MessageBox(NULL, "out of range", "drawscreensymbol", MB_ICONERROR);
        exit(EXIT_FAILURE);
    }

    hPenTemp = SelectObject(hdc, hPenRed);
    hBrTemp = SelectObject(hdc, hBrRed);
    if (iSymbol == -1)
    {
        Polygon(hdc, ptSegment[3], 6);
    }
    else
    {
        for (int i = 0; i < 7; i++)
        {
            if (fSegment[iSymbol][i])
            Polygon(hdc, ptSegment[i], ptNumber[i]);
        }
    }

    SelectObject(hdc, hPenTemp);
    SelectObject(hdc, hBrTemp);

    //release
    DeleteObject(hPenRed);
    DeleteObject(hBrRed);

    return;
}

void DrawScreenDigit(HWND hwnd, HDC hdc, int iNumber)
{
    BOOL fNegative = FALSE;
    if (iNumber < 0)
    {
        fNegative = TRUE;
        iNumber = -iNumber;
    }
    int iDigits[3];
    iDigits[2] = iNumber % 10;
    iNumber /= 10;
    iDigits[1] = iNumber % 10;
    iNumber /= 10;
    iDigits[0] = iNumber % 10;

    DrawScreenOrigin(hwnd, hdc);

    if (fNegative)
    {
        DrawScreenSymbol(hwnd, hdc, -1);
        SetViewportOrgEx(hdc, 13, 0, NULL);
        DrawScreenSymbol(hwnd, hdc, iDigits[1]);
        SetViewportOrgEx(hdc, 26, 0, NULL);
        DrawScreenSymbol(hwnd, hdc, iDigits[2]);
        SetViewportOrgEx(hdc, 0, 0, NULL);
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            SetViewportOrgEx(hdc, 13 * i, 0, NULL);
            DrawScreenSymbol(hwnd, hdc, iDigits[i]);
        }
        SetViewportOrgEx(hdc, 0, 0, NULL);
    }

    return;
}
