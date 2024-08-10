#include "tetris_fsm.h"


void TetrisSpawHandler(GameInfo_t *gameInfo, GameState *state)
{
  addPoints(gameInfo, fullLineHandler(gameInfo));
  if (resetBrick(gameInfo) != COL_STATE_NO)
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

void TetrisMovingHandler(GameInfo_t *gameInfo, GameState *state,
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
    int col = moveBrick(gameInfo, &gameInfo->currentBrick, direction, angle);
    col = TetrisHandleCollision(col, direction);
    if (col == COL_STATE_CRIT)
    {
      *state = kSpawn;
    }
  }
  else
    *state = kExitState;

  drawField(windows[kGameWin], gameInfo);
  if (*state == kOnPause)
  {
    printTetrisStats(windows[kInfoWin], gameInfo, 0);
  }
  else
  {
    printTetrisStats(windows[kInfoWin], gameInfo, 1);
  }
}

void TetrisStartHandler(GameInfo_t *gameInfo, GameState *state,
                  Signal signal, WINDOW *gameWin)
{
  startMessage(gameWin, gameInfo->winInfo.width, gameInfo->winInfo.width);

  if (signal == kStartSig)
  {
    clearField(gameInfo->field, gameInfo->winInfo.height,
               gameInfo->winInfo.width);
    *state = kSpawn;
  }
  else if (signal == kExit)
  {
    *state = kExitState;
  }
}

void TetrisGameOverHandler(GameInfo_t *gameInfo, GameState *state,
                     Signal signal, WINDOW *gameWin)
{

  gameOverMessage(gameWin, gameInfo->winInfo.width, gameInfo->winInfo.width);
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

GameInfo_t TetrisUpdateCurrentState(GameInfo_t gameInfo, GameState *state,
                              Signal signal, WINDOW **windows)
{

  switch (*state)
  {

  case kStart:
    TetrisStartHandler(&gameInfo, state, signal, windows[kGameWin]);
    break;
  case kSpawn:
    TetrisSpawHandler(&gameInfo, state);
    break;
  case kMoving:
    TetrisMovingHandler(&gameInfo, state, signal, windows);
    break;
    break;
  case kGameOver:
    TetrisGameOverHandler(&gameInfo, state, signal, windows[kGameWin]);
    break;
  case kOnPause:
    TetrisPauseHandler(state, signal);
    break;
  case kExitState:
    TetrisExitHandler(state);
    break;
  }
  return gameInfo;
}

Signal TetrisGetSignal(int userInput)
{
  Signal rc = kNosig;

  // if (userInput == KEY_UP)
  //   rc = kMoveUp;
  // else
  if (userInput == KEY_DOWN)
    rc = kMoveDown;
  else if (userInput == KEY_LEFT)
    rc = kMoveLeft;
  else if (userInput == KEY_RIGHT)
    rc = kMoveRight;
  else if (userInput == KEY_ROTATE_LEFT)
    rc = kRotateLeft;
  else if (userInput == KEY_ROTATE_RIGHT)
    rc = kRotateRight;
  else if (userInput == KEY_PAUSE)
    rc = kPause;
  else if (userInput == ERR)
    rc = kNosig;
  else if (userInput == KEY_START)
    rc = kStartSig;
  else if (userInput == KEY_ESCAPE)
    rc = kExit;

  return rc;
}
