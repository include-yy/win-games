#include"cursor_operate.h"
#include"snake_info.h"
#include<stdio.h>
void ShowScoreBoard(void)
{

  for (int i = 0; i < 120; i++) {
    gotoprint(i, LengthOfVertical, " ");
  }
  goto_xy(0, LengthOfVertical);
  printf("Scores: 0");
}
