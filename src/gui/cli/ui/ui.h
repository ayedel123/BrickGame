#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_UI_UI_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_UI_UI_H_

#include "../../../brick_game/back/back.h"
#include "../window/window.h"
#include "../user_input/user_input.h"
extern "C"
{
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
}
void DrawField(WINDOW *win, GameInfo *game_info);
WINDOW *SetUpWindow(int win_number);
int *SetUpBrickGameWindows(WINDOW **windows, int win_count);
void CursesSetUp();
void GameOverMessage(WINDOW *win, int height);
void StartMessage(WINDOW *win, int height);

void PrintMenu(WINDOW *menu_win, int highlight, const char *choices[], int choices_count);
int ChoseGame(WINDOW *win);

#endif