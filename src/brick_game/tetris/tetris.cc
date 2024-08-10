
#include "tetris.h"

// void TetrisSetUp(WINDOW **windows, int winCount, GameInfo_t *gameInfo, int **field)
// {
//   srand(time(0));
//   cursesSetUp();
//   setUpBrickGameWindows(windows, winCount);
//   initGameInfo(gameInfo, field, GAME_SPEED, GMAE_ACCELERATION, RANDOM_BRICK);
// }

void TetrisSetUp(GameInfo_t *gameInfo, int **field)
{
  initGameInfo(gameInfo, field, GAME_SPEED, GMAE_ACCELERATION, RANDOM_BRICK);
}

int TetrisGameLoop(GameInfo_t *gameInfo, WINDOW **windows)
{

  long long startTime = getTimeInMS();
  long long endTime = 0;
  int isEnd = 0;
  int keyVal = 0;
  int input = 0;
  GameState state = kStart;

  while (keyVal != 404 && state != kExitState)
  {
    input = userInput();
    *gameInfo =
        TetrisUpdateCurrentState(*gameInfo, &state, TetrisGetSignal(input), windows);

    endTime = getTimeInMS();
    if (state == kMoving &&
        endTime - startTime >=
            gameInfo->speed - gameInfo->level * gameInfo->acceleration)
    {
      startTime = getTimeInMS();
      *gameInfo = TetrisUpdateCurrentState(*gameInfo, &state, kMoveDown, windows);
    }
  }

  return 0;
}

int TetrisHandleCollision(int col, int dir)
{
  if (col == COL_STATE_NO)
    return COL_STATE_NO;

  if (dir != kDirDown)
    col = COL_STATE_COL;
  else
    col = COL_STATE_CRIT;
  return col;
}

// int main()
// {
//   WINDOW *windows[3];
//   GameInfo_t gameInfo;
//   int **field = NULL;
//   initField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
//   clearField(field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
//   setUp(windows, 2, &gameInfo, field);
//   gameLoop(&gameInfo, windows);
//   endwin();
//   deleteField(field, GAME_WINDOW_HEIGHT);

//   return 0;
// }