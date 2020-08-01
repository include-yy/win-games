#include"snake_operate.h"
#include<stdlib.h>

void SnakeDelete(SnakeHead * oldsnake)
{
  SnakeBody * one;
  SnakeBody * two;

  one = oldsnake->tobody;

  while(one != NULL) {
    two = one;
    one = one->next;
    free(two);
  }
}
