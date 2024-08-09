#ifndef __TETRIS_FIELD__
#define __TETRIS_FIELD__
extern "C"
{
#include <stdlib.h>
}
int deleteField(int **field, int rows);
void clearField(int **field, int rows, int cols);
int initField(int ***field, int rows, int cols);

#endif