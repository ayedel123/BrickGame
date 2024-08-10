#include "moveBrick.h"

// доработка

void moveBrickCords(Brick *brick, int direction)
{
  if (direction == kDirRight || direction == kDirLeft)
  {
    brick->x += direction;
  }
  if (direction == kDirTop || direction == kDirDown)
  {
    brick->y += direction / 2;
  }
}

void rotateBrickCords(Brick *brick, int angle)
{
  int tmp = 0;
  for (int i = 0; i < 4; i++)
  {
    tmp = brick->cords[i][0];
    brick->cords[i][0] = angle * brick->cords[i][1];
    brick->cords[i][1] = -angle * tmp;
  }
}

void deleteFromField(int **field, Brick *brick)
{
  for (int i = 0; i < 4; i++)
  {
    field[brick->y + brick->cords[i][1]][brick->x + brick->cords[i][0]] = 0;
  }
}

void moveBrickInField(int **field, Brick *brick)
{

  for (int i = 0; i < 4; i++)
  {
    field[brick->y + brick->cords[i][1]][brick->x + brick->cords[i][0]] =
        brick->color;
  }
}

int TryToMove(GameInfo_t *gameInfo, Brick *oldBrick, int direction, int angle)
{

  int result = COL_STATE_NO;
  for (int i = 0; i < 4 && result == COL_STATE_NO; i++)
  {
    result = checkOutOfBounds(oldBrick, i, gameInfo->winInfo.width,
                              gameInfo->winInfo.height, kDirState);
  }
  if (result == COL_STATE_NO)
  {
    deleteFromField(gameInfo->field, oldBrick);

    if (direction != kDirState)
    {
      moveBrickCords(oldBrick, direction);
    }
    else if (angle != 0 && direction == kDirState)
    {
      rotateBrickCords(oldBrick, angle);
    }

    result = checkCollision(gameInfo, oldBrick, direction);
  }
  return result;
}

int moveBrick(GameInfo_t *gameInfo, Brick *oldBrick, int direction, int angle)
{
  Brick newBrick = *oldBrick;
  int result = COL_STATE_NO;
  result = TryToMove(gameInfo, &newBrick, direction, angle);

  if (result == COL_STATE_NO)
  {
    *oldBrick = newBrick;
  }
  moveBrickInField(gameInfo->field, oldBrick);
  return result;
}

int ForceMoveBrick(GameInfo_t *gameInfo, Brick *oldBrick, int direction, int angle)
{
  deleteFromField(gameInfo->field, oldBrick);
  moveBrickCords(oldBrick, direction);
  moveBrickInField(gameInfo->field, oldBrick);
  return 0;
}