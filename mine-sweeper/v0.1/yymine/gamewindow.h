#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#define ID_FACE 10000
#define ID_CNTSCREEN 10001
#define ID_TIMSCREEN 10002

void GameWindowRegisterCubic(const TCHAR szclsName[]);
void GameWindowRegisterFace(const TCHAR szclsName[]);
void GameWindowRegisterTimeScreen(const TCHAR szclsName[]);
void GameWindowRegisterCounterScreen(const TCHAR szclsName[]);

POINT GameWindowGetSize(void);
void GameWindowDrawFrame(HWND hwnd, HDC hdc);

void GameWindowCreateCubic(HWND hParent, POINT Startpt);
void GameWindowCreateFace(HWND hParent, POINT Startpt);
void GameWindowCreateTimeScreen(HWND hParent, POINT StartPt);
void GameWindowCreateCounterScreen(HWND hParent, POINT StartPt);
void GameWindowDestroyCubic(void);
void GameWindowDestroyFace(void);
void GameWindowDestroyTimeScreen(void);
void GameWindowDestroyCounterScreen(void);

void GameWindowMoveFace(POINT newpt);
void GameWindowMoveTimeScreen(POINT newpt);

HWND GameWindowCreateFrame(void);
void GameWindowCreateChild(HWND hwnd);
void GameWindowDestroy(void);

//used for a game has started or ended
void GameWindowNewGame(HWND hwnd, int icRow, int icCol, int imines);

void GameWindowRestart(HWND hwnd);
#endif