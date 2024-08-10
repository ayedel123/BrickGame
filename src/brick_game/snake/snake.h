#ifndef __SNAKE__
#define __SNAKE__

#include "../../gui/cli/cli.h"
#include "../back/back.h"
#include "../tetris/fullLineHandler/fullLineHandler.h"
extern "C"
{
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
}
#include "snake_fsm.h"

// Временно

int SnakeGameLoop(GameInfo *game_info, WINDOW **windows);
// void setUp(WINDOW **windows, int winCount, GameInfo *game_info, int **field);
//  int SnakeHandleCollision(GameInfo *game_info, int col, int dir);
void SnakeSetUp(GameInfo *game_info, int **field);
// void RandomFreeCell(int **field, int height, int width, int *y, int *x);
// int SpawnApple(GameInfo *game_info);

// #define SNAKE_GAME_SPEED 300
// #define SNAKE_GAME_ACCELERATION 20

#endif