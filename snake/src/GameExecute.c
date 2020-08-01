#include"snake_operate.h"
#include"mass_function.h"
#include"snake_info.h"
#include<conio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

void GameExecute(SnakeHead * snake)
{
  CreateSnakeBox(); ///
  PrintSnake(snake); //
  
  int ControlHead;
  FOOD food[1];
  CreateFood(snake, food); ///
  PrintFood(food); ///

  GameHint();
  getch(); //press any key to start
  ShowScoreBoard();

  while(SnakeIsNotDead(snake)) { ///
    if (kbhit()) {
      ControlHead = getch();
      ChangeHeadTowards(snake, ControlHead); //
    }
    CleanSnake(snake);
    SnakeMove(snake); //
    //make snake move by clean the screen and then print it.a
    PrintSnake(snake); //
    
    if (SnakeEatFood(snake, food)) { ///
      SnakeGrow(snake); //
      CreateFood(snake, food); ///
      PrintFood(food);  ///
      ScoreAdd(snake);
    }
    PausePerStep(100);
  }
  GameOver();
  SnakeDelete(snake);
  getchar();
  
}
