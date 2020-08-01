#ifndef GAME_MESSAGE_H
#define GAME_MESSAGE_H

#include <windows.h>

//start and end message
#define WM_GAMESTART WM_USER + 1
#define WM_GAMEEND WM_USER + 2

//used for WM_GAMEEND's wParam
#define GAMEEND_WIN 0
#define GAMEEND_LOSE 1

//flags number change message
#define WM_FLAGCHANGE WM_USER + 3

//face change message
#define WM_FACECHANGE WM_USER + 4

//click in force
#define WM_CLICKBOOM WM_USER + 5

//temporary click or unclick
#define WM_TEMCLICK WM_USER + 6
#define WM_TEMLEAVE WM_USER + 7

//mouse leave 
#define WM_MSLEAVE WM_USER + 7


#endif