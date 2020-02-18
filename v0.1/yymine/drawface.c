#include <windows.h>
#include "drawface.h"

static void DrawFaceOrigin(HWND hwnd, HDC hdc)
{
    static POINT WhiteLine[][2] = { {0, 0, 0, 23}, {0, 0, 23, 0},
                                    {0, 1, 22, 1}, {1, 0, 1, 22} };
    static POINT GrayLine[][2] = { {23, 23, 23, 0}, {23, 23, 0, 23},
                                    {22, 23, 22, 1}, {23, 22, 1, 22} };
    HBRUSH hBrGray = CreateSolidBrush(RGB(0xC0, 0xC0, 0xC0));
    HPEN hPenWhite = CreatePen(PS_SOLID, 1, RGB(0xFF, 0xFF, 0xFF));
    HPEN hPenGray = CreatePen(PS_SOLID, 1, RGB(0x80, 0x80, 0x80));
    HPEN hPenTemp;
    POINT ptTemp;

    RECT rect;
    GetClientRect(hwnd, &rect);
    FillRect(hdc, &rect, hBrGray);

    hPenTemp = SelectObject(hdc, hPenWhite);
    MoveToEx(hdc, 0, 0, &ptTemp);
    for (int i = 0; i < sizeof WhiteLine / (sizeof (POINT) * 2); i++)
    {
        MoveToEx(hdc, WhiteLine[i][0].x, WhiteLine[i][0].y, NULL);
        LineTo(hdc, WhiteLine[i][1].x, WhiteLine[i][1].y);
    }
    SelectObject(hdc, hPenGray);
    for (int i = 0; i < sizeof GrayLine / (sizeof (POINT) * 2); i++)
    {
        MoveToEx(hdc, GrayLine[i][0].x, GrayLine[i][0].y, NULL);
        LineTo(hdc, GrayLine[i][1].x, GrayLine[i][1].y);
    }

    SelectObject(hdc, hPenTemp);
    MoveToEx(hdc, ptTemp.x, ptTemp.y, NULL);

    //release
    DeleteObject(hPenWhite);
    DeleteObject(hPenGray);
}

static void DrawFaceClicked(HWND hwnd, HDC hdc)
{
    static POINT GrayLine[][2] = { {0, 0, 24, 0},
                                   {0, 0, 0, 24} };
    HPEN hPenGray = CreatePen(PS_SOLID, 1, RGB(0x80, 0x80, 0x80));
    HPEN hPenTemp;
    POINT ptTemp;
    RECT rect;
    HBRUSH hBrGray = CreateSolidBrush(RGB(0xC0, 0xC0, 0xC0));

    GetClientRect(hwnd, &rect);
    FillRect(hdc, &rect, hBrGray);

    hPenTemp = SelectObject(hdc, hPenGray);
    MoveToEx(hdc, 0, 0, &ptTemp);

    for (int i = 0; i < sizeof GrayLine / (sizeof (POINT) * 2); i++)
    {
        MoveToEx(hdc, GrayLine[i][0].x, GrayLine[i][0].y, NULL);
        LineTo(hdc, GrayLine[i][1].x, GrayLine[i][1].y);
    }

    SelectObject(hdc, hPenTemp);
    MoveToEx(hdc, ptTemp.x, ptTemp.y, NULL);

    //release
    DeleteObject(hPenGray);
    DeleteObject(hBrGray);

    return;
}

void DrawFaceSmile(HWND hwnd, HDC hdc)
{
    static RECT CircleRect = { 4, 4, 21, 21 };
    static RECT SmallRect[] = { {9, 9, 11, 11},
                                {14, 9, 16, 11} };
    static POINT ShapeSmile[] = {8, 14, 9, 15, 10, 16,
                                 14, 16, 15, 15, 16, 14, 17, 13};
    HPEN hPenBlack = CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0x00));
    HBRUSH hBrYellow = CreateSolidBrush(RGB(0xFF, 0xFF, 0x00));
    HBRUSH hBrBlack = CreateSolidBrush(RGB(0x00, 0x00, 0x00));
    HPEN hPenTemp;
    HBRUSH hBrTemp;

    //background
    DrawFaceOrigin(hwnd, hdc);

    hPenTemp = SelectObject(hdc, hPenBlack);
    hBrTemp = SelectObject(hdc, hBrYellow);

    Ellipse(hdc, CircleRect.left, CircleRect.top,
            CircleRect.right, CircleRect.bottom);

    for (int i = 0; i < sizeof SmallRect / sizeof(RECT); i++)
    {
        FillRect(hdc, SmallRect + i, hBrBlack);
    }

    Polyline(hdc, ShapeSmile, sizeof ShapeSmile / sizeof(POINT));

    SelectObject(hdc, hPenTemp);
    SelectObject(hdc, hBrTemp);

    //release
    DeleteObject(hPenBlack);
    DeleteObject(hBrBlack);
    DeleteObject(hBrYellow);

    return;
}


void DrawFaceSmileClicked(HWND hwnd, HDC hdc)
{
    static RECT CircleRect = { 5, 4, 22, 21 };
    static RECT SmallRect[] = { {10, 9, 12, 11},
                                {15, 9, 17, 11} };
    static POINT ShapeSmile[] = {9, 14, 10, 15, 11, 16,
                                 15, 16, 16, 15, 17, 14, 18, 13};
    HPEN hPenBlack = CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0x00));
    HBRUSH hBrYellow = CreateSolidBrush(RGB(0xFF, 0xFF, 0x00));
    HBRUSH hBrBlack = CreateSolidBrush(RGB(0x00, 0x00, 0x00));
    HPEN hPenTemp;
    HBRUSH hBrTemp;

    //background
    DrawFaceClicked(hwnd, hdc);

    hPenTemp = SelectObject(hdc, hPenBlack);
    hBrTemp = SelectObject(hdc, hBrYellow);

    Ellipse(hdc, CircleRect.left, CircleRect.top,
            CircleRect.right, CircleRect.bottom);

    for (int i = 0; i < sizeof SmallRect / sizeof(RECT); i++)
    {
        FillRect(hdc, SmallRect + i, hBrBlack);
    }

    Polyline(hdc, ShapeSmile, sizeof ShapeSmile / sizeof(POINT));

    SelectObject(hdc, hPenTemp);
    SelectObject(hdc, hBrTemp);

    //release
    DeleteObject(hPenBlack);
    DeleteObject(hBrBlack);
    DeleteObject(hBrYellow);

    return;
}

void DrawFaceAmaze(HWND hwnd, HDC hdc)
{
    static RECT CircleRect = { 4, 4, 21, 21 };
    static POINT BlackPt[] = { 9, 8, 15, 8, 8, 9, 9, 9, 10, 9,
                               14, 9, 15, 9, 16, 9, 9, 10, 15, 10,
                               11, 13, 12, 13, 13, 13, 11, 14,
                               13, 14, 10, 15, 14, 15, 11, 16,
                               13, 16, 11, 17, 12, 17, 13, 17 };
    static POINT YellowPt[] = { 8, 8, 10, 8, 14, 8, 16, 8, 8, 10,
                                10, 10, 14, 10, 16, 10, 10, 14,
                                14, 14, 10, 16, 14, 16 };
    HPEN hPenBlack = CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0x00));
    HBRUSH hBrYellow = CreateSolidBrush(RGB(0xFF, 0xFF, 0x00));
    HPEN hPenTemp;
    HBRUSH hBrTemp;

    //background
    DrawFaceOrigin(hwnd, hdc);

    hPenTemp = SelectObject(hdc, hPenBlack);
    hBrTemp = SelectObject(hdc, hBrYellow);

    Ellipse(hdc, CircleRect.left, CircleRect.top,
            CircleRect.right, CircleRect.bottom);

    for (int i = 0; i < sizeof BlackPt / sizeof(POINT); i++)
    {
        SetPixel(hdc, BlackPt[i].x, BlackPt[i].y, RGB(0, 0, 0));
    }
    for (int i = 0; i < sizeof YellowPt / sizeof (POINT); i++)
    {
        SetPixel(hdc, YellowPt[i].x, YellowPt[i].y, RGB(0x80, 0x80, 0x00));
    }

    SelectObject(hdc, hPenTemp);
    SelectObject(hdc, hBrTemp);

    //release
    DeleteObject(hPenBlack);
    DeleteObject(hBrYellow);

    return;
}

void DrawFaceDead(HWND hwnd, HDC hdc)
{
    static RECT CircleRect = { 4, 4, 21, 21 };
    static POINT BlackPt[] = { 8, 8, 10, 8, 14, 8, 16, 8, 9, 9,
                               15, 9, 8, 10, 10, 10, 14, 10,
                               16, 10, 10, 14, 11, 14, 12, 14,
                               13, 14, 14, 14, 9, 15, 15, 15,
                               8, 16, 16, 16 };
    HPEN hPenBlack = CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0x00));
    HBRUSH hBrYellow = CreateSolidBrush(RGB(0xFF, 0xFF, 0x00));
    HPEN hPenTemp;
    HBRUSH hBrTemp;

    //background
    DrawFaceOrigin(hwnd, hdc);

    hPenTemp = SelectObject(hdc, hPenBlack);
    hBrTemp = SelectObject(hdc, hBrYellow);

    Ellipse(hdc, CircleRect.left, CircleRect.top,
            CircleRect.right, CircleRect.bottom);

    for (int i = 0; i < sizeof BlackPt / sizeof(POINT); i++)
    {
        SetPixel(hdc, BlackPt[i].x, BlackPt[i].y, RGB(0, 0, 0));
    }

    SelectObject(hdc, hPenTemp);
    SelectObject(hdc, hBrTemp);

    //release
    DeleteObject(hPenBlack);
    DeleteObject(hBrYellow);

    return;
}

void DrawFaceWin(HWND hwnd, HDC hdc)
{
    static RECT CircleRect = { 4, 4, 21, 21 };
    static POINT BlackPt[] = { 8, 9, 9, 9, 10, 9, 11, 9, 12, 9, 13, 9,
                               14, 9, 15, 9, 16, 9, 7, 10, 8, 10, 9, 10,
                               10, 10, 11, 10, 13, 10, 14, 10, 15, 10,
                               16, 10, 17, 10, 6, 11, 8, 11, 9, 11, 10, 11,
                               11, 11, 13, 11, 14, 11, 15, 11, 16, 11,
                               18, 11, 5, 12, 9, 12, 10, 12, 14, 12, 15, 12,
                               19, 12, 9, 15, 15, 15, 10, 16, 11, 16, 12, 16,
                               13, 16, 14, 16};
    static POINT YellowPt[] = { 8, 12, 16, 12 };
    HPEN hPenBlack = CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0x00));
    HBRUSH hBrYellow = CreateSolidBrush(RGB(0xFF, 0xFF, 0x00));
    HPEN hPenTemp;
    HBRUSH hBrTemp;

    //background
    DrawFaceOrigin(hwnd, hdc);

    hPenTemp = SelectObject(hdc, hPenBlack);
    hBrTemp = SelectObject(hdc, hBrYellow);

    Ellipse(hdc, CircleRect.left, CircleRect.top,
            CircleRect.right, CircleRect.bottom);

    for (int i = 0; i < sizeof BlackPt / sizeof(POINT); i++)
    {
        SetPixel(hdc, BlackPt[i].x, BlackPt[i].y, RGB(0, 0, 0));
    }
    for (int i = 0; i < sizeof YellowPt / sizeof (POINT); i++)
    {
        SetPixel(hdc, YellowPt[i].x, YellowPt[i].y, RGB(0x80, 0x80, 0x00));
    }

    SelectObject(hdc, hPenTemp);
    SelectObject(hdc, hBrTemp);

    //release
    DeleteObject(hPenBlack);
    DeleteObject(hBrYellow);

    return;
}