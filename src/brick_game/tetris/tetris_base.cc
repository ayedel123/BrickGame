
#include "tetris_base.h"

void TetrisSetUp(GameInfo *game_info, int **field) {
  InitGameInfo(game_info, field, TETRIS_GAME_SPEED, TETRIS_GAME_ACCELERATION,
               RANDOM_BRICK, "tetris_record");
}

int TetrisHandleCollision(int col, int dir) {
  if (col == COL_STATE_NO) return COL_STATE_NO;

  if (dir != kDirDown)
    col = COL_STATE_COL;
  else
    col = COL_STATE_CRIT;
  return col;
}

void TetrisAddPoints(GameInfo *game_info, int full_lines) {
  int points = (full_lines * 100 > 1500) ? 1500 : full_lines * 100;

  if (game_info->points <= 100000000) game_info->points += points;
  if (game_info->points > game_info->high_score) {
    game_info->high_score = game_info->points;
    WriteRecord("tetris_record", game_info->high_score);
  }
  if (game_info->points >= 600 * (game_info->level) && game_info->level < 10) {
    game_info->level = game_info->points / 600 + 1;
  }
}

void DropLines(GameInfo *game_info, int last_line, int linesCount) {
  for (int i = 0; i < last_line; i++) {
    for (int j = 0; j < game_info->win_info.width; j++) {
      if (last_line - i - linesCount >= 0) {
        game_info->field[last_line - i][j] =
            game_info->field[last_line - i - linesCount][j];
        game_info->field[last_line - i - linesCount][j] = 0;
      } else {
        game_info->field[last_line - i][j] = 0;
      }
    }
  }
}

int IsLineFull(GameInfo *game_info, int line_id) {
  int counter = 0;
  int result = 0;
  for (int j = 0; j < game_info->win_info.width; j++) {
    if (game_info->field[line_id][j] != 0) {
      counter++;
    }
  }
  if (counter == game_info->win_info.width) result = 1;
  return result;
}

int FullLineHandler(GameInfo *game_info) {
  int last_line = 0;
  int full_lines = 0;
  for (int i = 0; i < game_info->win_info.height; i++) {
    if (IsLineFull(game_info, i) != 0) {
      full_lines++;
      last_line = i;
    }
  }
  if (full_lines != 0) {
    DropLines(game_info, last_line, full_lines);
  }
  return full_lines;
}

int resetBrick(GameInfo *game_info) {
  int x = game_info->win_info.width / 2;
  int y = 0;
  game_info->current_brick = game_info->next_brick;
  BornBrick(&game_info->next_brick, x, y, RANDOM_BRICK, game_info->color_count);

  int is_end = CheckCollision(game_info, &game_info->current_brick, kDirDown) ==
                       COL_STATE_NO
                   ? 0
                   : 1;
  return is_end;
}
