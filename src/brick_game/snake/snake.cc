
#include "snake.h"

// void setUp(WINDOW **windows, int winCount, GameInfo *game_info, int **field) {
//   srand(time(0));
//   cursesSetUp();
//   setUpBrickGameWindows(windows, winCount);
//   InitGameInfo(game_info, field, GAME_SPEED, GMAE_ACCELERATION,3);
// }

void SnakeSetUp(GameInfo *game_info, int **field)
{
  InitGameInfo(game_info, field, SNAKE_GAME_SPEED, SNAKE_GAME_ACCELERATION, BRICK_TYPES_COUNT);
}

int SnakeGameLoop(GameInfo *game_info, WINDOW **windows)
{

  long long startTime = getTimeInMS();
  long long endTime = 0;
  int isEnd = 0;
  int keyVal = 0;
  int input = 0;
  GameState state = kStart;
  std::vector<Brick *> body = std::vector<Brick *>();
  Signal last_move = kMoveDown;
  while (keyVal != 404 && state != kExitState)
  {
    input = userInput();
    Signal signal = getSignal(input);
    if (signal == kMoveDown || signal == kMoveUp || signal == kMoveLeft || signal == kMoveRight)
    {
      last_move = signal;
    }

    *game_info =
        updateCurrentState(*game_info, body, &state, signal, windows);

    endTime = getTimeInMS();
    if (state == kMoving &&
        endTime - startTime >=
            game_info->speed - game_info->level * game_info->acceleration)
    {
      startTime = getTimeInMS();
      *game_info = updateCurrentState(*game_info, body, &state, last_move, windows);
    }
  }
  body.clear();

  return 0;
}

// void RandomFreeCell(int **field, int height, int width, int *y, int *x)
// {

//   int free_cells[height * width][2];
//   int free_count = 0;

//   for (int i = 0; i < height; i++)
//   {
//     for (int j = 0; j < width; j++)
//     {
//       if (field[i][j] == 0)
//       {
//         free_cells[free_count][0] = i;
//         free_cells[free_count][1] = j;
//         free_count++;
//       }
//     }
//   }

//   if (free_count > 0)
//   {
//     int random_index = rand() % free_count;
//     *y = free_cells[random_index][0];
//     *x = free_cells[random_index][1];
//   }
//   else
//   {
//     *y = -1;
//     *x = -1;
//   }
// }

// int SpawnApple(GameInfo *game_info)
// {
//   int x = -1, y = -1;
//   RandomFreeCell(game_info->field, game_info->win_info.height, game_info->win_info.width, &y, &x);
//   if (x == -1 && y == -1)
//   {
//     return 1;
//   }
//   game_info->next_Brick.x = x;
//   game_info->next_Brick.y = y;
//   moveBrickInField(game_info->field, &(game_info->next_Brick));

//   return 0;
// }

// int SnakeHandleCollision(GameInfo *game_info, int col, int dir)
// {

//   if (col != COLLIDE_WITH_BORDER && col != COL_STATE_NO)
//   {
//     ForceMoveBrick(game_info, &game_info->current_brick, dir, 0);
//     return COL_STATE_CRIT;
//   }

//   return col;
// }

// int main() {
//   WINDOW *windows[3];
//   GameInfo game_info;
//   int **field = NULL;
//   InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
//   ClearField(field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
//   setUp(windows, 2, &game_info, field);
//   gameLoop(&game_info, windows);
//   endwin();
//   DeleteField(field, GAME_WINDOW_HEIGHT);

//   return 0;
// }