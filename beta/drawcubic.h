#ifndef DRAW_CUBIC_H
#define DRAW_CUBIC_H

#include <windows.h>

void DrawCubicOrigin(HWND hwnd, HDC hdc);
void DrawCubicClicked(HWND hwnd, HDC hdc);

void DrawCubicOne(HWND hwnd, HDC hdc);
void DrawCubicTwo(HWND hwnd, HDC hdc);
void DrawCubicThree(HWND hwnd, HDC hdc);
void DrawCubicFour(HWND hwnd, HDC hdc);
void DrawCubicFive(HWND hwnd, HDC hdc);
void DrawCubicSix(HWND hwnd, HDC hdc);
void DrawCubicSeven(HWND hwnd, HDC hdc);
void DrawCubicEight(HWND hwnd, HDC hdc);

void DrawCubicFlag(HWND hwnd, HDC hdc);
void DrawCubicQuestion(HWND hwnd, HDC hdc);

void DrawCubicMine(HWND hwnd, HDC hdc);
void DrawCubicMistakeMine(HWND hwnd, HDC hdc);
void DrawCubicFailMine(HWND hwnd, HDC hdc);

void DrawCubicDigit(HWND hwnd, HDC hdc, int iNumber);

#endif