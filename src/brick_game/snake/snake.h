#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE_H_

#include "../../gui/cli/cli.h"
#include "../back/back.h"
extern "C"
{
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
}
#include "snake_fsm.h"

int SnakeGameLoop(GameInfo *game_info, WINDOW **windows);

void SnakeSetUp(GameInfo *game_info, int **field);

#endif