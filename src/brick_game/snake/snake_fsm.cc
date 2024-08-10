#include "snake_fsm.h"

void spawnAppleHandler(GameInfo *game_info, GameState *state)
{
  AddPoints(game_info, 1);

  SpawnApple(game_info);
  *state = kMoving;
}

void GetMoveData(int signal, int *direction, int *angle)
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

void movingHandler(GameInfo *game_info, std::vector<Brick *> &body, GameState *state,
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
    GetMoveData(signal, &direction, &angle);
    int col = 0;
    if (signal != kNosig)
      col = MoveBody(game_info, body, direction, false);
    game_info->current_brick = **body.begin();
    col = SnakeHandleCollision(game_info, col, direction);

    if (col == COL_STATE_CRIT)
    {
      SpawnNode(game_info, body);
      if (signal != kNosig)
        MoveBody(game_info, body, direction, true);

      *state = kSpawnApple;
    }
    else if (col == COL_STATE_END)
      *state = kGameOver;
  }

  drawField(windows[kGameWin], game_info);

  printTetrisStats(windows[kInfoWin], game_info, (*state == kOnPause) ? 0 : 1);
}

void startHandler(GameInfo *game_info, std::vector<Brick *> &body, GameState *state,
                  Signal signal, WINDOW *gameWin)
{
  game_info->current_brick.x = game_info->win_info.width / 2;
  game_info->current_brick.y = game_info->win_info.height / 2;
  game_info->current_brick.color = 1;
  game_info->next_brick.color = 2;
  ClearField(game_info->field, game_info->win_info.height,
             game_info->win_info.width);
  moveBrickInField(game_info->field, &game_info->current_brick);
  *state = kSpawnApple;
  body.clear();
  body.insert(body.begin(), new Brick{game_info->current_brick});
}

void gameOverHandler(GameInfo *game_info, GameState *state,
                     Signal signal, WINDOW *gameWin)
{

  gameOverMessage(gameWin, game_info->win_info.width, game_info->win_info.width);
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

GameInfo UpdateCurrentState(GameInfo game_info, std::vector<Brick *> &body, GameState *state,
                            Signal signal, WINDOW **windows)
{

  switch (*state)
  {

  case kStart:
    startHandler(&game_info, body, state, signal, windows[kGameWin]);
    break;
  case kSpawnApple:
    spawnAppleHandler(&game_info, state);
    break;
  case kMoving:
    movingHandler(&game_info, body, state, signal, windows);
    break;
    break;
  case kGameOver:
    gameOverHandler(&game_info, state, signal, windows[kGameWin]);
    break;
  case kOnPause:
    pauseHandler(state, signal);
    break;
  case kExitState:
    exitHandler(state);
    break;
  }
  return game_info;
}

Signal GetSignal(int userInput)
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
