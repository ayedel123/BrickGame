#ifndef __TETRIS_FSM__
#define __TETRIS_FSM__

#include "../../gui/cli/cli.h"
#include "../back/back.h"
#include "tetris.h"
extern "C"
{
#include <curses.h>
}


// typedef enum
// {
//   MOVE_UP = 0,
//   MOVE_DOWN,
//   MOVE_RIGHT,
//   MOVE_LEFT,
//   ROTATE_LEFT,
//   ROTATE_RIGHT,
//   PAUSE,
//   EXIT,
//   START_SIG,
//   NOSIG
// } tetris_signals;


GameInfo_t TetrisUpdateCurrentState(GameInfo_t gameInfo, game_states *state,
                              signals signal, WINDOW **windows);
signals TetrisGetSignal(int userInput);

#endif