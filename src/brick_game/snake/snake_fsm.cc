#include "snake_fsm.h"

void spawnAppleHandler(GameInfo_t *gameInfo, GameState *state)
{
  addPoints(gameInfo, 1);
  // if (resetBrick(gameInfo) != COL_STATE_NO)
  //   *state = kGameOver;
  // else
  //   *state = kMoving;
  SpawnApple(gameInfo);
  // bornBrick(&gameInfo->nextBrick, gameInfo->winInfo.width / 2, gameInfo->winInfo.height / 2, BRICK_TYPES_COUNT, 2);
  *state = kMoving;
}

void getMoveData(int signal, int *direction, int *angle)
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

void movingHandler(GameInfo_t *gameInfo, std::vector<Brick *> &body, GameState *state,
                   Signal signal, WINDOW **windows)
{
  if (signal == kExit)
  {
    *state = kExitState;
  }
  else if (signal == kPause)
  {
    *state = kOnPause;
  }
  else
  {
    int direction = kDirState;
    int angle = 0;
    getMoveData(signal, &direction, &angle);
    int col = 0;
    if (signal != kNosig)
      col = MoveBody(gameInfo, body, direction, false);
    gameInfo->currentBrick = **body.begin();
    col = SnakeHandleCollision(gameInfo, col, direction);

    if (col == COL_STATE_CRIT)
    {
      SpawnNode(gameInfo, body);
      if (signal != kNosig)
        MoveBody(gameInfo, body, direction, true);

      *state = kSpawnApple;
    }
    else if (col == COL_STATE_END)
      *state = kGameOver;
  }

  drawField(windows[kGameWin], gameInfo);

  printTetrisStats(windows[kInfoWin], gameInfo, (*state == kOnPause) ? 0 : 1);
}

void startHandler(GameInfo_t *gameInfo, std::vector<Brick *> &body, GameState *state,
                  Signal signal, WINDOW *gameWin)
{
  gameInfo->currentBrick.x = gameInfo->winInfo.width / 2;
  gameInfo->currentBrick.y = gameInfo->winInfo.height / 2;
  gameInfo->currentBrick.color = 1;
  gameInfo->nextBrick.color = 2;
  clearField(gameInfo->field, gameInfo->winInfo.height,
             gameInfo->winInfo.width);
  moveBrickInField(gameInfo->field, &gameInfo->currentBrick);
  *state = kSpawnApple;
  body.clear();
  body.insert(body.begin(), new Brick{gameInfo->currentBrick});
}

void gameOverHandler(GameInfo_t *gameInfo, GameState *state,
                     Signal signal, WINDOW *gameWin)
{

  gameOverMessage(gameWin, gameInfo->winInfo.width, gameInfo->winInfo.width);
  // signal = getSignal(userInput());
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

void exitHandler(GameState *state)
{
  *state = static_cast<GameState>(kExit);
}

void pauseHandler(GameState *state, Signal signal)
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

GameInfo_t updateCurrentState(GameInfo_t gameInfo, std::vector<Brick *> &body, GameState *state,
                              Signal signal, WINDOW **windows)
{

  switch (*state)
  {

  case kStart:
    startHandler(&gameInfo, body, state, signal, windows[kGameWin]);
    break;
  case kSpawnApple:
    spawnAppleHandler(&gameInfo, state);
    break;
  case kMoving:
    movingHandler(&gameInfo, body, state, signal, windows);
    break;
    break;
  case kGameOver:
    gameOverHandler(&gameInfo, state, signal, windows[kGameWin]);
    break;
  case kOnPause:
    pauseHandler(state, signal);
    break;
  case kExitState:
    exitHandler(state);
    break;
  }
  return gameInfo;
}

Signal getSignal(int userInput)
{
  Signal rc = kNosig;

  switch (userInput)
  {
  case KEY_UP:
    rc = kMoveUp;
    break;
  case KEY_DOWN:
    rc = kMoveDown;
    break;
  case KEY_LEFT:
    rc = kMoveLeft;
    break;
  case KEY_RIGHT:
    rc = kMoveRight;
    break;
  case KEY_ROTATE_LEFT:
    rc = kRotateLeft;
    break;
  case KEY_ROTATE_RIGHT:
    rc = kRotateRight;
    break;
  case KEY_PAUSE:
    rc = kPause;
    break;
  case ERR:
    rc = kNosig;
    break;
  case KEY_START:
    rc = kStartSig;
    break;
  case KEY_ESCAPE:
    rc = kExit;
    break;
  default:
    rc = kNosig;
    break;
  }

  return rc;
}
