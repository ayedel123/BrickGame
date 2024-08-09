#include "tetris_fsm.h"


void TetrisSpawHandler(GameInfo_t *gameInfo, game_states *state)
{
  addPoints(gameInfo, fullLineHandler(gameInfo));
  if (resetBrick(gameInfo) != COL_STATE_NO)
    *state = GAMEOVER;
  else
    *state = MOVING;
}

void TetrisGetMoveData(int signal, int *direction, int *angle)
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

void TetrisMovingHandler(GameInfo_t *gameInfo, game_states *state,
                   signals signal, WINDOW **windows)
{

  if (signal == PAUSE)
  {
    *state = ONPAUSE;
  }
  else if (signal != EXIT)
  {
    int direction = DIR_STATE;
    int angle = 0;
    TetrisGetMoveData(signal, &direction, &angle);
    int col = moveBrick(gameInfo, &gameInfo->currentBrick, direction, angle);
    col = TetrisHandleCollision(col, direction);
    if (col == COL_STATE_CRIT)
    {
      *state = SPAWN;
    }
  }
  else
    *state = EXIT_STATE;

  drawField(windows[GAME_WIN], gameInfo);
  if (*state == ONPAUSE)
  {
    printTetrisStats(windows[INFO_WIN], gameInfo, 0);
  }
  else
  {
    printTetrisStats(windows[INFO_WIN], gameInfo, 1);
  }
}

void TetrisStartHandler(GameInfo_t *gameInfo, game_states *state,
                  signals signal, WINDOW *gameWin)
{
  startMessage(gameWin, gameInfo->winInfo.width, gameInfo->winInfo.width);

  if (signal == START_SIG)
  {
    clearField(gameInfo->field, gameInfo->winInfo.height,
               gameInfo->winInfo.width);
    *state = SPAWN;
  }
  else if (signal == EXIT)
  {
    *state = EXIT_STATE;
  }
}

void TetrisGameOverHandler(GameInfo_t *gameInfo, game_states *state,
                     signals signal, WINDOW *gameWin)
{

  gameOverMessage(gameWin, gameInfo->winInfo.width, gameInfo->winInfo.width);
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

void TetrisExitHandler(game_states *state) { *state = static_cast<game_states>(EXIT); }

void TetrisPauseHandler(game_states *state, signals signal)
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

GameInfo_t TetrisUpdateCurrentState(GameInfo_t gameInfo, game_states *state,
                              signals signal, WINDOW **windows)
{

  switch (*state)
  {

  case START:
    TetrisStartHandler(&gameInfo, state, signal, windows[GAME_WIN]);
    break;
  case SPAWN:
    TetrisSpawHandler(&gameInfo, state);
    break;
  case MOVING:
    TetrisMovingHandler(&gameInfo, state, signal, windows);
    break;
    break;
  case GAMEOVER:
    TetrisGameOverHandler(&gameInfo, state, signal, windows[GAME_WIN]);
    break;
  case ONPAUSE:
    TetrisPauseHandler(state, signal);
    break;
  case EXIT_STATE:
    TetrisExitHandler(state);
    break;
  }
  return gameInfo;
}

signals TetrisGetSignal(int userInput)
{
  signals rc = NOSIG;

  // if (userInput == KEY_UP)
  //   rc = MOVE_UP;
  // else
  if (userInput == KEY_DOWN)
    rc = MOVE_DOWN;
  else if (userInput == KEY_LEFT)
    rc = MOVE_LEFT;
  else if (userInput == KEY_RIGHT)
    rc = MOVE_RIGHT;
  else if (userInput == KEY_ROTATE_LEFT)
    rc = ROTATE_LEFT;
  else if (userInput == KEY_ROTATE_RIGHT)
    rc = ROTATE_RIGHT;
  else if (userInput == KEY_PAUSE)
    rc = PAUSE;
  else if (userInput == ERR)
    rc = NOSIG;
  else if (userInput == KEY_START)
    rc = START_SIG;
  else if (userInput == KEY_ESCAPE)
    rc = EXIT;

  return rc;
}
