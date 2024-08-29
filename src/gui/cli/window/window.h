#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_WINDOW_WINDOW_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_WINDOW_WINDOW_H_
extern "C" {
#include <ncurses.h>
}
WINDOW *CreateNewWin(int height, int width, int starty, int startx);

#endif