#include "tetris_fsm.h"


void TetrisSpawHandler(GameInfo *game_info, GameState *state)
{
  AddPoints(game_info, FullLineHandler(game_info));
  if (resetBrick(game_info) != COL_STATE_NO)
    *state = kGameOver;
  else
    *state = kMoving;
}

void TetrisGetMoveData(int signal, int *direction, int *angle)
{
  switch (signal)
  {
  case kMoveUp:
    *direction = kDirTop;
    break;
  case kMoveDown:
    *direction = kDirDown;
    break;
  case kMoveLeft:
    *direction = kDirLeft;
    break;
  case kMoveRight:
    *direction = kDirRight;
    break;
  case kRotateLeft:
    *angle = -1;
    break;
  case kRotateRight:
    *angle = 1;
    break;
  case kNosig:
    break;
  };
}

void TetrisMovingHandler(GameInfo *game_info, GameState *state,
                   Signal signal, WINDOW **windows)
{

  if (signal == kPause)
  {
    *state = kOnPause;
  }
  else if (signal != kExit)
  {
    int direction = kDirState;
    int angle = 0;
    TetrisGetMoveData(signal, &direction, &angle);
    int col = moveBrick(game_info, &game_info->current_brick, direction, angle);
    col = TetrisHandleCollision(col, direction);
    if (col == COL_STATE_CRIT)
    {
      *state = kSpawn;
    }
  }
  else
    *state = kExitState;

  DrawField(windows[kGameWin], game_info);
  if (*state == kOnPause)
  {
    printTetrisStats(windows[kInfoWin], game_info, 0);
  }
  else
  {
    printTetrisStats(windows[kInfoWin], game_info, 1);
  }
}

void TetrisStartHandler(GameInfo *game_info, GameState *state,
                  Signal signal, WINDOW *gameWin)
{
  StartMessage(gameWin, game_info->win_info.width, game_info->win_info.width);

  if (signal == kStartSig)
  {
    ClearField(game_info->field, game_info->win_info.height,
               game_info->win_info.width);
    *state = kSpawn;
  }
  else if (signal == kExit)
  {
    *state = kExitState;
  }
}

void TetrisGameOverHandler(GameInfo *game_info, GameState *state,
                     Signal signal, WINDOW *gameWin)
{

  GameOverMessage(gameWin, game_info->win_info.width, game_info->win_info.width);
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

void TetrisExitHandler(GameState *state) { *state = static_cast<GameState>(kExit); }

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

GameInfo TetrisUpdateCurrentState(GameInfo game_info, GameState *state,
                              Signal signal, WINDOW **windows)
{

  switch (*state)
  {

  case kStart:
    TetrisStartHandler(&game_info, state, signal, windows[kGameWin]);
    break;
  case kSpawn:
    TetrisSpawHandler(&game_info, state);
    break;
  case kMoving:
    TetrisMovingHandler(&game_info, state, signal, windows);
    break;
    break;
  case kGameOver:
    TetrisGameOverHandler(&game_info, state, signal, windows[kGameWin]);
    break;
  case kOnPause:
    TetrisPauseHandler(state, signal);
    break;
  case kExitState:
    TetrisExitHandler(state);
    break;
  }
  return game_info;
}

Signal TetrisGetSignal(int UserInput)
{
  Signal rc = kNosig;

  // if (UserInput == KEY_UP)
  //   rc = kMoveUp;
  // else
  if (UserInput == KEY_DOWN)
    rc = kMoveDown;
  else if (UserInput == KEY_LEFT)
    rc = kMoveLeft;
  else if (UserInput == KEY_RIGHT)
    rc = kMoveRight;
  else if (UserInput == KEY_ROTATE_LEFT)
    rc = kRotateLeft;
  else if (UserInput == KEY_ROTATE_RIGHT)
    rc = kRotateRight;
  else if (UserInput == KEY_PAUSE)
    rc = kPause;
  else if (UserInput == ERR)
    rc = kNosig;
  else if (UserInput == KEY_START)
    rc = kStartSig;
  else if (UserInput == KEY_ESCAPE)
    rc = kExit;

  return rc;
}
