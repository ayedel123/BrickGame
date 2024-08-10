#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_BACK_BRICKS_BRICKS_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_BACK_BRICKS_BRICKS_H_

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

void BornBrick(Brick *brick, int x, int y, int brick_type, int color_count);

#endif