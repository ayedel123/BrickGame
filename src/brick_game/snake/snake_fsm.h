#ifndef __SNAKE_FSM__
#define __SNAKE_FSM__

#include "../../gui/cli/cli.h"
#include "../back/back.h"
// #include "snake.h"
extern "C"
{
#include <curses.h>
}
#include "snake_functions.h"
#include <vector>

// typedef enum {
//   S_START = 0,
//   S_SPAWN,
//   S_MOVING,
//   S_COLLIDE,
//   S_GAMEOVER,
//   S_ONPAUSE,
//   S_EXIT_STATE
// } snake_state;

// #define ESCAPE 27
// #define KEY_ROTATE_LEFT 'q'
// #define KEY_ROTATE_RIGHT 'e'
// #define KEY_ESCAPE '0'
// #define KEY_PAUSE ' '
// #define KEY_START '\n'

GameInfo updateCurrentState(GameInfo game_info, std::vector<Brick *> &body, GameState *state,
                              Signal signal, WINDOW **windows);
Signal getSignal(int userInput);
void getMoveData(int signal, int *direction, int *angle);

#endif