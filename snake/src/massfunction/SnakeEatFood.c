#include"mass_function.h"
#include"snake_operate.h"

int SnakeEatFood(SnakeHead * snake, FOOD * food)
{
  SnakeBody * bdy = snake->tobody;
  if (bdy->x == food->x &&
      bdy->y == food->y)
    return 1;
  else
    return 0;
}
