#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_BACK_GAME_INFO_GAME_INFO_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_BACK_GAME_INFO_GAME_INFO_H_

#include "../bricks/bricks.h"
#include "../common/defines.h"
extern "C" {
#include <stdio.h>
#include <stdlib.h>
}
typedef struct {
  WinInfo win_info;
  Brick current_brick;
  Brick next_brick;
  int color_count;
  int points;
  int **field;
  int level;
  int high_score;
  int speed;
  int acceleration;
  int pause;

} GameInfo;

void AddPoints(GameInfo *game_info, int full_lines);
void WriteRecord(const char *filename, int record);
int ReadRecord(const char *filename);
void InitGameInfo(GameInfo *game_info, int **field, int speed, int acceleration,
                  int brick_type, const char *file_name);
void BaseInitGameInfo(GameInfo *game_info);

#endif