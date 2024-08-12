
#include "tetris.h"

// void TetrisSetUp(WINDOW **windows, int win_count, GameInfo *game_info, int **field)
// {
//   srand(time(0));
//   CursesSetUp();
//   SetUpBrickGameWindows(windows, win_count);
//   InitGameInfo(game_info, field, TETRIS_GAME_SPEED, TETRIS_GAME_ACCELERATION, RANDOM_BRICK);
// }

void TetrisSetUp(GameInfo *game_info, int **field)
{
  InitGameInfo(game_info, field, TETRIS_GAME_SPEED, TETRIS_GAME_ACCELERATION, RANDOM_BRICK, "tetris_record");
}

int TetrisGameLoop(GameInfo *game_info, WINDOW **windows)
{

  long long startTime = GetTimeInMS();
  long long endTime = 0;
  int keyVal = 0;
  int input = 0;
  GameState state = kStart;

  while (keyVal != 404 && state != kExitState)
  {
    input = UserInput();
    *game_info =
        TetrisUpdateCurrentState(*game_info, &state, TetrisGetSignal(input), windows);

    endTime = GetTimeInMS();
    if (state == kMoving &&
        endTime - startTime >=
            game_info->speed - game_info->level * game_info->acceleration)
    {
      startTime = GetTimeInMS();
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

void TetrisAddPoints(GameInfo *game_info, int full_lines)
{

  int points = (full_lines * 100 > 1500) ? 1500 : full_lines * 100;

  if (game_info->points <= 100000000)
    game_info->points += points;
  if (game_info->points > game_info->high_score)
  {
    game_info->high_score = game_info->points;
    WriteRecord("tetris_record", game_info->high_score);
  }
  if (game_info->points >= 600 * (game_info->level) && game_info->level < 10)
  {
    game_info->level = game_info->points / 600 + 1;
  }
}
