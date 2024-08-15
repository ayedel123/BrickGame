#include "tetris_fsm.h"

void TetrisSpawHandler(GameInfo *game_info, GameState *state)
{
  TetrisAddPoints(game_info, FullLineHandler(game_info));
  if (resetBrick(game_info) != COL_STATE_NO)
    *state = kGameOver;
  else
    *state = kMoving;
}


void TetrisMovingHandler(GameInfo *game_info, GameState *state,
                         Signal signal)
{

  if (signal == kPause)
  {
    *state = kOnPause;
  }
  else if (signal != kExit)
  {
    int direction = kDirState;
    int angle = 0;
    GetMoveData(signal, &direction, &angle);
    int col = MoveBrick(game_info, &game_info->current_brick, direction, angle);
    col = TetrisHandleCollision(col, direction);
    if (col == COL_STATE_CRIT)
    {
      *state = kSpawn;
    }
  }
  else
    *state = kExitState;
}

void TetrisStartHandler(GameInfo *game_info, GameState *state)
{
  ClearField(game_info->field, game_info->win_info.height,
             game_info->win_info.width);
  *state = kSpawn;
}

void TetrisGameOverHandler(GameState *state,
                           Signal signal)
{

  if (signal != kNosig)
  {
    if (signal != kExit)
    {
      *state = kStart;
    }
    else
      *state = kExitState;
  }
}

void TetrisExitHandler(GameInfo *game_info, GameState *state)
{
  ClearField(game_info->field, game_info->win_info.height, game_info->win_info.width);
  *state = static_cast<GameState>(kExit);
}

void TetrisPauseHandler(GameState *state, Signal signal)
{
  if (signal == kPause)
  {
    *state = kMoving;
  }
  else if (signal == kExit)
  {
    *state = kExitState;
  }
}

void TetrisUpdateCurrentState(GameInfo *game_info, GameState *state,
                              Signal signal)
{

  switch (*state)
  {

  case kSpawn:
    TetrisSpawHandler(game_info, state);
    break;
  case kMoving:
    TetrisMovingHandler(game_info, state, signal);
    break;
    break;
  case kGameOver:
    TetrisGameOverHandler(state, signal);
    break;
  case kOnPause:
    TetrisPauseHandler(state, signal);
    break;
  case kExitState:
    TetrisExitHandler(game_info, state);
    break;
  default:
    TetrisStartHandler(game_info, state);
    break;
  }
}
