
#include "tetris.h"

// void TetrisSetUp(WINDOW **windows, int winCount, GameInfo *game_info, int **field)
// {
//   srand(time(0));
//   cursesSetUp();
//   setUpBrickGameWindows(windows, winCount);
//   InitGameInfo(game_info, field, GAME_SPEED, GMAE_ACCELERATION, RANDOM_BRICK);
// }

void TetrisSetUp(GameInfo *game_info, int **field)
{
  InitGameInfo(game_info, field, GAME_SPEED, GMAE_ACCELERATION, RANDOM_BRICK);
}

int TetrisGameLoop(GameInfo *game_info, WINDOW **windows)
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
    *game_info =
        TetrisUpdateCurrentState(*game_info, &state, TetrisGetSignal(input), windows);

    endTime = getTimeInMS();
    if (state == kMoving &&
        endTime - startTime >=
            game_info->speed - game_info->level * game_info->acceleration)
    {
      startTime = getTimeInMS();
      *game_info = TetrisUpdateCurrentState(*game_info, &state, kMoveDown, windows);
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
//   GameInfo game_info;
//   int **field = NULL;
//   InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
//   ClearField(field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
//   setUp(windows, 2, &game_info, field);
//   gameLoop(&game_info, windows);
//   endwin();
//   DeleteField(field, GAME_WINDOW_HEIGHT);

//   return 0;
// }