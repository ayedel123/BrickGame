#include "check_collision.h"

int CheckCollisionBrick(int **field, Brick *brick, int cordI) {
  int result = field[brick->y + brick->cords[cordI][1]]
                    [brick->x + brick->cords[cordI][0]];

  return result;
}

int CheckOutOfBounds(Brick *brick, int cordI, int width, int height,
                     int direction) {
  int brickX = brick->x + brick->cords[cordI][0];
  int brickY = brick->y + brick->cords[cordI][1];
  int result = (brickX < 0 || brickX >= width || brickY < 0 || brickY >= height)
                   ? COLLIDE_WITH_BORDER
                   : COL_STATE_NO;

  result = (brickY >= height && direction != kDirState) ? COLLIDE_WITH_BORDER
                                                        : result;
  return result;
}

int CheckCollision(GameInfo *game_info, Brick *brick, int direction) {
  int result = 0;
  for (int i = 0; i < 4 && result == COL_STATE_NO; i++) {
    result = CheckOutOfBounds(brick, i, game_info->win_info.width,
                              game_info->win_info.height, direction);
    if (result == COL_STATE_NO) {
      result = CheckCollisionBrick(game_info->field, brick, i);
    }
  }

  return result;
}