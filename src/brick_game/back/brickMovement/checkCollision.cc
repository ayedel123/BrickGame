#include "checkCollision.h"

int checkCollisionBrick(int **field, Brick *brick, int cordI, int direction)
{

  int result = field[brick->y + brick->cords[cordI][1]]
                    [brick->x + brick->cords[cordI][0]];

  // if (result != COL_STATE_NO && direction == DIR_DOWN)
  // {
  //   result = COL_STATE_COL;
  // }
  return result;
}

int checkOutOfBounds(Brick *brick, int cordI, int width, int height,
                     int direction)
{
  int brickX = brick->x + brick->cords[cordI][0];
  int brickY = brick->y + brick->cords[cordI][1];
  int result = (brickX < 0 || brickX >= width || brickY < 0 || brickY >= height)
                   ? COLLIDE_WITH_BORDER
                   : COL_STATE_NO;

  result =
      (brickY >= height && direction != DIR_STATE) ? COLLIDE_WITH_BORDER : result;
  return result;
}

int checkCollision(GameInfo_t *gameInfo, Brick *brick, int direction)
{
  int result = 0;
  for (int i = 0; i < 4 && result == COL_STATE_NO; i++)
  {
    result = checkOutOfBounds(brick, i, gameInfo->winInfo.width,
                              gameInfo->winInfo.height, direction);
    if (result == COL_STATE_NO)
    {
      result = checkCollisionBrick(gameInfo->field, brick, i, direction);
    }
  }

  return result;
}