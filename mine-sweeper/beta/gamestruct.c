#include "gamestruct.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
//used for GameStructInit
static void GenerateMine(PGAMESTRUCT pgs);
static void CountAroundMine(PGAMESTRUCT pgs, int index);

void GameStructInit(PGAMESTRUCT pgs, int icRow, int icCol, int icMines)
{
    //null pointer check
    if (pgs == NULL)
    {
        MessageBox(NULL, "Null pointer", "GameStructInit", MB_ICONERROR);
        exit(EXIT_FAILURE);
    }
    //icRow, icCol and icMines must be positive.
    //assert(icRow > 0 || icCol > 0 || icMines > 0);
    if (icRow <= 0 || icCol <= 0 || icMines <= 0)
    {
        MessageBox(NULL, "argument negative error!",
                   "GameStructInit", MB_ICONERROR);
        exit(EXIT_FAILURE);
    }

    pgs->icRow = icRow;
    pgs->icCol = icCol;
    pgs->icCubics = icRow * icCol;

    //debug info
    /*
    char buf[20];
    sprintf(buf, "%d", pgs->icCubics);
    MessageBox(NULL, buf, "cao", MB_OK);
    //*/

    //generate mines
    pgs->icMines = icMines;
    pgs->pfHaveMine = malloc(sizeof(BOOL) * pgs->icCubics);
    //new added
    pgs->pMineStatus = malloc(sizeof(int) * pgs->icCubics);
    for (int i = 0; i < pgs->icCubics; i++)
    {
        pgs->pfHaveMine[i] = FALSE;
//        pgs->pMineStatus[i] = mine_no;
    }
    GenerateMine(pgs);
    //initial mineStatus
    /*
    for (int i = 0; i < pgs->icCubics; i++)
    {
        if (pgs->pfHaveMine[i] == TRUE)
        {
            pgs->pMineStatus[i] = mine_normal;
        }
    }
    */
    //game info
    pgs->icRestMines = icMines; //rest mines
    pgs->iGameStatus = game_ready; //not start
    pgs->iFlagUsed = 0; //flag 0
    pgs->iTotalTime = 0; //time zero
    pgs->fPlaySound = TRUE; //play sound
    pgs->fQuestionMark = TRUE; //use quesiton mark
    pgs->fLeftButtonPressed = FALSE; //not pressed;
    pgs->fRightButtonPressed = FALSE; //same

    //allocate memories for other pointers
    pgs->piCheckKind = malloc(sizeof(int) * pgs->icCubics);
    pgs->pcAroundMine = malloc(sizeof(int) * pgs->icCubics);
    pgs->phwndCubic = malloc(sizeof(HWND) * pgs->icCubics);
    //assert(gs.piCheckKind != NULL || gs.pcAroundMine != NULL || gs.phwndCubic != NULL);
    if (pgs->pfHaveMine == NULL || pgs->piCheckKind == NULL || pgs->phwndCubic == NULL)
    {
        MessageBox(NULL, "memory allocate failed!",
                   "GameStructInit", MB_ICONERROR);
    }

    //hwndFace, hwndCounterScreen, hwndTimeScreen
    pgs->hwndFace = NULL;
    pgs->hwndCounterScreen = NULL;
    pgs->hwndTimeScreen = NULL;

    //Initialize CheckKind, CountAroundMine and hwndCubic's memory block
    for (int i = 0; i < pgs->icCubics; i++)
    {
        pgs->piCheckKind[i] = click_no;
        pgs->phwndCubic[i] = NULL;
        CountAroundMine(pgs, i);
    }

    return;
}

static void GenerateMine(PGAMESTRUCT pgs)
{
    int iMineCount = 0;
    int ivalue;
    clock_t StartTime = clock();

    //null pointer check
    if (pgs == NULL)
    {
        MessageBox(NULL, "null pointer", "GenerateMine", MB_ICONERROR);
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    while (iMineCount < pgs->icMines)
    {
        //cost too much time
        if (clock() - StartTime > 500)
        {
            break;
        }

        ivalue = rand() % pgs->icCubics;
        if (pgs->pfHaveMine[ivalue] == FALSE)
        {
            pgs->pfHaveMine[ivalue] = TRUE;
            iMineCount++;
        }
    }

    if (iMineCount == pgs->icMines)
    {
        return;
    }
    else
    {
        //use fixed step to cover the rest blank
        for (int i = rand() % (pgs->icCubics / 5);
             i < pgs->icCubics;
             i += 3)
        {
            if (iMineCount == pgs->icMines)
            {
                break;
            }

            if (pgs->pfHaveMine[i] == FALSE)
            {
                pgs->pfHaveMine[i] = TRUE;
                iMineCount++;
            }
        }

        if (iMineCount == pgs->icMines)
        {
            return;
        }
        else //fuck! use the naivest way
        {
            for (int i = 0; i < pgs->icCubics; i++)
            {
                if (iMineCount == pgs->icMines)
                {
                    return;
                }

                if (pgs->pfHaveMine[i] == FALSE)
                {
                    pgs->pfHaveMine[i] = TRUE;
                    iMineCount++;
                }
            }
        }
    }
}

//tempory debug
static void CountAroundMine(PGAMESTRUCT pgs, int index)
{
    //null pointer check
    if (pgs == NULL)
    {
        MessageBox(NULL, "null pointer", "CountAroundMine", MB_ICONERROR);
        exit(EXIT_FAILURE);
    }
    //index exceed
    if (index >= pgs->icCubics)
    {
        MessageBox(NULL, "index exceed", "CountAroundMine", MB_ICONERROR);
        exit(EXIT_FAILURE);
    }
    //it's a mine
    if (pgs->pfHaveMine[index] == TRUE)
    {
        pgs->pcAroundMine[index] = -1;
        return;
    }

    int iNowRow = index / pgs->icRow;
    int iNowCol = index % pgs->icCol;
    int iCountMine = 0;

    for (int i = iNowRow - 1; i <= iNowRow + 1; i++)
    {
        for (int j = iNowCol - 1; j <= iNowCol + 1; j++)
        {
            if (i < 0 || i >= pgs->icRow || j < 0 || j >= pgs->icCol)
            {
                continue;
            }

            if (pgs->pfHaveMine[i * pgs->icCol + j] == TRUE)
            {
                iCountMine++;
            }
        }
    }
    pgs->pcAroundMine[index] = iCountMine;

    return;
}

void GameStructDestroy(PGAMESTRUCT pgs)
{
    //null pointer check
    if (pgs == NULL)
    {
        MessageBox(NULL, "null pointer", "GameStructDestroy", MB_ICONERROR);
        exit(EXIT_FAILURE);
    }
    //basic info
    pgs->icRow = pgs->icCol = pgs->icCubics = 0;
    pgs->icMines = 0;

    //gane info
    pgs->icRestMines = 0;
    pgs->iGameStatus = game_ready;
    pgs->iTotalTime = 0;
    pgs->iFlagUsed = 0;
    pgs->fLeftButtonPressed = FALSE;
    pgs->fRightButtonPressed = FALSE;

    //MessageBox(NULL, "gamestruct.c 226", "debug", MB_OK);

    free(pgs->pfHaveMine);
    free(pgs->piCheckKind);
    free(pgs->pcAroundMine);
    free(pgs->phwndCubic);
    //new add
//    free(pgs->pMineStatus);

    pgs->pfHaveMine = 0;
    pgs->piCheckKind = 0;
    pgs->pcAroundMine = 0;
    pgs->phwndCubic = NULL;

    pgs->hwndCounterScreen = 0;
    pgs->hwndTimeScreen = 0;
    pgs->hwndTimeScreen = 0;

    return;
}

GAMESTRUCT gs;

PGAMESTRUCT GetPGS(void)
{
    return &gs;
}

void GameStructRestart(PGAMESTRUCT pgs)
{
    //null pointer check
    if (pgs == NULL)
    {
        MessageBox(NULL, "null pointer", "GameStructRestart", MB_ICONERROR);
        exit(EXIT_FAILURE);
    }

    //arrays
    for (int i = 0; i < pgs->icCubics; i++)
    {
        pgs->pfHaveMine[i] = FALSE;
        //new added
//        pgs->pMineStatus[i] = mine_no;

        pgs->piCheckKind[i] = click_no;
        pgs->pcAroundMine[i] = 0;
    }

    //game info need update
    pgs->icRestMines = pgs->icMines;
    pgs->iGameStatus = 0;
    pgs->iTotalTime = 0;
    pgs->iFlagUsed = 0;
    pgs->fLeftButtonPressed = FALSE;
    pgs->fRightButtonPressed = FALSE;

    //generate mine
    GenerateMine(pgs);
    //new added
    for (int i = 0; i < pgs->icCubics; i++)
    {/*
        if (pgs->pfHaveMine[i] == TRUE)
        {
            pgs->pMineStatus[i] = mine_normal;
        }
     */
        CountAroundMine(pgs, i);
    }

    return;
}