#ifndef __TETRIS__
#define __TETRIS__

#include "../../gui/cli/cli.h"
#include "../back/back.h"
#include "fullLineHandler/fullLineHandler.h"
#include "tetris_fsm.h"
extern "C"
{
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
}
int TetrisGameLoop(GameInfo *game_info, WINDOW **windows);
// void TetrisSetUp(WINDOW **windows, int winCount, GameInfo *game_info, int **field);
int TetrisHandleCollision(int col, int dir);
void TetrisSetUp(GameInfo *game_info, int **field);

#define GAME_SPEED 300
#define GMAE_ACCELERATION 20

#endif