
#include "snake.h"

void SnakeSetUp(GameInfo *game_info, int **field)
{
  InitGameInfo(game_info, field, SNAKE_GAME_SPEED, SNAKE_GAME_ACCELERATION, BRICK_TYPES_COUNT);
}

int SnakeGameLoop(GameInfo *game_info, WINDOW **windows)
{

  long long startTime = GetTimeInMS();
  long long endTime = 0;
  int is_end = 0;
  int keyVal = 0;
  int input = 0;
  GameState state = kStart;
  std::vector<Brick *> body = std::vector<Brick *>();
  Signal last_move = kMoveDown;
  while (keyVal != 404 && state != kExitState)
  {
    input = UserInput();
    Signal signal = GetSignal(input);
    if (signal == kMoveDown || signal == kMoveUp || signal == kMoveLeft || signal == kMoveRight)
    {
      last_move = signal;
    }

    *game_info =
        UpdateCurrentState(*game_info, body, &state, signal, windows);

    endTime = GetTimeInMS();
    if (state == kMoving &&
        endTime - startTime >=
            game_info->speed - game_info->level * game_info->acceleration)
    {
      startTime = GetTimeInMS();
      *game_info = UpdateCurrentState(*game_info, body, &state, last_move, windows);
    }
  }
  body.clear();

  return 0;
}
