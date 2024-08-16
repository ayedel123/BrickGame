#include "game_info.h"

void InitGameInfo(GameInfo *game_info, int **field, int speed, int acceleration,
                  int brick_type, const char *file_name) {
  game_info->win_info.height = GAME_WINDOW_HEIGHT;
  game_info->win_info.width = GAME_WINDOW_WIDTH;
  game_info->color_count = COLOR_COUNT;
  game_info->field = field;
  BornBrick(&game_info->current_brick, game_info->win_info.width / 2, 0,
            brick_type, game_info->color_count);
  BornBrick(&game_info->next_brick, game_info->win_info.width / 2, 0,
            brick_type, game_info->color_count);
  game_info->points = 0;
  game_info->level = 1;
  game_info->speed = speed;
  game_info->high_score = ReadRecord(file_name);
  game_info->acceleration = acceleration;
}

void BaseInitGameInfo(GameInfo *game_info) {
  game_info->win_info.height = 0;
  game_info->win_info.width = 0;
  game_info->color_count = 1;
  game_info->field = NULL;
  game_info->current_brick = BRICKS_TYPES[0];
  game_info->next_brick = BRICKS_TYPES[0];
  game_info->level = 0;
  game_info->points = 0;
  game_info->high_score = 0;
  game_info->acceleration = 0;
}

void WriteRecord(const char *filename, int record) {
  FILE *file = fopen(filename, "wb");
  if (file == NULL) {
    return;
  }
  fwrite(&record, sizeof(int), 1, file);
  fclose(file);
}

int ReadRecord(const char *filename) {
  int number = 0;
  FILE *file = fopen(filename, "rb");

  if (file != NULL) {
    fread(&number, sizeof(int), 1, file);
    fclose(file);
  }
  return number;
}

void AddPoints(GameInfo *game_info, int full_lines) {
  int points = 0;
  switch (full_lines) {
    case 0:
      points = 0;
      break;
    case 1:
      points = 100;
      break;
    case 2:
      points = 300;
      break;
    case 3:
      points = 700;
      break;
    case 4:
      points = 1500;
      break;
    default:
      points = 1500;
      break;
  }
  if (game_info->points <= 100000000) game_info->points += points;
  if (game_info->points > game_info->high_score) {
    game_info->high_score = game_info->points;
    WriteRecord("record", game_info->high_score);
  }
  if (game_info->points >= 600 * (game_info->level) && game_info->level < 10) {
    game_info->level = game_info->points / 600 + 1;
  }
}
