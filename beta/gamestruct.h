#ifndef GAMESTRUCT_H
#define GAMESTRUCT_H

#include <windows.h>

//for iGameStatus
enum {game_ready, game_ing, game_win, game_lose};

//for iCheckKind
enum {click_no, click_yes, click_flag, click_mark};

//for mine status: pMineStatus
enum {mine_no, mine_normal, mine_mistake, mine_click};

struct tagGameStruct
{
    /* basic info */
    //number of row and col
    int icRow;
    int icCol;
    //number of cubic
    int icCubics;
    //number of mine
    int icMines;

    /* game info */
    //use question mark or not
    BOOL fQuestionMark;
    //play sound or not
    BOOL fPlaySound;

    //game status, 0 for not start, 1 for ing, 2 for win, three for lose
    //now, use the enum value
    int iGameStatus;
    //number of mine left
    int icRestMines;
    //time passed after starting
    int iTotalTime;
    //number of flag used
    int iFlagUsed;
    //if left button has been pressed
    BOOL fLeftButtonPressed;
    //if right button has been pressed
    BOOL fRightButtonPressed;

    //bool array, tells if the specified cubic has mine, TRUE for have
    PBOOL pfHaveMine;
    //int array, tells if the specified cubic has been checked,
    //zero for no, one for clicked, two for flagged, three for question mark
    //now, use enum value
    PINT piCheckKind;
    //int array, tells how many mines around it.
    PINT pcAroundMine;
    //int array, mine display status, just for cubics have mine
    PINT pMineStatus;

    //handles of cubic
    HWND * phwndCubic;
    //handle of face
    HWND hwndFace;
    //handle of Counter
    HWND hwndCounterScreen;
    //handle of TimeScreen
    HWND hwndTimeScreen;
};

typedef struct tagGameStruct GAMESTRUCT, * PGAMESTRUCT;

void GameStructInit(PGAMESTRUCT pgs, int icRow, int icCol, int icMines);
void GameStructDestroy(PGAMESTRUCT pgs);
void GameStructRestart(PGAMESTRUCT pgs);

BOOL GameStructFindAndSearch(PGAMESTRUCT pgs, int iStartid, int * clickArray);

PGAMESTRUCT GetPGS(void);
#define ReleasePGS(pgs) ((pgs = NULL))

#endif