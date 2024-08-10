#include "full_line_handler.h"

void dropLines(GameInfo *game_info, int last_line, int linesCount)
{
  for (int i = 0; i < last_line; i++)
  {
    for (int j = 0; j < game_info->win_info.width; j++)
    {
      if (last_line - i - linesCount >= 0)
      {
        game_info->field[last_line - i][j] =
            game_info->field[last_line - i - linesCount][j];
        game_info->field[last_line - i - linesCount][j] = 0;
      }
      else
      {
        game_info->field[last_line - i][j] = 0;
      }
    }
  }
}

int isLineFull(GameInfo *game_info, int line_id)
{
  int counter = 0;
  int result = 0;
  for (int j = 0; j < game_info->win_info.width; j++)
  {
    if (game_info->field[line_id][j] != 0)
    {
      counter++;
    }
  }
  if (counter == game_info->win_info.width)
    result = 1;
  return result;
}

int FullLineHandler(GameInfo *game_info)
{
  int last_line = 0;
  int full_lines = 0;
  for (int i = 0; i < game_info->win_info.height; i++)
  {
    if (isLineFull(game_info, i) != 0)
    {
      full_lines++;
      last_line = i;
    }
  }
  if (full_lines != 0)
  {
    dropLines(game_info, last_line, full_lines);
  }
  return full_lines;
}

int resetBrick(GameInfo *game_info)
{
  int x = game_info->win_info.width / 2;
  int y = 0;
  game_info->current_brick = game_info->next_brick;
  BornBrick(&game_info->next_brick, x, y, RANDOM_BRICK, game_info->color_count);

  int is_end = CheckCollision(game_info, &game_info->current_brick, kDirDown) == COL_STATE_NO ? 0 : 1;
  return is_end;
}