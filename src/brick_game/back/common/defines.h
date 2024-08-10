#ifndef __DEFINES__
#define __DEFINES__

typedef enum { GAME_WIN, INFO_WIN, DEBUG_WIN } WINDOWS_ENUM;

typedef struct WinInfo {
  int height, width;
} WinInfo;

typedef enum directions_enum {
  DIR_TOP = -2,
  DIR_DOWN = 2,
  DIR_RIGHT = 1,
  DIR_LEFT = -1,
  DIR_STATE = 0
} DIRECTIONS_ENUM;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef enum {
  MOVE_UP = 0,
  MOVE_DOWN,
  MOVE_RIGHT,
  MOVE_LEFT,
  ROTATE_LEFT,
  ROTATE_RIGHT,
  PAUSE,
  EXIT,
  START_SIG,
  NOSIG
} signals;

typedef enum
{
  START = 0,
  SPAWN,
  MOVING,
  COLLIDE,
  GAMEOVER,
  ONPAUSE,
  SPAWN_APPLE,
  EXIT_STATE
} game_states;

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