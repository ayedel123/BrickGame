#ifndef __BRICK__
#define __BRICK__

extern "C"
{
#include <stdlib.h>
#include <time.h>
}
#include "../common/defines.h"

#define BRICK_TYPES_COUNT 7
#define RANDOM_BRICK -1

typedef struct
{
  int cords[4][2];
  int x;
  int y;
  int color;
} Brick;

typedef struct
{
  int left;
  int right;
  int bottom;
  int top;
} BrickBorder;

extern const Brick BRICKS_TYPES[BRICK_TYPES_COUNT + 1];

void bornBrick(Brick *brick, int x, int y, int brickType, int colorCount);

#endif