#include "snake_fsm.h"

void spawnAppleHandler(GameInfo_t *gameInfo, game_states *state)
{
  addPoints(gameInfo, 1);
  // if (resetBrick(gameInfo) != COL_STATE_NO)
  //   *state = GAMEOVER;
  // else
  //   *state = MOVING;
  SpawnApple(gameInfo);
  // bornBrick(&gameInfo->nextBrick, gameInfo->winInfo.width / 2, gameInfo->winInfo.height / 2, BRICK_TYPES_COUNT, 2);
  *state = MOVING;
}

void getMoveData(int signal, int *direction, int *angle)
{
  switch (signal)
  {
  case MOVE_UP:
    *direction = DIR_TOP;
    break;
  case MOVE_DOWN:
    *direction = DIR_DOWN;
    break;
  case MOVE_LEFT:
    *direction = DIR_LEFT;
    break;
  case MOVE_RIGHT:
    *direction = DIR_RIGHT;
    break;
  case ROTATE_LEFT:
    *angle = -1;
    break;
  case ROTATE_RIGHT:
    *angle = 1;
    break;
  case NOSIG:
    break;
  };
}

void movingHandler(GameInfo_t *gameInfo, std::vector<Brick *> &body, game_states *state,
                   signals signal, WINDOW **windows)
{
  if (signal == EXIT)
  {
    *state = EXIT_STATE;
  }
  else if (signal == PAUSE)
  {
    *state = ONPAUSE;
  }
  else
  {
    int direction = DIR_STATE;
    int angle = 0;
    getMoveData(signal, &direction, &angle);
    int col = 0;
    if (signal != NOSIG)
      col = MoveBody(gameInfo, body, direction, false);
    gameInfo->currentBrick = **body.begin();
    col = SnakeHandleCollision(gameInfo, col, direction);

    if (col == COL_STATE_CRIT)
    {
      SpawnNode(gameInfo, body);
      if (signal != NOSIG)
        MoveBody(gameInfo, body, direction, true);

      *state = SPAWN_APPLE;
    }
    else if (col == COL_STATE_END)
      *state = GAMEOVER;
  }

  drawField(windows[GAME_WIN], gameInfo);

  printTetrisStats(windows[INFO_WIN], gameInfo, (*state == ONPAUSE) ? 0 : 1);
}

void startHandler(GameInfo_t *gameInfo, std::vector<Brick *> &body, game_states *state,
                  signals signal, WINDOW *gameWin)
{
  gameInfo->currentBrick.x = gameInfo->winInfo.width / 2;
  gameInfo->currentBrick.y = gameInfo->winInfo.height / 2;
  gameInfo->currentBrick.color = 1;
  gameInfo->nextBrick.color = 2;
  clearField(gameInfo->field, gameInfo->winInfo.height,
             gameInfo->winInfo.width);
  moveBrickInField(gameInfo->field, &gameInfo->currentBrick);
  *state = SPAWN_APPLE;
  body.clear();
  body.insert(body.begin(), new Brick{gameInfo->currentBrick});
}

void gameOverHandler(GameInfo_t *gameInfo, game_states *state,
                     signals signal, WINDOW *gameWin)
{

  gameOverMessage(gameWin, gameInfo->winInfo.width, gameInfo->winInfo.width);
  // signal = getSignal(userInput());
  if (signal != NOSIG)
  {
    if (signal != EXIT)
    {
      *state = START;
    }
    else
      *state = EXIT_STATE;
  }
}

void exitHandler(game_states *state)
{
  *state = static_cast<game_states>(EXIT);
}

void pauseHandler(game_states *state, signals signal)
{
  if (signal == PAUSE)
  {
    *state = MOVING;
  }
  else if (signal == EXIT)
  {
    *state = EXIT_STATE;
  }
}

GameInfo_t updateCurrentState(GameInfo_t gameInfo, std::vector<Brick *> &body, game_states *state,
                              signals signal, WINDOW **windows)
{

  switch (*state)
  {

  case START:
    startHandler(&gameInfo, body, state, signal, windows[GAME_WIN]);
    break;
  case SPAWN_APPLE:
    spawnAppleHandler(&gameInfo, state);
    break;
  case MOVING:
    movingHandler(&gameInfo, body, state, signal, windows);
    break;
    break;
  case GAMEOVER:
    gameOverHandler(&gameInfo, state, signal, windows[GAME_WIN]);
    break;
  case ONPAUSE:
    pauseHandler(state, signal);
    break;
  case EXIT_STATE:
    exitHandler(state);
    break;
  }
  return gameInfo;
}

signals getSignal(int userInput)
{
  signals rc = NOSIG;

  switch (userInput)
  {
  case KEY_UP:
    rc = MOVE_UP;
    break;
  case KEY_DOWN:
    rc = MOVE_DOWN;
    break;
  case KEY_LEFT:
    rc = MOVE_LEFT;
    break;
  case KEY_RIGHT:
    rc = MOVE_RIGHT;
    break;
  case KEY_ROTATE_LEFT:
    rc = ROTATE_LEFT;
    break;
  case KEY_ROTATE_RIGHT:
    rc = ROTATE_RIGHT;
    break;
  case KEY_PAUSE:
    rc = PAUSE;
    break;
  case ERR:
    rc = NOSIG;
    break;
  case KEY_START:
    rc = START_SIG;
    break;
  case KEY_ESCAPE:
    rc = EXIT;
    break;
  default:
    rc = NOSIG;
    break;
  }

  return rc;
}
