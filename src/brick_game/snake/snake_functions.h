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
int SnakeHandleCollision(GameInfo *game_info, int col, int dir);
void RandomFreeCell(int **field, int height, int width, int *y, int *x);
int SpawnApple(GameInfo *game_info);
int SpawnNode(GameInfo *game_info, std::vector<Brick *> &body);
void redrawBody(GameInfo *game_info, std::vector<Brick *> &body);
int MoveBody(GameInfo *game_info, std::vector<Brick *> &body, int direction, bool ignore_collision);


#define SNAKE_GAME_SPEED 350
#define SNAKE_GAME_ACCELERATION 20

#endif