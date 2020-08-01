#include"mass_function.h"
#include"snake_operate.h"
#include"cursor_operate.h"
#include"snake_info.h"
#include<stdlib.h>

void CreateSnakeBox(void)
{
  system("cls");
  
  int i;
  for (i = 0; i < LengthOfHorizontal; i++) {
    gotoprint(i, 0, "#");
    gotoprint(i, LengthOfVertical - 1, "#");
  }
  for (i = 0; i < LengthOfVertical; i++) {
    gotoprint(0, i, "#");
    gotoprint(LengthOfHorizontal - 1, i, "#");
  }
}
    
