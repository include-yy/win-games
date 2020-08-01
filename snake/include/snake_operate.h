#ifndef SNAKE_OPERATE_H
#define SNAKE_OPERATE_H

struct snake_body
{
  int x;
  int y;

  struct snake_body * next;
};
typedef struct snake_body SnakeBody;

typedef struct
{
  int HeadTowards;
  int length;
  SnakeBody * tobody;
  SnakeBody * tail;
}SnakeHead;

typedef SnakeHead Snake[1];

void SnakeCreate(SnakeHead * newsnake);
void SnakeDelete(SnakeHead * oldsnake);
void SnakeMove(SnakeHead * head);
void SnakeGrow(SnakeHead * head);

void PrintSnake(SnakeHead * snake);
void CleanSnake(SnakeHead * snake);
void ChangeHeadTowards(SnakeHead * snake, int way);

#endif 
