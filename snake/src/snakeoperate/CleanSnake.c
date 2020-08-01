#include"snake_operate.h"
#include"cursor_operate.h"
#include<stdlib.h>
void CleanSnake(SnakeHead * snake)
{
  SnakeBody * bdycl = snake->tobody;
  int pointx, pointy;

  while(bdycl != NULL) {
    pointx = bdycl->x;
    pointy = bdycl->y;
    
    gotoprint(pointx, pointy, " ");
    bdycl= bdycl->next;
  }
}
