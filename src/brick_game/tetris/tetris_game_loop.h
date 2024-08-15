#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_GAME_LOOP_FSM_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_GAME_LOOP_FSM_H_

#include "../../gui/cli/cli.h"
#include "../back/back.h"
#include "tetris_fsm.h"

extern "C"
{
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
}
#include "../../gui/cli/cli.h"

int TetrisGameLoop(GameInfo *game_info, WINDOW **windows);

#endif