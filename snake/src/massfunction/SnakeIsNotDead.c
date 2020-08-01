#include"snake_info.h"
#include"snake_operate.h"

#define NULL ((void*)0)

int SnakeIsNotDead(SnakeHead * snake)
{
  if (snake->length ==
      (LengthOfHorizontal - 2) *
      (LengthOfVertical - 2))
    return 0;

  SnakeBody * bdy = snake->tobody;
  int px, py;
  px = bdy->x;
  py = bdy->y;

  if (px == LengthOfHorizontal - 2 ||
      px == 0 ||
      py == LengthOfVertical - 2 ||
      py == 0)
    return 0;

  bdy = bdy->next;
  while(bdy != NULL) {
    if (px == bdy->x && py == bdy->y)
      return 0;
    bdy = bdy->next;
  }

  return 1;
}
