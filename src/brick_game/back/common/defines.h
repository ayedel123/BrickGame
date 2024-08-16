#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_BACK_COMMON_DEFINES_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_BACK_COMMON_DEFINES_H_

typedef enum { kGameWin, kInfoWin, kDebugWIn } WindowsEnum;

typedef struct WinInfo {
  int height, width;
} WinInfo;

typedef enum directions_enum {
  kDirTop = -2,
  kDirDown = 2,
  kDirRight = 1,
  kDirLeft = -1,
  kDirState = 0
} DirectionEnum;

// typedef enum {
//   KStart,
//   Pause,
//   Terminate,
//   Left,
//   Right,
//   Up,
//   Down,
//   Action
// } UserAction;

typedef enum {
  kMoveUp = 0,
  kMoveDown,
  kMoveRight,
  kMoveLeft,
  kRotateLeft,
  kRotateRight,
  kAction,
  kPause,
  kExit,
  kStartSig,
  kNosig
} Signal;

typedef enum {
  kStart = 0,
  kSpawn,
  kMoving,
  kCollide,
  kGameOver,
  kOnPause,
  kSpawnApple,
  kExitState
} GameState;

#define ESCAPE 27
#define KEY_ROTATE_LEFT 'q'
#define KEY_ROTATE_RIGHT 'e'
#define KEY_ESCAPE '0'
#define KEY_PAUSE ' '
#define KEY_START '\n'

#define COLLIDE_WITH_BORDER -1

#define COL_STATE_NO 0
#define COL_STATE_COL 1
#define COL_STATE_CRIT 2
#define COL_STATE_END 3

#define WINDOW_OFFSET 1
#define GAME_WINDOW_HEIGHT 20
#define GAME_WINDOW_WIDTH 10
#define GAME_WINDOW_STARTX 0
#define GAME_WINDOW_STARTY 0

#define COLOR_COUNT 7

//#define bool int

#endif