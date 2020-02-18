#include <windows.h>
#include "gamewindow.h"
#include "gamestruct.h"

LRESULT CALLBACK CubicWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK FaceWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK TimeScreenWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CounterScreenWndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInst;
extern const char szAppname[];
extern const char szCubicClass[];
extern const char szScreenClass[];

void GameWindowRegisterCubic(const char szclsName[])
{
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = CubicWndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInst;
    wndclass.hIcon = 0;
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = GetStockObject(COLOR_BTNFACE);
    wndclass.lpszClassName = szclsName;
    wndclass.lpszMenuName = NULL;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, "cubic class register error", szclsName, MB_ICONERROR);
        exit(EXIT_FAILURE);
    }

    return;
}

void GameWindowRegisterScreen(const char szclsName[])
{
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = TimeScreenWndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInst;
    wndclass.hIcon = 0;
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = GetStockObject(COLOR_WINDOWTEXT);
    wndclass.lpszClassName = szclsName;
    wndclass.lpszMenuName = NULL;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, "screen class register error", szclsName, MB_ICONERROR);
        exit(EXIT_FAILURE);
    }

    return;
}

POINT GameWindowGetSize(void)
{
    POINT size;
    PGAMESTRUCT pgs;
    pgs = GetPGS();
    size.x = 12 + 16 * pgs->icCol + 8 +
        GetSystemMetrics(SM_CXSIZEFRAME) - 2; //width
    size.y = 9 + 37 + 9 + 16 * pgs->icRow + 8 +
        GetSystemMetrics(SM_CYCAPTION) +
        GetSystemMetrics(SM_CYMENU) + 5; //height
    ReleasePGS(pgs);

    return size;
}

void GameWindowDrawFrame(HWND hwnd, HDC hdc)
{
    RECT rect;
    HPEN hPenWhite = CreatePen(PS_SOLID, 1, RGB(0xFF, 0xFF, 0xFF));
    HPEN hPenGray = CreatePen(PS_SOLID, 1, RGB(0x80, 0x80, 0x80));
    HBRUSH hBrGray = CreateSolidBrush(RGB(0xC0, 0xC0, 0xC0));
    HPEN hPenTemp;
    POINT ptTemp;

    GetClientRect(hwnd, &rect);
    hPenTemp = SelectObject(hdc, hPenWhite);
    MoveToEx(hdc, 0, 0, &ptTemp);

    //background
    FillRect(hdc, &rect, hBrGray);

    //two white line close to frame
    //vertical
    MoveToEx(hdc, 0, 0, NULL);
    LineTo(hdc, 0, rect.bottom);
    MoveToEx(hdc, 1, 0, NULL);
    LineTo(hdc, 1, rect.bottom);
    MoveToEx(hdc, 2, 0, NULL);
    LineTo(hdc, 2, rect.bottom);
    //horizontal
    MoveToEx(hdc, 0, 0, NULL);
    LineTo(hdc, rect.right, 0);
    MoveToEx(hdc, 0, 1, NULL);
    LineTo(hdc, rect.right, 1);
    MoveToEx(hdc, 0, 2, NULL);
    LineTo(hdc, rect.right, 2);

    //draw up box
    //up part
    SelectObject(hdc, hPenGray);
    MoveToEx(hdc, 9, 9, NULL);
    LineTo(hdc, rect.right - 6, 9);
    MoveToEx(hdc, 9, 10, NULL);
    LineTo(hdc, rect.right - 7, 10);
    MoveToEx(hdc, 9, 9, NULL);
    LineTo(hdc, 9, 45);
    MoveToEx(hdc, 10, 9, NULL);
    LineTo(hdc, 10, 44);
    //down part
    SelectObject(hdc, hPenWhite);
    MoveToEx(hdc, rect.right - 6, 45, NULL);
    LineTo(hdc, rect.right - 6, 9);
    MoveToEx(hdc, rect.right - 7, 45, NULL);
    LineTo(hdc, rect.right - 7, 10);
    MoveToEx(hdc, rect.right - 6, 45, NULL);
    LineTo(hdc, 9, 45);
    MoveToEx(hdc, rect.right - 6, 44, NULL);
    LineTo(hdc, 10, 44);

    //draw mine box
    //up part
    SelectObject(hdc, hPenGray);
    MoveToEx(hdc, 9, 51, NULL);
    LineTo(hdc, rect.right - 6, 51);
    MoveToEx(hdc, 9, 52, NULL);
    LineTo(hdc, rect.right - 7, 52);
    MoveToEx(hdc, 9, 53, NULL);
    LineTo(hdc, rect.right - 8, 53);

    MoveToEx(hdc, 9, 51, NULL);
    LineTo(hdc, 9, rect.bottom - 6);
    MoveToEx(hdc, 10, 51, NULL);
    LineTo(hdc, 10, rect.bottom - 7);
    MoveToEx(hdc, 11, 51, NULL);
    LineTo(hdc, 11, rect.bottom - 8);
    //down part
    SelectObject(hdc, hPenWhite);
    MoveToEx(hdc, rect.right - 6, rect.bottom - 6, NULL);
    LineTo(hdc, 9, rect.bottom - 6);
    MoveToEx(hdc, rect.right - 6, rect.bottom - 7, NULL);
    LineTo(hdc, 10, rect.bottom - 7);
    MoveToEx(hdc, rect.right - 6, rect.bottom - 8, NULL);
    LineTo(hdc, 11, rect.bottom - 8);

    MoveToEx(hdc, rect.right - 6, rect.bottom - 6, NULL);
    LineTo(hdc, rect.right - 6, 51);
    MoveToEx(hdc, rect.right - 7, rect.bottom - 6, NULL);
    LineTo(hdc, rect.right - 7, 52);
    MoveToEx(hdc, rect.right - 8, rect.bottom - 6, NULL);
    LineTo(hdc, rect.right - 8, 53);

    //counter screen part
    //up part
    SelectObject(hdc, hPenGray);
    MoveToEx(hdc, 16, 15, NULL);
    LineTo(hdc, 16 + 40, 15);
    MoveToEx(hdc, 16, 15, NULL);
    LineTo(hdc, 16, 15 + 24);
    //down part
    SelectObject(hdc, hPenWhite);
    MoveToEx(hdc, 17, 15 + 24, NULL);
    LineTo(hdc, 17 + 39, 15 + 24);
    MoveToEx(hdc, 17 + 39, 15 + 24, NULL);
    LineTo(hdc, 17 + 39, 15);

    //time screen part
    //up part
    SelectObject(hdc, hPenGray);
    MoveToEx(hdc, rect.right - 15, 15, NULL);
    LineTo(hdc, rect.right - 14 - 40, 15);
    MoveToEx(hdc, rect.right - 14 - 40, 15, NULL);
    LineTo(hdc, rect.right - 14 - 40, 15 + 24);
    //down part
    SelectObject(hdc, hPenWhite);
    MoveToEx(hdc, rect.right - 14, 15 + 24, NULL);
    LineTo(hdc, rect.right - 14, 15);
    MoveToEx(hdc, rect.right - 14, 15 + 24, NULL);
    LineTo(hdc, rect.right - 14 - 40, 15 + 24);

    //face part
    SelectObject(hdc, hPenGray);
    MoveToEx(hdc, rect.right / 2 - 13, 15, NULL);
    LineTo(hdc, rect.right / 2 - 13, 15 + 25);

    MoveToEx(hdc, rect.right / 2 - 13, 15, NULL);
    LineTo(hdc, rect.right / 2 - 13 + 25, 15);

    MoveToEx(hdc, rect.right / 2 + 12, 15 + 25, NULL);
    LineTo(hdc, rect.right / 2 + 12 - 25, 15 + 25);

    MoveToEx(hdc, rect.right / 2 + 12, 15 + 25, NULL);
    LineTo(hdc, rect.right / 2 + 12 , 15);

    SelectObject(hdc, hPenTemp);
    MoveToEx(hdc, ptTemp.x, ptTemp.y, NULL);

    //release
    DeleteObject(hPenWhite);
    DeleteObject(hPenGray);
    DeleteObject(hBrGray);

    return;
}
void GameWindowCreateCubic(HWND hParent, POINT startPt)
{
    PGAMESTRUCT pgs = GetPGS();
    for (int i = 0; i < pgs->icRow; i++)
    {
        for (int j = 0; j < pgs->icCol; j++)
        {
            pgs->phwndCubic[i * pgs->icCol + j] =
                CreateWindow(szCubicClass, NULL,
                             WS_CHILDWINDOW | WS_VISIBLE,
                             startPt.x + j * 16, startPt.y + i * 16,
                             16, 16,
                             hParent, (HMENU)(i * pgs->icCol + j), hInst, NULL);
        }
    }

    ReleasePGS(pgs);
    return;
}

void GameWindowDestroyCubic(void)
{
    PGAMESTRUCT pgs = GetPGS();
    for (int i = 0; i < pgs->icCubics; i++)
    {
        DestroyWindow(pgs->phwndCubic[i]);
    }
    ReleasePGS(pgs);
    return;
}

void GameWindowCreateFace(HWND hParent, POINT startPt)
{
    PGAMESTRUCT pgs = GetPGS();
    pgs->hwndFace = CreateWindow(szCubicClass, NULL,
                                 WS_CHILDWINDOW | WS_VISIBLE,
                                 startPt.x, startPt.y,
                                 24, 24,
                                 hParent, (HMENU)ID_FACE, hInst, NULL);

    SetWindowLong(pgs->hwndFace, GWL_WNDPROC, (LONG)FaceWndProc);

    ReleasePGS(pgs);
    return;
}

void GameWindowDestroyFace(void)
{
    PGAMESTRUCT pgs = GetPGS();
    DestroyWindow(pgs->hwndFace);
    ReleasePGS(pgs);
    return;
}

void GameWindowCreateTimeScreen(HWND hParent, POINT startPt)
{
    PGAMESTRUCT pgs = GetPGS();
    pgs->hwndTimeScreen = CreateWindow(szScreenClass, NULL,
                                       WS_CHILDWINDOW | WS_VISIBLE,
                                       startPt.x, startPt.y,
                                       39, 23,
                                       hParent, (HMENU)ID_TIMSCREEN, hInst, NULL);
    ReleasePGS(pgs);
    return;
}

void GameWindowDestroyTimeScreen(void)
{
    PGAMESTRUCT pgs = GetPGS();
    DestroyWindow(pgs->hwndTimeScreen);
    ReleasePGS(pgs);
    return;
}

void GameWindowCreateCounterScreen(HWND hParent, POINT startPt)
{
    PGAMESTRUCT pgs = GetPGS();
    pgs->hwndCounterScreen = CreateWindow(szScreenClass, NULL,
                                          WS_CHILDWINDOW | WS_VISIBLE,
                                          startPt.x, startPt.y,
                                          39, 23,
                                          hParent, (HMENU)ID_CNTSCREEN, hInst, NULL);

    SetWindowLong(pgs->hwndCounterScreen, GWL_WNDPROC, (LONG)CounterScreenWndProc);
    ReleasePGS(pgs);
    return;
}

void GameWindowDestroyCounterScreen(void)
{
    PGAMESTRUCT pgs = GetPGS();
    DestroyWindow(pgs->hwndCounterScreen);
    ReleasePGS(pgs);
   return;
}

void GameWindowMoveFace(POINT newPt)
{
    PGAMESTRUCT pgs;
    pgs = GetPGS();

    MoveWindow(pgs->hwndFace, newPt.x, newPt.y, 24, 24, TRUE);
    ReleasePGS(pgs);
    return;
}

void GameWindowMoveTimeScreen(POINT newPt)
{
    PGAMESTRUCT pgs;
    pgs = GetPGS();

    MoveWindow(pgs->hwndTimeScreen, newPt.x, newPt.y, 39, 23, TRUE);
    ReleasePGS(pgs);
    return;
}

HWND GameWindowCreateFrame(void)
{
    HWND hwnd;
    POINT ptFrame = GameWindowGetSize();
    hwnd = CreateWindow(szAppname, "mine creeper",
                        WS_EX_LAYERED |WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        ptFrame.x, ptFrame.y,
                        NULL, NULL, hInst, NULL);

    return hwnd;
}

void GameWindowCreateChild(HWND hParent)
{
    RECT rect;
    POINT pt;

    GetClientRect(hParent, &rect);
    //create Face
    pt.x = rect.right / 2 - 12;
    pt.y = 16;
    GameWindowCreateFace(hParent, pt);

    //create counter screen
    pt.x = 17;
    pt.y = 16;
    GameWindowCreateCounterScreen(hParent, pt);

    //create time screen
    pt.x = rect.right - 53;
    pt.y = 16;
    GameWindowCreateTimeScreen(hParent, pt);

    //bug, but i don't know where it comes form ...
    //MessageBox(NULL, "Mark", "mark", MB_OK);k

    //create mine window
    pt.x = 12;
    pt.y = 54;
    GameWindowCreateCubic(hParent, pt);

    return;
}

void GameWindowDestroy(void)
{
    GameWindowDestroyCubic();
    GameWindowDestroyFace();
    GameWindowDestroyTimeScreen();
    GameWindowDestroyCounterScreen();

    return;
}

void GameWindowNewGame(HWND hwnd, int icRow, int icCol, int iMines)
{
    RECT rect;
    POINT pt;
    PGAMESTRUCT pgs;

    //destroy and reinitialize
    GameWindowDestroy();
    pgs = GetPGS();
    GameStructDestroy(pgs);
    GameStructInit(pgs, icRow, icCol, iMines);
    ReleasePGS(pgs);

    GetWindowRect(hwnd, &rect);
    pt = GameWindowGetSize();
    MoveWindow(hwnd, rect.left, rect.top, pt.x, pt.y, TRUE);

    //create child window
    GameWindowCreateChild(hwnd);

    return;
}

void GameWindowRestart(HWND hwnd)
{
    PGAMESTRUCT pgs;
    pgs = GetPGS();

    GameStructRestart(pgs);

    //MessageBox(NULL, "gamewindow.c 417", "debug", MB_OK);
    for (int i = 0; i < pgs->icCubics; i++)
    {
        InvalidateRect(pgs->phwndCubic[i], NULL, TRUE);
    }

    ReleasePGS(pgs);
    return;
}