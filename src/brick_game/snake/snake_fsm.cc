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

  // DrawField(windows[kGameWin], snake.game_info);

  // printTetrisStats(windows[kInfoWin], snake.game_info, (*state == kOnPause) ? 0 : 1);
}

void StartHandler(s21::Snake &snake, GameState *state)
{
  ClearField(snake.game_info->field, snake.game_info->win_info.height,
             snake.game_info->win_info.width);
  snake.Respawn();
  moveBrickInField(snake.game_info->field, &snake.game_info->current_brick);
  *state = kSpawnApple;
}

void GameOverHandler(s21::Snake &snake, GameState *state,
                     Signal signal)
{
  snake.Kill();
  // GameOverMessage(gameWin, snake.game_info->win_info.width);
  if (signal != kNosig)
  {
    if (signal != kExit)
    {
      *state = kStart;
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
  *state = static_cast<GameState>(kExit);
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

Signal GetSignal(int user_input)
{
  Signal rc = kNosig;

  switch (user_input)
  {
  case KEY_UP:
    rc = kMoveUp;
    break;
  case KEY_DOWN:
    rc = kMoveDown;
    break;
  case KEY_LEFT:
    rc = kMoveLeft;
    break;
  case KEY_RIGHT:
    rc = kMoveRight;
    break;
  case KEY_ROTATE_LEFT:
    rc = kRotateLeft;
    break;
  case KEY_ROTATE_RIGHT:
    rc = kRotateRight;
    break;
  case KEY_PAUSE:
    rc = kPause;
    break;
  case ERR:
    rc = kNosig;
    break;
  case KEY_START:
    rc = kStartSig;
    break;
  case KEY_ESCAPE:
    rc = kExit;
    break;
  default:
    rc = kNosig;
    break;
  }

  return rc;
}
