#include"mass_function.h"
#include"snake_info.h"
#include"snake_operate.h"
#include<time.h>
#include<stdlib.h>

static int NotSatisfied(int px, int py, SnakeBody * sk);

void CreateFood(SnakeHead * snake, FOOD * food)
{
  srand((int)time(NULL));
  SnakeBody * bodyptr = snake->tobody;
  int pointx = rand() % (LengthOfHorizontal - 2) + 1;
  int pointy = rand() % (LengthOfVertical - 2) + 1;

  while(NotSatisfied(pointx, pointy, bodyptr)) {
    pointx = rand() % (LengthOfHorizontal - 1);
    pointy = rand() % (LengthOfVertical - 1);
  }
  
  food->x = pointx;
  food->y = pointy;
}

static int NotSatisfied(int px, int py, SnakeBody * bdy)
{
  while(bdy != NULL) {
    if(bdy->x == px && bdy->y == py)
      return 1;
    else
      bdy = bdy->next;
  }

  return 0;
}
