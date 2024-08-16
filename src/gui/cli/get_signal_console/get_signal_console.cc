#include "get_signal_console.h"

Signal GetSignalConsole(int user_input) {
  Signal signal = kNosig;

  switch (user_input) {
    case KEY_UP:
      signal = kMoveUp;
      break;
    case KEY_DOWN:
      signal = kMoveDown;
      break;
    case KEY_LEFT:
      signal = kMoveLeft;
      break;
    case KEY_RIGHT:
      signal = kMoveRight;
      break;
    case KEY_ROTATE_LEFT:
      signal = kRotateLeft;
      break;
    case KEY_ROTATE_RIGHT:
      signal = kRotateRight;
      break;
    case KEY_PAUSE:
      signal = kPause;
      break;
    case ERR:
      signal = kNosig;
      break;
    case KEY_START:
      signal = kStartSig;
      break;
    case KEY_ESCAPE:
      signal = kExit;
      break;
    default:
      signal = kNosig;
      break;
  }

  return signal;
}