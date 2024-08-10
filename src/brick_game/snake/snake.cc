
#include "snake.h"

// void setUp(WINDOW **windows, int winCount, GameInfo_t *gameInfo, int **field) {
//   srand(time(0));
//   cursesSetUp();
//   setUpBrickGameWindows(windows, winCount);
//   initGameInfo(gameInfo, field, GAME_SPEED, GMAE_ACCELERATION,3);
// }

void SnakeSetUp(GameInfo_t *gameInfo, int **field)
{
  initGameInfo(gameInfo, field, SNAKE_GAME_SPEED, SNAKE_GAME_ACCELERATION, BRICK_TYPES_COUNT);
}

int SnakeGameLoop(GameInfo_t *gameInfo, WINDOW **windows)
{

  long long startTime = getTimeInMS();
  long long endTime = 0;
  int isEnd = 0;
  int keyVal = 0;
  int input = 0;
  game_states state = START;
  std::vector<Brick *> body = std::vector<Brick *>();
  signals last_move = MOVE_DOWN;
  while (keyVal != 404 && state != EXIT_STATE)
  {
    input = userInput();
    signals signal = getSignal(input);
    if (signal == MOVE_DOWN || signal == MOVE_UP || signal == MOVE_LEFT || signal == MOVE_RIGHT)
    {
      last_move = signal;
    }

    *gameInfo =
        updateCurrentState(*gameInfo, body, &state, signal, windows);

    endTime = getTimeInMS();
    if (state == MOVING &&
        endTime - startTime >=
            gameInfo->speed - gameInfo->level * gameInfo->acceleration)
    {
      startTime = getTimeInMS();
      *gameInfo = updateCurrentState(*gameInfo, body, &state, last_move, windows);
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

// int SpawnApple(GameInfo_t *gameInfo)
// {
//   int x = -1, y = -1;
//   RandomFreeCell(gameInfo->field, gameInfo->winInfo.height, gameInfo->winInfo.width, &y, &x);
//   if (x == -1 && y == -1)
//   {
//     return 1;
//   }
//   gameInfo->nextBrick.x = x;
//   gameInfo->nextBrick.y = y;
//   moveBrickInField(gameInfo->field, &(gameInfo->nextBrick));

//   return 0;
// }

// int SnakeHandleCollision(GameInfo_t *gameInfo, int col, int dir)
// {

//   if (col != COLLIDE_WITH_BORDER && col != COL_STATE_NO)
//   {
//     ForceMoveBrick(gameInfo, &gameInfo->currentBrick, dir, 0);
//     return COL_STATE_CRIT;
//   }

//   return col;
// }

// int main() {
//   WINDOW *windows[3];
//   GameInfo_t gameInfo;
//   int **field = NULL;
//   initField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
//   clearField(field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
//   setUp(windows, 2, &gameInfo, field);
//   gameLoop(&gameInfo, windows);
//   endwin();
//   deleteField(field, GAME_WINDOW_HEIGHT);

//   return 0;
// }