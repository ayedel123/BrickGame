#ifndef __SNAKE_FUNCTIONS__
#define __SNAKE_FUNCTIONS__

#include "../../gui/cli/cli.h"
#include "../back/back.h"

extern "C"
{
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
}
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
int SnakeHandleCollision(GameInfo_t *gameInfo, int col, int dir);
void RandomFreeCell(int **field, int height, int width, int *y, int *x);
int SpawnApple(GameInfo_t *gameInfo);
int SpawnNode(GameInfo_t *gameInfo, std::vector<Brick *> &body);
void redrawBody(GameInfo_t *gameInfo, std::vector<Brick *> &body);
int MoveBody(GameInfo_t *gameInfo, std::vector<Brick *> &body, int direction, bool ignore_collision);


#define SNAKE_GAME_SPEED 350
#define SNAKE_GAME_ACCELERATION 20

#endif