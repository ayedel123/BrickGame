#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_STATS_STATS_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_STATS_STATS_H_

#include "../../../brick_game/back/back.h"
#include "../ui/ui.h"
#include "../window/window.h"
extern "C"
{
#include <ncurses.h>
}
void printTetrisStats(WINDOW *menu_win, GameInfo *game_info, int on_pause);

#endif