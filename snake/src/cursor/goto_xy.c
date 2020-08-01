#include<windows.h>

void goto_xy(int x, int y)
{
  COORD position;
  HANDLE outputplace;
  
  position.X = x;
  position.Y = y;

  outputplace = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(outputplace, position);
}
