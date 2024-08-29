#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_H_

extern "C" {
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
}

#include "tetris_base.h"
#include "tetris_fsm.h"
#include "tetris_game_loop.h"

#define TETRIS_GAME_SPEED 300
#define TETRIS_GAME_ACCELERATION 20

#endif