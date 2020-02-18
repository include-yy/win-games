#ifndef GAMESTRUCT_H

#define GAMESTRUCT_H

#include <Windows.h>

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

    //number of mine left
    int icRestMines;
    //bool array, tells if the specified cubic has mine, TRUE for have
    PINT pfHaveMine;
    //int array, tells how many mines around it.
    PINT pcAroundMine;
    //int array, mine display status, just for cubics have mine
    PINT pMineStatus;

    //int array, tells if the specified cubic has been checked,
    //zero for no, one for clicked, two for flagged, three for question mark
    //now, use enum value
    PINT piCheckKind;

    //time passed after starting
    int iTotalTime;
    //number of flag used
    int iFlagUsed;

    /* game info */
    //use question mark or not
    int fQuestionMark;
    //play sound or not
    int fPlaySound;

    //game status, 0 for not start, 1 for ing, 2 for win, three for lose
    //now, use the enum value
    int iGameStatus;

    //if left button has been pressed
    int fLeftButtonPressed;
    //if right button has been pressed
    int fRightButtonPressed;

    
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

//10
void GSInitBasic(PGAMESTRUCT pgs, int icRow, int icCol, int icMine);
void GSInitMine(PGAMESTRUCT pgs);
void GSInitCheckKind(PGAMESTRUCT pgs);
void GSInitHWND(PGAMESTRUCT pgs);
void GSInitTotalTime(PGAMESTRUCT pgs);
void GSInitFlagUsed(PGAMESTRUCT pgs);
void GSInitQuestionMark(PGAMESTRUCT pgs);
void GSInitPlaySound(PGAMESTRUCT pgs);
void GSInitGameStatus(PGAMESTRUCT pgs);
void GSInitButton(PGAMESTRUCT pgs);
//8
void GSDestroyBasic(PGAMESTRUCT pgs);
void GSDestroyMine(PGAMESTRUCT pgs);
void GSDestroyCheckKind(PGAMESTRUCT pgs);
void GSDestroyHWND(PGAMESTRUCT pgs);
void GSDestroyTotalTime(PGAMESTRUCT pgs);
void GSDestroyFlagUsed(PGAMESTRUCT pgs);
void GSDestroyGameStatus(PGAMESTRUCT pgs);
void GSDestroyButton(PGAMESTRUCT pgs);

int GSGetRow(PGAMESTRUCT pgs);
int GSGetCol(PGAMESTRUCT pgs);
int GSGetCubic(PGAMESTRUCT pgs);
int GSGetMine(PGAMESTRUCT pgs);

int GSGetRestMine(PGAMESTRUCT pgs);
void GSSetRestMine(PGAMESTRUCT pgs, int num);

int GSIsHaveMine(PGAMESTRUCT pgs, int index);
int GSAroundMine(PGAMESTRUCT pgs, int index);

int GSGetMineStatus(PGAMESTRUCT pgs, int index);
void GSSetMineStatus(PGAMESTRUCT pgs, int index, int style);

int GSGetCheckKind(PGAMESTRUCT pgs, int index);
void GSSetCheckKind(PGAMESTRUCT pgs, int index, int style);

int GSGetTotalTime(PGAMESTRUCT pgs);
void GSSetTotalTime(PGAMESTRUCT pgs, int time);

int GSGetFlagUsed(PGAMESTRUCT pgs);
void GSSetFlagUsed(PGAMESTRUCT pgs, int num);

int GSGetQuestion(PGAMESTRUCT pgs);
void GSSetQuestion(PGAMESTRUCT pgs, int b);

int GSGetSound(PGAMESTRUCT pgs);
void GSSetSound(PGAMESTRUCT pgs, int b);

int GSGetGameStatus(PGAMESTRUCT pgs);
void GSSetGameStatus(PGAMESTRUCT pgs, int style);

int GSGetLBP(PGAMESTRUCT pgs);
void GSSetLBP(PGAMESTRUCT pgs, int b);

int GSGetRBP(PGAMESTRUCT pgs);
void GSSetRBP(PGAMESTRUCT pgs, int b);

HWND GSGetCubicH(PGAMESTRUCT pgs, int index);
HWND GSGetFaceH(PGAMESTRUCT pgs);
HWND GSGetCounterH(PGAMESTRUCT pgs);
HWND GSGetTimeH(PGAMESTRUCT pgs);

//api function
void GameStructInit(PGAMESTRUCT pgs, int icRow, int icCol, int icMines);
void GameStructDestroy(PGAMESTRUCT pgs);
void GameStructRestart(PGAMESTRUCT pgs);

//retrun 0 means you lose. otherwise ok.
int GameStructClick(PGAMESTRUCT pgs, int clickid, int clickArray[], int *getlength);
int GameStructIsWin(PGAMESTRUCT pgs);

PGAMESTRUCT GetPGS(void);
#define ReleasePGS(pgs) ((pgs = NULL))

#endif