#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_H_

#include "../../gui/cli/cli.h"
#include "../back/back.h"
#include "full_line_handler/full_line_handler.h"
#include "tetris_fsm.h"

extern "C"
{
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
}
int TetrisGameLoop(GameInfo *game_info, WINDOW **windows);
int TetrisHandleCollision(int col, int dir);
void TetrisSetUp(GameInfo *game_info, int **field);
void TetrisAddPoints(GameInfo *game_info, int full_lines);

#define TETRIS_GAME_SPEED 300
#define TETRIS_GAME_ACCELERATION 20

#endif