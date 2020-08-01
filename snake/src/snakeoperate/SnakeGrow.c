#include"snake_operate.h"
#include<stdlib.h>
void SnakeGrow(SnakeHead * head)
{
  SnakeBody * tail = head->tail;
  SnakeBody * new;
  tail->next = (SnakeBody *)malloc(sizeof(SnakeBody));
  new = tail->next;
  new->x = tail->x;
  new->y = tail->y;
  new->next = NULL;

  head->tail = new;
  head->length += 1;
}
