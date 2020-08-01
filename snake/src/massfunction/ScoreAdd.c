#include"cursor_operate.h"
#include"snake_operate.h"
#include"snake_info.h"
#include<stdio.h>
void ScoreAdd(SnakeHead * head)
{
  goto_xy(8, LengthOfVertical);
  printf("%d\n", head->length - SnakeInitialSize);
}
