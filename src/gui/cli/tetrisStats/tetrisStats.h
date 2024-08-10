#ifndef __TETRIS_MENU__
#define __TETRIS_MENU__

#include "../../../brick_game/back/back.h"
//#include "../../../brick_game/back/common/defines.h"
#include "../ui/ui.h"
#include "../window/window.h"
extern "C"
{
#include <ncurses.h>
}
void printTetrisStats(WINDOW *menuWin, GameInfo *game_info, int isOnPause);

#endif