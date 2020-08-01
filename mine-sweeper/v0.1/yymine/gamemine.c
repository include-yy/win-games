#include <Windows.h>
#include "gamestruct.h"
#include <time.h>

void GenerateMine(PGAMESTRUCT pgs)
{
    int iMineCount = 0;
    int ivalue;
    clock_t StartTime = clock();

    //null pointer check
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null pointer"), TEXT("GenerateMine"), MB_ICONERROR);
        exit(EXIT_FAILURE);
    }
    srand((unsigned int)time(NULL));
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
void CountAroundMine(PGAMESTRUCT pgs, int index)
{
    //null pointer check
    if (pgs == NULL)
    {
        MessageBox(NULL, TEXT("null pointer"), TEXT("CountAroundMine"), MB_ICONERROR);
        exit(EXIT_FAILURE);
    }
    //index exceed
    if (index >= pgs->icCubics)
    {
        MessageBox(NULL, TEXT("index exceed"), TEXT("CountAroundMine"), MB_ICONERROR);
        exit(EXIT_FAILURE);
    }
    //it's a mine
    if (pgs->pfHaveMine[index] == TRUE)
    {
        pgs->pcAroundMine[index] = -1;
        return;
    }

    int iNowRow = index / pgs->icCol;
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