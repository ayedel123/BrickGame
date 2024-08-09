#ifndef __SNAKE_FUNCTIONS__
#define __SNAKE_FUNCTIONS__


#include "../../gui/cli/cli.h"
#include "../back/back.h"

// Временно
#include "../tetris/fullLineHandler/fullLineHandler.h"
extern "C"
{
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
}

//#include <list>

int SnakeHandleCollision(GameInfo_t *gameInfo, int col, int dir);
void RandomFreeCell(int **field, int height, int width, int *y, int *x);
int SpawnApple(GameInfo_t *gameInfo);

#define SNAKE_GAME_SPEED 300
#define SNAKE_GAME_ACCELERATION 20

#endif