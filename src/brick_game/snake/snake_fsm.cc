#include "snake_fsm.h"

void SpawnAppleHandler(s21::Snake &snake, GameState *state)
{
  snake.AddPoints(1);
  snake.SpawnApple();
  *state = kMoving;
}

void GetMoveData(int signal, int *direction, int *angle)
{
  switch (signal)
  {
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
  case kNosig:
    break;
  };
}

void MovingHandler(s21::Snake &snake, GameState *state,
                   Signal signal)
{
  if (signal == kExit)
  {
    *state = kExitState;
  }
  else if (signal == kPause)
  {
    *state = kOnPause;
  }
  else
  {
    int direction = kDirState;
    int angle = 0;
    GetMoveData(signal, &direction, &angle);
    int col = 0;
    if (signal != kNosig && direction != -snake.last_direction)
    {
      col = snake.MoveBody(direction, false);
      snake.last_direction = direction;
      snake.last_signal = signal;
    }
    snake.game_info->current_brick = **snake.body.begin();
    *state = snake.SnakeHandleCollision(col, snake, *state);
  }

}

void StartHandler(s21::Snake &snake, GameState *state)
{
  ClearField(snake.game_info->field, snake.game_info->win_info.height,
             snake.game_info->win_info.width);
  snake.Respawn();
  snake.last_signal = kMoveDown;
  MoveBrickInField(snake.game_info->field, &snake.game_info->current_brick);
  *state = kSpawn;
}

void GameOverHandler(s21::Snake &snake, GameState *state,
                     Signal signal)
{
  snake.Kill();
  if (signal != kNosig)
  {
    if (signal != kExit)
    {
      *state = kStart;
      snake.last_signal = kStartSig;
    }
    else
      *state = kExitState;
  }
}

void ExitHandler(s21::Snake &snake, GameState *state)
{
  if (!snake.body.empty())
  {
    snake.Kill();
  }
  *state = kExitState;
}

void PauseHandler(GameState *state, Signal signal)
{
  if (signal == kPause)
  {
    *state = kMoving;
  }
  else if (signal == kExit)
  {
    *state = kExitState;
  }
}
