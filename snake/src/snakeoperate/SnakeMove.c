#include"snake_operate.h"
#include"snake_info.h"
#include<stdlib.h>
void SnakeMove(SnakeHead * head)
{
  SnakeBody * bdy = head->tobody;
  int prevX, prevY;
  prevX = bdy->x;
  prevY = bdy->y;
  
  int NowX, NowY;
  for (bdy = bdy->next; bdy != NULL; bdy = bdy->next) {
    NowX = bdy->x;
    NowY = bdy->y;
    
    bdy->x = prevX;
    bdy->y = prevY;

    prevX = NowX;
    prevY = NowY;
  }

  switch (head->HeadTowards) {
  case UP :
    head->tobody->y -= 1;
    break;
  case DOWN :
    head->tobody->y += 1;
    break;
  case LEFT:
    head->tobody->x -= 1;
    break;
  case RIGHT :
    head->tobody->x += 1;
    break;
  }
}
