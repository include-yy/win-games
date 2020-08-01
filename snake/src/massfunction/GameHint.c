#include"cursor_operate.h"
#include"snake_info.h"
#include<stdio.h>

void GameHint(void)
{
  goto_xy(0, LengthOfVertical);
  printf("press w, a, s, d to UP, DOWN, LEFT, RIGHT, press any key to start");
}
