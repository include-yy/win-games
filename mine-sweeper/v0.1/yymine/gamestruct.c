#include "gamestruct.h"
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
//used for mine
void GenerateMine(PGAMESTRUCT pgs);
void CountAroundMine(PGAMESTRUCT pgs, int index);

void GSInitBasic(PGAMESTRUCT pgs, int icRow, int icCol, int icMines)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GameStructInitBasic"), MB_OK);
        exit(1);
    }
    if (icRow <= 0 || icCol <= 0 || icMines <= 0)
    {
        MessageBox(NULL, TEXT("neg"), TEXT("GameStructInitBasic"), MB_OK);
        exit(1);
    }
    pgs->icRow = icRow;
    pgs->icCol = icCol;
    pgs->icMines = icMines;

    pgs->icCubics = icRow * icCol;

    return;
}

void GSInitMine(PGAMESTRUCT pgs)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GameStructInitMine"), MB_OK);
        exit(1);
    }
    pgs->icRestMines = pgs->icMines;

    pgs->pfHaveMine = (PINT)malloc(sizeof(int) * pgs->icCubics);
    pgs->pcAroundMine = (PINT)malloc(sizeof(int) * pgs->icCubics);
    pgs->pMineStatus = (PINT)malloc(sizeof(int) * pgs->icCubics);

    if (pgs->pfHaveMine == NULL ||
        pgs->pcAroundMine == NULL ||
        pgs->pMineStatus == NULL)
    {
        MessageBox(NULL, TEXT("alloc error"), TEXT("GameStructInitMine"), MB_OK);
        exit(1);
    }

    for (int i = 0; i < pgs->icCubics; i++)
    {
        pgs->pfHaveMine[i] = FALSE;
    }
    GenerateMine(pgs);
    for (int i = 0; i < pgs->icCubics; i++)
    {
        pgs->pMineStatus[i] = mine_no;
        CountAroundMine(pgs, i);
    }
    for (int i = 0; i < pgs->icCubics; i++)
    {
        if (pgs->pfHaveMine[i] == TRUE)
        {
            pgs->pMineStatus[i] = mine_normal;
        }
    }
    return;
}

void GSInitCheckKind(PGAMESTRUCT pgs)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSInitCheckKind"), MB_OK);
        exit(1);
    }

    pgs->piCheckKind = (PINT)malloc(sizeof(int) * pgs->icCubics);
    if (pgs->piCheckKind == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSInitCheckKind"), MB_OK);
        exit(1);
    }

    for (int i = 0; i < pgs->icCubics; i++)
    {
        pgs->piCheckKind[i] = click_no;
    }
    return;
}

void GSInitHWND(PGAMESTRUCT pgs)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSInitHWND"), MB_OK);
        exit(1);
    }
    pgs->phwndCubic = (HWND*)malloc(sizeof(HWND) * pgs->icCubics);
    if (pgs->phwndCubic == NULL)
    {
        MessageBox(NULL, TEXT("alloc error"), TEXT("GSInitHWND"), MB_OK);
        exit(1);
    }
    
    for (int i = 0; i < pgs->icCubics; i++)
    {
        pgs->phwndCubic[i] = 0;
    }
    pgs->hwndCounterScreen = 0;
    pgs->hwndFace = 0;
    pgs->hwndTimeScreen = 0;

    return;
}

void GSInitTotalTime(PGAMESTRUCT pgs)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSInitTotalTime"), MB_OK);
        exit(1);
    }
    pgs->iTotalTime = 0;

    return;
}

void GSInitFlagUsed(PGAMESTRUCT pgs)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSInitFlagUsed"), MB_OK);
        exit(1);
    }
    pgs->iFlagUsed = 0;

    return;
}

void GSInitQuestionMark(PGAMESTRUCT pgs)
{
    static int done;
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSInitQuestionMark"), MB_OK);
        exit(1);
    }
    if (done == 0)
    {
        pgs->fQuestionMark = TRUE;
        done = 1;
    }
    return;
}

void GSInitPlaySound(PGAMESTRUCT pgs)
{
    static int done;
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSInitPlaySound"), MB_OK);
        exit(1);
    }
    if (done == 0)
    {
        pgs->fPlaySound = TRUE;
        done = 1;
    }
    return;
}

void GSInitGameStatus(PGAMESTRUCT pgs)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSInitGameStatus"), MB_OK);
        exit(1);
    }
    pgs->iGameStatus = game_ready;

    return;
}

void GSInitButton(PGAMESTRUCT pgs)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSInitButton"), MB_OK);
        exit(1);
    }
    pgs->fLeftButtonPressed = FALSE;
    pgs->fRightButtonPressed = FALSE;

    return;
}

void GSDestroyBasic(PGAMESTRUCT pgs)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSDestroyBasic"), MB_OK);
        exit(1);
    }

    pgs->icRow = 0;
    pgs->icCol = 0;
    pgs->icCubics = 0;
    pgs->icMines = 0;

    return;
}

void GSDestroyMine(PGAMESTRUCT pgs)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSDestroyMine"), MB_OK);
        exit(1);
    }

    pgs->icRestMines = 0;
    free(pgs->pfHaveMine);
    free(pgs->pcAroundMine);
    free(pgs->pMineStatus);

    pgs->pfHaveMine = NULL;
    pgs->pcAroundMine = NULL;
    pgs->pMineStatus = NULL;
    
    return;
}

void GSDestroyCheckKind(PGAMESTRUCT pgs)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSDestroyCheckKind"), MB_OK);
        exit(1);
    }

    free(pgs->piCheckKind);
    pgs->piCheckKind = NULL;

    return;
}

void GSDestroyHWND(PGAMESTRUCT pgs)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSDestroyHWND"), MB_OK);
        exit(1);
    }
    free(pgs->phwndCubic);
    pgs->phwndCubic = NULL;
    pgs->hwndCounterScreen = 0;
    pgs->hwndFace = 0;
    pgs->hwndTimeScreen = 0;

    return;
}

void GSDestroyTotalTime(PGAMESTRUCT pgs)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSDestroyTotalTime"), MB_OK);
        exit(1);
    }
    pgs->iTotalTime = 0;

    return;
}

void GSDestroyFlagUsed(PGAMESTRUCT pgs)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSDestroyFlagUsed"), MB_OK);
        exit(1);
    }
    pgs->iFlagUsed = 0;

    return;
}

void GSDestroyGameStatus(PGAMESTRUCT pgs)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSDestroyGameStatus"), MB_OK);
        exit(1);
    }
    pgs->iGameStatus = game_ready;

    return;
}

void GSDestroyButton(PGAMESTRUCT pgs)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GSDestroyButton"), MB_OK);
        exit(1);
    }
    pgs->fLeftButtonPressed = FALSE;
    pgs->fRightButtonPressed = FALSE;

    return;
}

int GSGetRow(PGAMESTRUCT pgs)
{
    return pgs->icRow;
}

int GSGetCol(PGAMESTRUCT pgs)
{
    return pgs->icCol;
}

int GSGetCubic(PGAMESTRUCT pgs)
{
    return pgs->icCubics;
}

int GSGetMine(PGAMESTRUCT pgs)
{
    return pgs->icMines;
}

int GSGetRestMine(PGAMESTRUCT pgs)
{
    return pgs->icRestMines;
}
void GSSetRestMine(PGAMESTRUCT pgs, int num)
{
    pgs->icRestMines = num;
}

int GSIsHaveMine(PGAMESTRUCT pgs, int index)
{
    if (pgs->icCubics <= index)
    {
        MessageBox(NULL, TEXT("gamestruct.c, index exceed"), TEXT("GSIsHaveMine"), MB_OK);
        exit(1);
    }
    return pgs->pfHaveMine[index];
}

int GSAroundMine(PGAMESTRUCT pgs, int index)
{
    if (pgs->icCubics <= index)
    {
        MessageBox(NULL, TEXT("gamestruct.c, index exceed"), TEXT("GSAroundMine"), MB_OK);
        exit(1);
    }
    return pgs->pcAroundMine[index];
}

int GSGetMineStatus(PGAMESTRUCT pgs, int index)
{
    if (pgs->icCubics <= index)
    {
        MessageBox(NULL, TEXT("gamestruct.c, index exceed"), TEXT("GSGetMineStatus"), MB_OK);
        exit(1);
    }
    return pgs->pMineStatus[index];
}
void GSSetMineStatus(PGAMESTRUCT pgs, int index, int style)
{
    if (pgs->icCubics <= index)
    {
        MessageBox(NULL, TEXT("gamestruct.c index exceed"), TEXT("GSSetMineStatus"), MB_OK);
        exit(1);
    }
    if ((style != mine_no) && (style != mine_normal) &&
        (style != mine_mistake) && (style != mine_click))
    {
        MessageBox(NULL, TEXT("gamestruct.c style error"), TEXT("GSSetMineStatus"), MB_OK);
        exit(1);
    }
    pgs->pMineStatus[index] = style;

    return;
}

int GSGetCheckKind(PGAMESTRUCT pgs, int index)
{
    if (pgs->icCubics <= index)
    {
        MessageBox(NULL, TEXT("gamestruct.c index exceed"), TEXT("GSGetCheckKind"), MB_OK);
        exit(1);
    }
    return pgs->piCheckKind[index];
}
void GSSetCheckKind(PGAMESTRUCT pgs, int index, int style)
{
    if (pgs->icCubics <= index)
    {
        MessageBox(NULL, TEXT("gamestruct.c index exceed"), TEXT("GSSetCheckKind"), MB_OK);
        exit(1);
    }
    if ((style != click_flag) && (style != click_mark) &&
        (style != click_no) && (style != click_yes))
    {
        MessageBox(NULL, TEXT("gamestruct.c style error"), TEXT("GSSetCheckKind"), MB_OK);
        exit(1);
    }
    pgs->piCheckKind[index] = style;
}

int GSGetTotalTime(PGAMESTRUCT pgs)
{
    return pgs->iTotalTime;
}
void GSSetTotalTime(PGAMESTRUCT pgs, int time)
{
    pgs->iTotalTime = time;
}

int GSGetFlagUsed(PGAMESTRUCT pgs)
{
    return pgs->iFlagUsed;
}
void GSSetFlagUsed(PGAMESTRUCT pgs, int flags)
{
    pgs->iFlagUsed = flags;
}

int GSGetQuestion(PGAMESTRUCT pgs)
{
    return pgs->fQuestionMark;
}
void GSSetQuestion(PGAMESTRUCT pgs, int b)
{
    pgs->fQuestionMark = b;
}

int GSGetSound(PGAMESTRUCT pgs)
{
    return pgs->fPlaySound;
}
void GSSetSound(PGAMESTRUCT pgs, int b)
{
    pgs->fPlaySound = b;
}

int GSGetGameStatus(PGAMESTRUCT pgs)
{
    return pgs->iGameStatus;
}
void GSSetGameStatus(PGAMESTRUCT pgs, int style)
{
    if ((style != game_ready) && (style != game_ing) &&
        (style != game_lose) && (style != game_win))
    {
        MessageBox(NULL, TEXT("style error"), TEXT("GSSetGameStatus"), MB_OK);
        exit(1);
    }

    pgs->iGameStatus = style;
    return;
}

int GSGetLBP(PGAMESTRUCT pgs)
{
    return pgs->fLeftButtonPressed;
}
void GSSetLBP(PGAMESTRUCT pgs, int b)
{
    pgs->fLeftButtonPressed = b;
}

int GSGetRBP(PGAMESTRUCT pgs)
{
    return pgs->fRightButtonPressed;
}
void GSSetRBP(PGAMESTRUCT pgs, int b)
{
    pgs->fRightButtonPressed = b;
}

HWND GSGetCubicH(PGAMESTRUCT pgs, int index)
{
    if (pgs->icCubics <= index)
    {
        MessageBox(NULL, TEXT("index exceed"), TEXT("GSGetCubicH"), MB_OK);
        exit(1);
    }
    return pgs->phwndCubic[index];
}
HWND GSGetFaceH(PGAMESTRUCT pgs)
{
    return pgs->hwndFace;
}
HWND GSGetCounterH(PGAMESTRUCT pgs)
{
    return pgs->hwndCounterScreen;
}
HWND GSGetTimeH(PGAMESTRUCT pgs)
{
    return pgs->hwndTimeScreen;
}

void GameStructInit(PGAMESTRUCT pgs, int Row, int Col, int Mines)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GameStructInit"), MB_OK);
        exit(1);
    }

    GSInitBasic(pgs, Row, Col, Mines);
    GSInitMine(pgs);
    GSInitCheckKind(pgs);
    GSInitHWND(pgs);
    GSInitTotalTime(pgs);
    GSInitFlagUsed(pgs);
    GSInitGameStatus(pgs);
    GSInitButton(pgs);
    GSInitQuestionMark(pgs);
    GSInitPlaySound(pgs);
    return;
}

void GameStructDestroy(PGAMESTRUCT pgs)
{
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GameStructDestroy"), MB_OK);
        exit(1);
    }

    GSDestroyBasic(pgs);
    GSDestroyMine(pgs);
    GSDestroyCheckKind(pgs);
    GSDestroyHWND(pgs);
    GSDestroyTotalTime(pgs);
    GSDestroyFlagUsed(pgs);
    GSDestroyGameStatus(pgs);
    GSDestroyButton(pgs);

    return;
}

void GameStructRestart(PGAMESTRUCT pgs)
{
    //null pointer check
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null"), TEXT("GameStructRestart"), MB_ICONERROR);
        exit(EXIT_FAILURE);
    }
    //basic needn't modify
    //hwnd needn't realloc

    //mine re
    GSDestroyMine(pgs);
    GSInitMine(pgs);
    //CheckKind re
    GSDestroyCheckKind(pgs);
    GSInitCheckKind(pgs);
    //TotalTime re 
    GSDestroyTotalTime(pgs);
    GSInitTotalTime(pgs);
    //FlagUsed re
    GSDestroyFlagUsed(pgs);
    GSInitFlagUsed(pgs);
    //GameStatus re
    GSDestroyGameStatus(pgs);
    GSInitGameStatus(pgs);
    //button re
    GSDestroyButton(pgs);
    GSInitButton(pgs);
    return;
}

GAMESTRUCT gs;
PGAMESTRUCT GetPGS(void)
{
    return &gs;
}