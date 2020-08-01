#include"cursor_operate.h"
#include<stdio.h>

void gotoprint(int x, int y, char * msg)
{
  goto_xy(x, y);
  printf(msg);
}
