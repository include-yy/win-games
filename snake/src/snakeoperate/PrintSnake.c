#include"snake_operate.h"
#include"cursor_operate.h"
#include"snake_info.h"
#include<stdlib.h>

void PrintSnake(SnakeHead * snake)
{
  SnakeBody * now = snake->tobody;
  int xpoint, ypoint;

  xpoint = now->x;
  ypoint = now->y;
  gotoprint(xpoint, ypoint, ShapeOfHead);

  now = now->next;
  while(now != NULL) {
    xpoint = now->x;
    ypoint = now->y;
    gotoprint(xpoint, ypoint, ShapeOfBody);
    now = now->next;
  }
}
