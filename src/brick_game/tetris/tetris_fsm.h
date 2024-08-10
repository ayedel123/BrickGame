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
//   kMoveUp = 0,
//   kMoveDown,
//   kMoveRight,
//   kMoveLeft,
//   kRotateLeft,
//   kRotateRight,
//   kPause,
//   kExit,
//   kStartSig,
//   kNosig
// } tetris_signals;


GameInfo_t TetrisUpdateCurrentState(GameInfo_t gameInfo, GameState *state,
                              Signal signal, WINDOW **windows);
Signal TetrisGetSignal(int userInput);

#endif