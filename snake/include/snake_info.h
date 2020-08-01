#ifndef SNAKE_INFO_H
#define SNAKE_INFO_H

#define UP                              0X1
#define DOWN                            0X2
#define LEFT                            0X3
#define RIGHT                           0X4

#define SnakeInitialSize                3
#define SnakeInitialTowards             RIGHT

#define LengthOfHorizontal              60
#define LengthOfVertical                16

#define StartPointX                     (LengthOfHorizontal/4)
#define StartPointY                     (LengthOfVertical * 3 / 4)


#define ShapeOfHead                     "@"
#define ShapeOfBody                     "$"
#define ShapeOfFood                     "+"
#endif
