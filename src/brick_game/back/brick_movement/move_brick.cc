#include "move_brick.h"

// доработка

void MoveBrickCords(Brick *brick, int direction) {
  if (direction == kDirRight || direction == kDirLeft) {
    brick->x += direction;
  }
  if (direction == kDirTop || direction == kDirDown) {
    brick->y += direction / 2;
  }
}

void RotateBrickCords(Brick *brick, int angle) {
  int tmp = 0;
  for (int i = 0; i < 4; i++) {
    tmp = brick->cords[i][0];
    brick->cords[i][0] = angle * brick->cords[i][1];
    brick->cords[i][1] = -angle * tmp;
  }
}

void DeleteFromField(int **field, Brick *brick) {
  for (int i = 0; i < 4; i++) {
    field[brick->y + brick->cords[i][1]][brick->x + brick->cords[i][0]] = 0;
  }
}

void MoveBrickInField(int **field, Brick *brick) {
  for (int i = 0; i < 4; i++) {
    field[brick->y + brick->cords[i][1]][brick->x + brick->cords[i][0]] =
        brick->color;
  }
}

int TryToMove(GameInfo *game_info, Brick *oldBrick, int direction, int angle) {
  int result = COL_STATE_NO;
  for (int i = 0; i < 4 && result == COL_STATE_NO; i++) {
    result = CheckOutOfBounds(oldBrick, i, game_info->win_info.width,
                              game_info->win_info.height, kDirState);
  }
  if (result == COL_STATE_NO) {
    DeleteFromField(game_info->field, oldBrick);

    if (direction != kDirState) {
      MoveBrickCords(oldBrick, direction);
    } else if (angle != 0 && direction == kDirState) {
      RotateBrickCords(oldBrick, angle);
    }

    result = CheckCollision(game_info, oldBrick, direction);
  }
  return result;
}

int MoveBrick(GameInfo *game_info, Brick *oldBrick, int direction, int angle) {
  Brick newBrick = *oldBrick;
  int result = COL_STATE_NO;
  result = TryToMove(game_info, &newBrick, direction, angle);

  if (result == COL_STATE_NO) {
    *oldBrick = newBrick;
  }
  MoveBrickInField(game_info->field, oldBrick);
  return result;
}

int ForceMoveBrick(GameInfo *game_info, Brick *oldBrick, int direction) {
  DeleteFromField(game_info->field, oldBrick);
  MoveBrickCords(oldBrick, direction);
  MoveBrickInField(game_info->field, oldBrick);
  return 0;
}
