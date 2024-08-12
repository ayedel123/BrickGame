#ifndef __TETRIS_MOVE_BRICK__
#define __TETRIS_MOVE_BRICK__

#include "../common/defines.h"
#include "../game_info/game_info.h"
#include "check_collision.h"

int moveBrick(GameInfo *game_info, Brick *oldBrick, int direction,
              int angle);
int ForceMoveBrick(GameInfo *game_info, Brick *oldBrick, int direction);
void moveBrickInField(int **field, Brick *brick);
void deleteFromField(int **field, Brick *brick);
void rotateBrickCords(Brick *brick, int angle);
void moveBrickCords(Brick *brick, int direction);

#endif