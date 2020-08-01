#include"snake_operate.h"

void GameExecute(SnakeHead * snake);

int main(int argc, char ** argv)
{
  Snake snake1;
  SnakeCreate(snake1);
  GameExecute(snake1);
  return 0;
}
