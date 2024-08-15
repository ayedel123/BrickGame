#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE_GAME_LOOP_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE_GAME_LOOP_H_

#include "../../gui/cli/cli.h"
#include "../back/back.h"

extern "C"
{
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
}
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "./snake_class.h"
// #include "./snake_fsm.h"
#include "snake_update_current_state.h"
int SnakeGameLoop(s21::Snake &snake, WINDOW **windows);

// #define SNAKE_GAME_SPEED 350
// #define SNAKE_GAME_ACCELERATION 20

#endif