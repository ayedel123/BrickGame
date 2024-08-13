#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_FSM_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_FSM_H_

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

void TetrisUpdateCurrentState(GameInfo *game_info, GameState *state,
                                  Signal signal);
Signal TetrisGetSignal(int UserInput);

#endif