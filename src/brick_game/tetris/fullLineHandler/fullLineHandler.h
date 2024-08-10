#ifndef __TETRIS_FULL_LINE_HANDLER__
#define __TETRIS_FULL_LINE_HANDLER__

#include "../../back/back.h"

int fullLineHandler(GameInfo *game_info);

int isLineFull(GameInfo *game_info, int lineId);
void dropLines(GameInfo *game_info, int lastLine, int linesCount);
int resetBrick(GameInfo *game_info);

#endif