#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE__H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE__H_

#include "snake_class.h"
#include "snake_fsm.h"

void SnakeUpdateCurrentState(s21::Snake &snake, GameState *state,
                             Signal signal);

#endif