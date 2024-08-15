
#include "tetris.h"

void TetrisSetUp(GameInfo *game_info, int **field)
{
  InitGameInfo(game_info, field, TETRIS_GAME_SPEED, TETRIS_GAME_ACCELERATION, RANDOM_BRICK, "tetris_record");
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
