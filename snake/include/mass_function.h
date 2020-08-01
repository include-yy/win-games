#ifndef MASS_FUNCTION_H
#define MASS_FUNCTION_H

#include"snake_operate.h"
typedef struct 
{
  int x;
  int y;
}FOOD;


void CreateSnakeBox(void);
void CreateFood(SnakeHead * snake, FOOD * food);
int SnakeEatFood(SnakeHead * snake, FOOD * food);
void PrintFood(FOOD * food);
int SnakeIsNotDead(SnakeHead * snake);
void PausePerStep(int ms);

void GameHint(void);
void ShowScoreBoard(void);
void ScoreAdd(SnakeHead * head);
void GameOver(void);
#endif
