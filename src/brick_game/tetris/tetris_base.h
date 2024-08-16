#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_BASE_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_BASE_H_

extern "C" {
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
}

#include "../../gui/cli/cli.h"
#include "../back/back.h"

int TetrisHandleCollision(int col, int dir);
void TetrisSetUp(GameInfo *game_info, int **field);
void TetrisAddPoints(GameInfo *game_info, int full_lines);
int FullLineHandler(GameInfo *game_info);
int IsLineFull(GameInfo *game_info, int line_id);
void DropLines(GameInfo *game_info, int last_line, int linesCount);
int resetBrick(GameInfo *game_info);

#define TETRIS_GAME_SPEED 300
#define TETRIS_GAME_ACCELERATION 20

#endif