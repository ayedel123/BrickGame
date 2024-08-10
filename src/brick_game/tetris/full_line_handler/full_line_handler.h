#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_FULL_LINE_HANDLER_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_FULL_LINE_HANDLER_H_

#include "../../back/back.h"

int FullLineHandler(GameInfo *game_info);

int isLineFull(GameInfo *game_info, int line_id);
void dropLines(GameInfo *game_info, int last_line, int linesCount);
int resetBrick(GameInfo *game_info);

#endif