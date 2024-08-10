#include "fullLineHandler.h"

void dropLines(GameInfo *game_info, int lastLine, int linesCount)
{
  for (int i = 0; i < lastLine; i++)
  {
    for (int j = 0; j < game_info->win_info.width; j++)
    {
      if (lastLine - i - linesCount >= 0)
      {
        game_info->field[lastLine - i][j] =
            game_info->field[lastLine - i - linesCount][j];
        game_info->field[lastLine - i - linesCount][j] = 0;
      }
      else
      {
        game_info->field[lastLine - i][j] = 0;
      }
    }
  }
}

int isLineFull(GameInfo *game_info, int lineId)
{
  int counter = 0;
  int result = 0;
  for (int j = 0; j < game_info->win_info.width; j++)
  {
    if (game_info->field[lineId][j] != 0)
    {
      counter++;
    }
  }
  if (counter == game_info->win_info.width)
    result = 1;
  return result;
}

int fullLineHandler(GameInfo *game_info)
{
  int lastLine = 0;
  int fullLines = 0;
  for (int i = 0; i < game_info->win_info.height; i++)
  {
    if (isLineFull(game_info, i) != 0)
    {
      fullLines++;
      lastLine = i;
    }
  }
  if (fullLines != 0)
  {
    dropLines(game_info, lastLine, fullLines);
  }
  return fullLines;
}

int resetBrick(GameInfo *game_info)
{
  int x = game_info->win_info.width / 2;
  int y = 0;
  game_info->current_brick = game_info->next_Brick;
  BornBrick(&game_info->next_Brick, x, y, RANDOM_BRICK, game_info->color_count);

  int isEnd = CheckCollision(game_info, &game_info->current_brick, kDirDown) == COL_STATE_NO ? 0 : 1;
  return isEnd;
}