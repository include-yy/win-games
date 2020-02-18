#include "gamestruct.h"
#include <Windows.h>
#include <stdlib.h>

static int GetAroundFlag(PGAMESTRUCT pgs, int index);

int GameStructClick(PGAMESTRUCT pgs, int idStart, int clickArray[], int* getlength)
{
	int* clickStack = NULL;
	int iStkpos = 0;
	int iArraypos = 0;
	int fOccurMine = FALSE;
	clickStack = (int*)malloc(sizeof(int) * GSGetCubic(pgs));
	if (clickStack == NULL)
	{
		MessageBox(NULL, TEXT("alloc failed"), TEXT("GameStructClick"), MB_ICONERROR);
		exit(1);
	}

	// you meet a mine at the begining of this function
	if (GSIsHaveMine(pgs, idStart))
	{
		GSSetMineStatus(pgs, idStart, mine_click);
		GSSetCheckKind(pgs, idStart, click_yes);
		clickArray[iArraypos++] = idStart;
		*getlength = iArraypos;
		return TRUE;
	}

	clickStack[iStkpos++] = idStart;

	//loop start
	while (iStkpos > 0)
	{
		int currId = clickStack[--iStkpos];
		GSSetCheckKind(pgs, currId, click_yes);
		clickArray[iArraypos++] = currId;

		int irow = currId / GSGetCol(pgs);
		int icol = currId % GSGetCol(pgs);
		int inowindex;
		if (GetAroundFlag(pgs, currId) == GSAroundMine(pgs, currId)) //satis
		{
			for (int i = irow - 1; i <= irow + 1; i++)
			{
				for (int j = icol - 1; j <= icol + 1; j++)
				{
					if (i < 0 || i >= GSGetRow(pgs) ||
						j < 0 || j >= GSGetCol(pgs))
						continue;
					inowindex = i * GSGetCol(pgs) + j;
					if (inowindex == currId)
						continue;

					if (GSGetCheckKind(pgs, inowindex) == click_yes)
						continue;
					else if (GSGetCheckKind(pgs, inowindex) == click_no ||
						GSGetCheckKind(pgs, inowindex) == click_mark)
					{
						if (GSIsHaveMine(pgs, inowindex) == FALSE)
						{
							clickStack[iStkpos++] = inowindex;
						}
						else
						{
							if (fOccurMine == FALSE)
							{
								GSSetMineStatus(pgs, inowindex, mine_click);
								GSSetCheckKind(pgs, inowindex, click_yes);
								fOccurMine = TRUE;
							}
						}
					}
					else
					{
						if (GSIsHaveMine(pgs, inowindex) == FALSE)
						{
							GSSetMineStatus(pgs, inowindex, mine_mistake);
							GSSetCheckKind(pgs, inowindex, click_yes);
						}
					}
				}
			}
		}
	}
	*getlength = iArraypos;
	free(clickStack);
	return fOccurMine;
}

//count flags around one cubic
static int GetAroundFlag(PGAMESTRUCT pgs, int index)
{
	int sum = 0;
	if (index >= GSGetCubic(pgs))
	{
		MessageBox(NULL, TEXT("index excedd"), TEXT("gamestructclick.c GetAroundFlag"), MB_ICONERROR);
		exit(1);
	}

	int irow = index / GSGetCol(pgs);
	int icol = index % GSGetCol(pgs);

	for (int i = irow - 1; i <= irow + 1; i++)
	{
		for (int j = icol - 1; j <= icol + 1; j++)
		{
			if (i < 0 || i >= GSGetRow(pgs) ||
				j < 0 || j >= GSGetCol(pgs))
			{
				continue;
			}
			if (GSGetCheckKind(pgs, i * GSGetCol(pgs) + j) == click_flag)
			{
				sum = sum + 1;
			}
		}
	}

	return sum;
}

int GameStructIsWin(PGAMESTRUCT pgs)
{
	int sum = 0;
	if (GSGetRestMine(pgs) != 0)
	{
		return 0;
	}
	else
	{
		for (int i = 0; i < GSGetCubic(pgs); i++)
		{
			if (GSGetCheckKind(pgs, i) == click_yes ||
				GSGetCheckKind(pgs, i) == click_flag)
				sum = sum + 1;
		}


		if (sum == GSGetCubic(pgs))
			return 1;
		else
			return 0;
	}

	return 0;
}