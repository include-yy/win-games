#include"cursor_operate.h"
#include"mass_function.h"
#include"snake_info.h"
void PrintFood(FOOD * food)
{
  int xp = food->x;
  int yp = food->y;

  gotoprint(xp, yp, ShapeOfFood);
  
}
