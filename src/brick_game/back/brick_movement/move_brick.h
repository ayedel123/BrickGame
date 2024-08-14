#ifndef __TETRIS_MOVE_BRICK__
#define __TETRIS_MOVE_BRICK__

#include "../common/defines.h"
#include "../game_info/game_info.h"
#include "check_collision.h"

int MoveBrick(GameInfo *game_info, Brick *oldBrick, int direction,
              int angle);
int ForceMoveBrick(GameInfo *game_info, Brick *oldBrick, int direction);
void MoveBrickInField(int **field, Brick *brick);
void DeleteFromField(int **field, Brick *brick);
void RotateBrickCords(Brick *brick, int angle);
void MoveBrickCords(Brick *brick, int direction);

#endif