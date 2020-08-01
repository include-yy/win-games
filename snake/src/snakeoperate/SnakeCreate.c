#include"snake_operate.h"
#include"snake_info.h"
#include<stdlib.h>

void SnakeCreate (SnakeHead * newsnake)
{
  SnakeBody * newbody;
  int i;
  
  newsnake->length = SnakeInitialSize;
  newsnake->HeadTowards = SnakeInitialTowards;
  newbody = (SnakeBody *)malloc(sizeof(SnakeBody));
  newbody->x = StartPointX;
  newbody->y = StartPointY;
  newsnake->tobody = newbody;

  for (i = 1; i < 3; i++) {
    newbody->next = (SnakeBody *)malloc(sizeof(SnakeBody));
    newbody = newbody->next;
    newbody->x = StartPointX - i;
    newbody->y = StartPointY;
  }

  newbody->next = NULL;
  newsnake->tail = newbody;
}
