#include "get_move_data.h"

void GetMoveData(int signal, int *direction, int *angle) {
  switch (signal) {
    case kMoveUp:
      *direction = kDirTop;
      break;
    case kMoveDown:
      *direction = kDirDown;
      break;
    case kMoveLeft:
      *direction = kDirLeft;
      break;
    case kMoveRight:
      *direction = kDirRight;
      break;
    case kRotateLeft:
      *angle = -1;
      break;
    case kRotateRight:
      *angle = 1;
      break;
    default:
      break;
  };
}