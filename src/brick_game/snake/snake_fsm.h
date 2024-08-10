#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE_FSM_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE_FSM_H_

#include "../../gui/cli/cli.h"
#include "../back/back.h"

extern "C"
{
#include <curses.h>
}
#include "snake_functions.h"
#include <vector>

GameInfo UpdateCurrentState(GameInfo game_info, std::vector<Brick *> &body, GameState *state,
                              Signal signal, WINDOW **windows);
Signal GetSignal(int UserInput);
void GetMoveData(int signal, int *direction, int *angle);

#endif