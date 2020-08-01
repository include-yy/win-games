#include <windows.h>
#include "drawcubic.h"

void DrawCubicOrigin(HWND hwnd, HDC hdc)
{
    RECT rect;
    static POINT upPart[] =   {0, 0, 14, 0, 13, 1, 1, 1, 1, 13, 0, 14, 0, 0};
    static POINT downPart[] = {15, 15, 1, 15, 2, 14, 14, 14, 14, 2, 15, 1, 15, 15};

    HBRUSH hBr = CreateSolidBrush(RGB(0xC0, 0xC0, 0xC0));
    HPEN hPenUp = CreatePen(PS_SOLID, 1, RGB(0xFF, 0xFF, 0xFF));
    HPEN hPenDown = CreatePen(PS_SOLID, 1, RGB(0x80, 0x80, 0x80));
    HPEN hPenTemp;

    //draw background and lines
    GetClientRect(hwnd, &rect);
    FillRect(hdc, &rect, hBr);
    hPenTemp = SelectObject(hdc, hPenUp);
    Polyline(hdc, upPart, sizeof upPart / sizeof (POINT));
    SelectObject(hdc, hPenDown);
    Polyline(hdc, downPart, sizeof downPart / sizeof (POINT));

    SelectObject(hdc, hPenTemp);
    //release pens and brush
    DeleteObject(hBr);
    DeleteObject(hPenDown);
    DeleteObject(hPenUp);

    return;
}

void DrawCubicClicked(HWND hwnd, HDC hdc)
{
    RECT rect;
    HBRUSH hBr = CreateSolidBrush(RGB(0xC0, 0xC0, 0xC0));
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0x80, 0x80, 0x80));
    HPEN hPenTemp;
    POINT ptTemp;

    MoveToEx(hdc, 0, 0, &ptTemp);
    //draw lines
    GetClientRect(hwnd, &rect);
    FillRect(hdc, &rect, hBr);
    hPenTemp = SelectObject(hdc, hPen);
    LineTo(hdc, 0, 16);
    MoveToEx(hdc, 0, 0, NULL);
    LineTo(hdc, 16, 0);

    SelectObject(hdc, hPenTemp);
    MoveToEx(hdc, ptTemp.x, ptTemp.y, NULL);
    //relase pen and brush
    DeleteObject(hPen);
    DeleteObject(hBr);

    return;
}

void DrawCubicOne(HWND hwnd, HDC hdc)
{
    static POINT ShapeOne[] = { 5, 6, 8, 3, 9, 3, 9, 11, 11, 11,
                                11, 12, 5, 12, 5, 11, 7, 11, 7, 6, 5, 6 };
    HPEN hPenBlue = CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0xFF));
    HBRUSH hBrBlue = CreateSolidBrush(RGB(0x00, 0x00, 0xFF));
    HPEN hPenTemp;
    HBRUSH hBrushTemp;

    //background
    DrawCubicClicked(hwnd, hdc);

    hPenTemp = SelectObject(hdc, hPenBlue);
    hBrushTemp = SelectObject(hdc, hBrBlue);
    Polygon(hdc, ShapeOne, sizeof ShapeOne / sizeof(POINT));

    SelectObject(hdc, hPenTemp);
    SelectObject(hdc, hBrushTemp);

    //release
    DeleteObject(hPenBlue);
    DeleteObject(hBrBlue);

    return;
}

void DrawCubicTwo(HWND hwnd, HDC hdc)
{
    static POINT ShapeTwo[] = { 3, 4, 4, 3, 11, 3, 12, 4, 12, 6, 11, 7,
                                10, 8, 7, 8, 8, 9, 6, 9, 6, 11, 12, 11,
                                12, 12, 3, 12, 3, 10, 4, 9, 6, 9, 6, 8,
                                8, 8, 8, 7, 10, 7, 10, 4, 5, 4, 5, 5,
                                3, 5, 3, 4};
    HPEN hPenGreen = CreatePen(PS_SOLID, 1, RGB(0x00, 0x80, 0x00));
    HBRUSH hBrGreen = CreateSolidBrush(RGB(0x00, 0x80, 0x00));
    HPEN hPenTemp;
    HBRUSH hBrushTemp;

    //background
    DrawCubicClicked(hwnd, hdc);

    hPenTemp = SelectObject(hdc, hPenGreen);
    hBrushTemp = SelectObject(hdc, hBrGreen);
    Polygon(hdc, ShapeTwo, sizeof ShapeTwo / sizeof(POINT));

    SelectObject(hdc, hPenTemp);
    SelectObject(hdc, hBrushTemp);

    //release
    DeleteObject(hPenGreen);
    DeleteObject(hBrGreen);

    return;
}

void DrawCubicThree(HWND hwnd, HDC hdc)
{
    static POINT ShapeThree[][2] = { {3, 3, 12, 3}, {3, 4, 13, 4},
                                     {10, 5, 13, 5}, {10, 6, 13, 6},
                                     {6, 7, 12, 7}, {6, 8, 12, 8},
                                     {10, 9, 13, 9}, {10, 10, 13, 10},
                                     {3, 11, 13, 11}, {3, 12, 12, 12} };

    HPEN hPenRed = CreatePen(PS_SOLID, 1, RGB(0xFF, 0x00, 0x00));
    HPEN hPenTemp;
    POINT ptTemp;

    hPenTemp = SelectObject(hdc, hPenRed);

    //background
    DrawCubicClicked(hwnd, hdc);

    MoveToEx(hdc, 0, 0, &ptTemp);
    for (int i = 0; i < sizeof ShapeThree / (sizeof (POINT) * 2); i++)
    {
        MoveToEx(hdc, ShapeThree[i][0].x, ShapeThree[i][0].y, NULL);
        LineTo(hdc, ShapeThree[i][1].x, ShapeThree[i][1].y);
    }

    SelectObject(hdc, hPenTemp);
    MoveToEx(hdc, ptTemp.x, ptTemp.y, NULL);
    //release
    DeleteObject(hPenRed);

    return;
}

void DrawCubicFour(HWND hwnd, HDC hdc)
{
    static POINT ShapeFour[][2] = { {5, 3, 8, 3}, {5, 4, 8, 4},
                                    {4, 5, 7, 5}, {4, 6, 7, 6},
                                    {3, 7, 13, 7}, {3, 8, 13, 8},
                                    {9, 3, 9, 13}, {10, 3, 10, 13},
                                    {11, 3, 11, 13} };

    HPEN hPenDeepBlue = CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0x80));
    HPEN hPenTemp;
    POINT ptTemp;

    hPenTemp = SelectObject(hdc, hPenDeepBlue);

    //background
    DrawCubicClicked(hwnd, hdc);

    MoveToEx(hdc, 0, 0, &ptTemp);
    for (int i = 0; i < sizeof ShapeFour / (sizeof(POINT) * 2); i++)
    {
        MoveToEx(hdc, ShapeFour[i][0].x, ShapeFour[i][0].y, NULL);
        LineTo(hdc, ShapeFour[i][1].x, ShapeFour[i][1].y);
    }

    SelectObject(hdc, hPenTemp);
    MoveToEx(hdc, ptTemp.x, ptTemp.y, NULL);

    //release
    DeleteObject(hPenDeepBlue);

    return;
}

void DrawCubicFive(HWND hwnd, HDC hdc)
{
    static POINT ShapeFive[] = { 3, 3, 12, 3, 12, 4, 5, 4, 5, 7, 11, 7,
                                 12, 8, 12, 11, 11, 12, 3, 12, 3, 11,
                                 10, 11, 10, 8, 3, 8, 3, 3};

    HPEN hPenDeepRed = CreatePen(PS_SOLID, 1, RGB(0x80, 0x00, 0x00));
    HBRUSH hBrDeepRed = CreateSolidBrush(RGB(0x80, 0x00, 0x00));
    HPEN hPenTemp;
    HBRUSH hBrushTemp;

    hPenTemp = SelectObject(hdc, hPenDeepRed);
    hBrushTemp = SelectObject(hdc, hBrDeepRed);

    //background
    DrawCubicClicked(hwnd, hdc);

    Polygon(hdc, ShapeFive, sizeof ShapeFive / sizeof(POINT));

    SelectObject(hdc, hPenTemp);
    SelectObject(hdc, hBrushTemp);

    //release
    DeleteObject(hPenDeepRed);
    DeleteObject(hBrDeepRed);

    return;
}

void DrawCubicSix(HWND hwnd, HDC hdc)
{
    static POINT ShapeSix[][2] = { {4, 3, 12, 3}, {3, 4, 12, 4},
                                   {3, 7, 12, 7}, {3, 8, 13, 8},
                                   {3, 11, 13, 11}, {4, 12, 12, 12},
                                   {3, 4, 3, 12}, {4, 3, 4, 13},
                                   {5, 3, 5, 13}, {10, 7, 10, 13},
                                   {11, 7, 11, 13}, {12, 8, 12, 12} };

    HPEN hPenCyan = CreatePen(PS_SOLID, 1, RGB(0x00, 0x80, 0x80));
    HPEN hPenTemp;
    POINT ptTemp;

    hPenTemp = SelectObject(hdc, hPenCyan);

    //background
    DrawCubicClicked(hwnd, hdc);

    MoveToEx(hdc, 0, 0, &ptTemp);
    for (int i = 0; i < sizeof ShapeSix / (sizeof(POINT) * 2); i++)
    {
        MoveToEx(hdc, ShapeSix[i][0].x, ShapeSix[i][0].y, NULL);
        LineTo(hdc, ShapeSix[i][1].x, ShapeSix[i][1].y);
    }

    SelectObject(hdc, hPenTemp);
    MoveToEx(hdc, ptTemp.x, ptTemp.y, NULL);

    //release
    DeleteObject(hPenCyan);

    return;
}

void DrawCubicSeven(HWND hwnd, HDC hdc)
{
    static POINT ShapeSeven[][2] = { {3, 3, 13, 3}, {3, 4, 13, 4},
                                     {12, 5, 12, 7}, {11, 5, 11, 9},
                                     {10, 5, 10, 11}, {9, 7, 9, 13},
                                     {8, 9, 8, 13}, {7, 11, 7, 13} };

    HPEN hPenBlack = CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0x00));
    HPEN hPenTemp;
    POINT ptTemp;

    hPenTemp = SelectObject(hdc, hPenBlack);

    //background
    DrawCubicClicked(hwnd, hdc);

    MoveToEx(hdc, 0, 0, &ptTemp);
    for (int i = 0; i < sizeof ShapeSeven / (sizeof(POINT) * 2); i++)
    {
        MoveToEx(hdc, ShapeSeven[i][0].x, ShapeSeven[i][0].y, NULL);
        LineTo(hdc, ShapeSeven[i][1].x, ShapeSeven[i][1].y);
    }

    SelectObject(hdc, hPenTemp);
    MoveToEx(hdc, ptTemp.x, ptTemp.y, NULL);

    //release
    DeleteObject(hPenBlack);

    return;
}

void DrawCubicEight(HWND hwnd, HDC hdc)
{
    static POINT ShapeEight[][2] = { {4, 3, 12, 3}, {4, 4, 12, 4},
                                     {4, 7, 12, 7}, {4, 8, 12, 8},
                                     {4, 11, 12, 11}, {4, 12, 12, 12},
                                     {3, 4, 3, 7}, {3, 9, 3, 12},
                                     {4, 3, 4, 13}, {5, 3, 5, 13},
                                     {10, 3, 10, 13}, {11, 3, 11, 13},
                                     {12, 4, 12, 7}, {12, 9, 12, 12} };

    HPEN hPenGray = CreatePen(PS_SOLID, 1, RGB(0x80, 0x80, 0x80));
    POINT ptTemp;

    SelectObject(hdc, hPenGray);
    MoveToEx(hdc, 0, 0, &ptTemp);

    //background
    DrawCubicClicked(hwnd, hdc);

    for (int i = 0; i < sizeof ShapeEight / (sizeof(POINT) * 2); i++)
    {
        MoveToEx(hdc, ShapeEight[i][0].x, ShapeEight[i][0].y, NULL);
        LineTo(hdc, ShapeEight[i][1].x, ShapeEight[i][1].y);
    }

    SelectObject(hdc, hPenGray);
    MoveToEx(hdc, ptTemp.x, ptTemp.y, NULL);

    //release
    DeleteObject(hPenGray);

    return;
}

void DrawCubicFlag(HWND hwnd, HDC hdc)
{
    static POINT ShapeRed[][2] = { {7, 3, 9, 3}, {5, 4, 9, 4},
                                   {4, 5, 9, 5}, {5, 6, 9, 6},
                                   {7, 7, 9, 7} };
    static POINT ShapeBlack[][2] = { {8, 8, 9, 8}, {8, 9, 9, 9},
                                     {6, 10, 10, 10}, {4, 11, 12, 11},
                                     {4, 12, 12, 12} };

    HPEN hPenRed = CreatePen(PS_SOLID, 1, RGB(0xFF, 0x00, 0x00));
    HPEN hPenBlack = CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0x00));
    HPEN hPenTemp;
    POINT ptTemp;

    //background
    DrawCubicOrigin(hwnd, hdc);

    MoveToEx(hdc, 0, 0, &ptTemp);
    hPenTemp = SelectObject(hdc, hPenRed);

    for (int i = 0; i < sizeof ShapeRed / (sizeof(POINT) * 2); i++)
    {
        MoveToEx(hdc, ShapeRed[i][0].x, ShapeRed[i][0].y, NULL);
        LineTo(hdc, ShapeRed[i][1].x, ShapeRed[i][1].y);
    }
    SelectObject(hdc, hPenBlack);
    for (int i = 0; i < sizeof ShapeBlack / (sizeof(POINT) * 2); i++)
    {
        MoveToEx(hdc, ShapeBlack[i][0].x, ShapeBlack[i][0].y, NULL);
        LineTo(hdc, ShapeBlack[i][1].x, ShapeBlack[i][1].y);
    }

    MoveToEx(hdc, ptTemp.x, ptTemp.y, NULL);
    SelectObject(hdc, hPenTemp);

    //release
    DeleteObject(hPenBlack);
    DeleteObject(hPenRed);

    return;
}

void DrawCubicQuestion(HWND hwnd, HDC hdc)
{
    static POINT ShapeQuestion[][2] = { {6, 3, 10, 3},
                                        {8, 7, 10, 7} };
    static RECT RestPart[4] = { {5, 4, 7, 6},
                                {9, 4, 11, 7},
                                {7, 8, 9, 10},
                                {7, 11, 9, 13} };
    HBRUSH hBrBlack = CreateSolidBrush(RGB(0x00, 0x00, 0x00));
    HPEN hPenBlack = CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0x00));
    HPEN hPenTemp;
    POINT ptTemp;

    //background
    DrawCubicOrigin(hwnd, hdc);

    hPenTemp = SelectObject(hdc, hPenBlack);
    MoveToEx(hdc, 0, 0, &ptTemp);
    for (int i = 0; i < sizeof ShapeQuestion / (sizeof(POINT) * 2); i++)
    {
        MoveToEx(hdc, ShapeQuestion[i][0].x, ShapeQuestion[i][0].y, NULL);
        LineTo(hdc, ShapeQuestion[i][1].x, ShapeQuestion[i][1].y);
    }

    for (int i = 0; i < 4; i++)
    {
        FillRect(hdc, RestPart + i, hBrBlack);
    }

    SelectObject(hdc, hPenTemp);
    MoveToEx(hdc, ptTemp.x, ptTemp.y, NULL);
    //release
    DeleteObject(hPenBlack);
    DeleteObject(hBrBlack);

    return;
}

//the next three funcitons is used for draw
//three kind of mine
static void DrawCubicRedBackGround(HWND hwnd, HDC hdc)
{
    RECT rect;
    HBRUSH hBr = CreateSolidBrush(RGB(0xFF, 0x00, 0x00));
    HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0x80, 0x80, 0x80));
    HPEN hPenTemp;
    POINT ptTemp;

    MoveToEx(hdc, 0, 0, &ptTemp);
    //draw lines
    GetClientRect(hwnd, &rect);
    FillRect(hdc, &rect, hBr);
    hPenTemp = SelectObject(hdc, hPen);
    LineTo(hdc, 0, 16);
    MoveToEx(hdc, 0, 0, NULL);
    LineTo(hdc, 16, 0);

    SelectObject(hdc, hPenTemp);
    MoveToEx(hdc, ptTemp.x, ptTemp.y, NULL);
    //relase pen and brush
    DeleteObject(hPen);
    DeleteObject(hBr);

    return;
}

static void DrawCubicMineOnly(HWND hwnd, HDC hdc)
{
    static RECT ShapeCircle = { 4, 4, 13, 13 };
    static RECT WhiteRect = { 6, 6, 8, 8 };
    static POINT Lines[][2] = { {4, 4, 13, 13}, {4, 12, 13, 3},
                                {2, 8, 15, 8}, {8, 2, 8, 15} };
    static POINT RestPoint[] = { 6, 4, 10, 4, 4, 6, 12, 6,
                                 4, 10, 12, 10, 6, 12, 10, 12};
    HBRUSH hBrBlack = CreateSolidBrush(RGB(0x00, 0x00, 0x00));
    HBRUSH hBrWhite = CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
    HPEN hPenBlack = CreatePen(PS_SOLID, 1, RGB(0x00, 0x00, 0x00));
    HPEN hPenTemp;
    HBRUSH hBrushTemp;
    POINT ptTemp;

    hBrushTemp = SelectObject(hdc, hBrBlack);
    hPenTemp = SelectObject(hdc, hPenBlack);
    MoveToEx(hdc, 0, 0, &ptTemp);

    Ellipse(hdc, ShapeCircle.left, ShapeCircle.top,
            ShapeCircle.right, ShapeCircle.bottom);

    for (int i = 0; i < sizeof Lines / (sizeof(POINT) * 2); i++)
    {
        MoveToEx(hdc, Lines[i][0].x, Lines[i][0].y, NULL);
        LineTo(hdc, Lines[i][1].x, Lines[i][1].y);
    }

    for (int i = 0; i < sizeof RestPoint / sizeof(POINT);i++)
    {
        SetPixel(hdc, RestPoint[i].x, RestPoint[i].y, RGB(0, 0, 0));
    }
    FillRect(hdc, &WhiteRect, hBrWhite);

    SelectObject(hdc, hPenTemp);
    SelectObject(hdc, hBrushTemp);
    MoveToEx(hdc, ptTemp.x, ptTemp.y, NULL);

    //release
    DeleteObject(hPenBlack);
    DeleteObject(hBrBlack);
    DeleteObject(hBrWhite);

    return;
}

static void DrawCubicRedX(HWND hwnd, HDC hdc)
{
    static POINT ShapeX[][2] = { {2, 3, 14, 15}, {3, 3, 15, 15},
                                 {2, 14, 14, 2}, {3, 14, 15, 2} };
    HPEN hPenRed = CreatePen(PS_SOLID, 1, RGB(0xFF, 0, 0));
    HPEN hPenTemp;
    POINT ptTemp;

    hPenTemp = SelectObject(hdc, hPenRed);
    MoveToEx(hdc, 0, 0, &ptTemp);

    for (int i = 0; i < sizeof ShapeX / (sizeof (POINT) * 2); i++)
    {
        MoveToEx(hdc, ShapeX[i][0].x, ShapeX[i][0].y, NULL);
        LineTo(hdc, ShapeX[i][1].x, ShapeX[i][1].y);
    }

    SelectObject(hdc, hPenTemp);
    MoveToEx(hdc, ptTemp.x, ptTemp.y, NULL);

    //release
    DeleteObject(hPenRed);

    return;
}

void DrawCubicMine(HWND hwnd, HDC hdc)
{
    DrawCubicClicked(hwnd, hdc);
    DrawCubicMineOnly(hwnd, hdc);

    return;
}

void DrawCubicMistakeMine(HWND hwnd, HDC hdc)
{
    DrawCubicClicked(hwnd, hdc);
    DrawCubicMineOnly(hwnd, hdc);
    DrawCubicRedX(hwnd, hdc);

    return;
}

void DrawCubicFailMine(HWND hwnd, HDC hdc)
{
    DrawCubicRedBackGround(hwnd, hdc);
    DrawCubicMineOnly(hwnd, hdc);
}

//iNumber must be non-negative, and not bigger than eight
void DrawCubicDigit(HWND hwnd, HDC hdc, int iNumber)
{
    static void (*pfunbox[])(HWND, HDC) = { DrawCubicClicked,
                                            DrawCubicOne,
                                            DrawCubicTwo,
                                            DrawCubicThree,
                                            DrawCubicFour,
                                            DrawCubicFive,
                                            DrawCubicSix,
                                            DrawCubicSeven,
                                            DrawCubicEight };
    if (iNumber < 0 || iNumber > 8)
    {
        MessageBox(NULL, "iNumber out of range!", "DrawCubicDigit", MB_ICONERROR);
        exit(EXIT_FAILURE);
    }

    pfunbox[iNumber](hwnd, hdc);

    return;
}