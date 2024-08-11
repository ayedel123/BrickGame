#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE_FSM_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE_FSM_H_

#include "../../gui/cli/cli.h"
#include "../back/back.h"

extern "C"
{
#include <curses.h>
}
#include "snake.h"
#include <vector>

Signal GetSignal(int UserInput);
void GetMoveData(int signal, int *direction, int *angle);
void GetMoveData(int signal, int *direction, int *angle);
void SpawnAppleHandler(s21::Snake &snake, GameState *state);
void MovingHandler(s21::Snake &snake, GameState *state,
                   Signal signal, WINDOW **windows);
void StartHandler(s21::Snake &snake, GameState *state,
                  Signal signal, WINDOW *gameWin);
void GameOverHandler(s21::Snake &snake, GameState *state,
                     Signal signal, WINDOW *gameWin);
void ExitHandler(GameState *state);
void PauseHandler(GameState *state, Signal signal);
Signal GetSignal(int user_input);

#endif