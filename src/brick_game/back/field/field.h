#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_BACK_FIELD_FIELD_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_BACK_FIELD_FIELD_H_
extern "C" {
#include <stdlib.h>
}
int DeleteField(int **field, int rows);
void ClearField(int **field, int rows, int cols);
int InitField(int ***field, int rows, int cols);

#endif