#include "bricks.h"

// const Brick BRICKS_TYPES[BRICK_TYPES_COUNT] = {
//     {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}, 0, 0, 0},
//     {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}, 0, 0, 0},
//     {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}, 0, 0, 0},
//     {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}, 0, 0, 0},
//     {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}, 0, 0, 0},
//     {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}, 0, 0, 0},
//     {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}, 0, 0, 0}};

const Brick BRICKS_TYPES[BRICK_TYPES_COUNT + 1] = {
    {{{0, 0}, {1, 0}, {2, 0}, {3, 0}}, 0, 0, 0},
    {{{0, 0}, {0, 1}, {1, 1}, {2, 1}}, 0, 0, 0},
    {{{0, 1}, {1, 1}, {2, 1}, {2, 0}}, 0, 0, 0},
    {{{0, 0}, {1, 0}, {0, 1}, {1, 1}}, 0, 0, 0},
    {{{0, 1}, {1, 1}, {1, 0}, {2, 0}}, 0, 0, 0},
    {{{0, 1}, {1, 1}, {2, 1}, {1, 0}}, 0, 0, 0},
    {{{0, 0}, {1, 0}, {1, 1}, {2, 1}}, 0, 0, 0},
    {{{0, 0}, {0, 0}, {0, 0}, {0, 0}}, 0, 0, 0},
};
/*
  0:  0000  1:  000   2:   0  3: 00  4:   00
                  0      000     00      00

  5:   0   6:  00
      000       00
*/

void BornBrick(Brick *brick, int x, int y, int brick_type, int color_count) {
  brick_type = (brick_type < 0 || brick_type > BRICK_TYPES_COUNT)
                   ? rand() % BRICK_TYPES_COUNT
                   : brick_type;

  *brick = BRICKS_TYPES[brick_type];
  brick->x = x;
  brick->y = y;
  brick->color =
      (COLOR_COUNT == color_count) ? (rand() % color_count) + 1 : color_count;
}
