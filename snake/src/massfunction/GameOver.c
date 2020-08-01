#include"cursor_operate.h"
#include"snake_info.h"
#include<stdio.h>
void GameOver(void)
{
  goto_xy(0,LengthOfVertical + 1);
  printf("Game over, thanks for playing");
}
