#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_GET_SIGNAL_CONSOLE_GET_SIGNAL_CONSOLE_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_GET_SIGNAL_CONSOLE_GET_SIGNAL_CONSOLE_H_

#include "../../../brick_game/back/common/defines.h"
extern "C"
{
#include <ncurses.h>
}

Signal GetSignalConsole(int user_input);

#endif