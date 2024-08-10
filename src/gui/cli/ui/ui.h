#ifndef __TETRIS_UI__
#define __TETRIS_UI__

#include "../../../brick_game/back/back.h"
#include "../window/window.h"
extern "C"
{
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
}
void drawField(WINDOW *win, GameInfo *gameManager);
WINDOW *setUpWindow(int winNumber);
int *setUpBrickGameWindows(WINDOW **windows, int winCount);
void cursesSetUp();
void gameOverMessage(WINDOW *win, int width, int height);
void startMessage(WINDOW *win, int width, int height);

#endif