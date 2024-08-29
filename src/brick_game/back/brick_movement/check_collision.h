#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_BACK_BRICK_MOVEMENT_CHECK_COLLISION_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_BACK_BRICK_MOVEMENT_CHECK_COLLISION_H_

#include "../game_info/game_info.h"

int CheckCollision(GameInfo *game_info, Brick *brick, int direction);
int CheckOutOfBounds(Brick *brick, int cordI, int width, int height,
                     int direction);
int CheckCollisionBrick(int **field, Brick *brick, int cordI);

#endif