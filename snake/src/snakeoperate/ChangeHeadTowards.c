#include"snake_operate.h"
#include"snake_info.h"

static int Transcoder(int origincode);
static int OpsiteWay(int originway);
void ChangeHeadTowards (SnakeHead * snake, int way)
{
  int CodeWay = Transcoder(way);
  if (CodeWay == 0)
    return;
  int OriginWay = snake->HeadTowards;
  if (CodeWay == OriginWay)
    return;
  else if(CodeWay == OpsiteWay(OriginWay))
    return;
  else
    snake->HeadTowards = CodeWay;
}
  
static int Transcoder(int origincode)
{
  switch (origincode) {
  case 'w':
    return UP;
    break;
  case 's':
    return DOWN;
    break;
  case 'a':
    return LEFT;
    break;
  case 'd':
    return RIGHT;
    break;
  default:
    return 0;
  }
}

static int OpsiteWay(int originway)
{
  if (originway == UP)
    return DOWN;
  else if (originway == DOWN)
    return UP;
  else if (originway == LEFT)
    return RIGHT;
  else if (originway == RIGHT)
    return LEFT;
  return 0;
}
