
#include "snake_functions.h"

// void setUp(WINDOW **windows, int winCount, GameInfo_t *gameInfo, int **field) {
//   srand(time(0));
//   cursesSetUp();
//   setUpBrickGameWindows(windows, winCount);
//   initGameInfo(gameInfo, field, GAME_SPEED, GMAE_ACCELERATION,3);
// }

void RandomFreeCell(int **field, int height, int width, int *y, int *x)
{

    int free_cells[height * width][2];
    int free_count = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (field[i][j] == 0)
            {
                free_cells[free_count][0] = i;
                free_cells[free_count][1] = j;
                free_count++;
            }
        }
    }

    if (free_count > 0)
    {
        int random_index = rand() % free_count;
        *y = free_cells[random_index][0];
        *x = free_cells[random_index][1];
    }
    else
    {
        *y = -1;
        *x = -1;
    }
}

int SpawnApple(GameInfo_t *gameInfo)
{
    int x = -1, y = -1;
    RandomFreeCell(gameInfo->field, gameInfo->winInfo.height, gameInfo->winInfo.width, &y, &x);
    if (x == -1 && y == -1)
    {
        return 1;
    }
    gameInfo->nextBrick.x = x;
    gameInfo->nextBrick.y = y;
    moveBrickInField(gameInfo->field, &(gameInfo->nextBrick));

    return 0;
}

void redrawBody(GameInfo_t *gameInfo, std::vector<Brick *> &body)
{
    for (auto it = body.begin(); it != body.cend(); ++it)
    {
        // deleteFromField(gameInfo->field, *it);
        moveBrickInField(gameInfo->field, *it);
    }
}

int SpawnNode(GameInfo_t *gameInfo, std::vector<Brick *> &body)
{
    Brick local_brick = Brick{*(body.back())};
    // moveBrickCords(&local_brick, -direction);

    // moveBrickCords(&local_brick, direction);
    body.push_back(new Brick{local_brick});
    // moveBrickInField(gameInfo->field, &local_brick);

    return 0;
}

int SnakeHandleCollision(GameInfo_t *gameInfo, int col, int dir)
{

    if (col == gameInfo->nextBrick.color)
    {
        col = COL_STATE_CRIT;
    }
    else if (col == COLLIDE_WITH_BORDER || col == gameInfo->currentBrick.color)
    {
        col = COL_STATE_END;
    }

    return col;
}

int MoveBody(GameInfo_t *gameInfo, std::vector<Brick *> &body, int direction, bool ignore_collision)
{
    if (body.empty())
        return COL_STATE_NO;

    Brick *head = body.front();
    Brick old_brick = *head;

    int col = moveBrick(gameInfo, head, direction, 0);

    if (col != COL_STATE_NO)
    {
        if (ignore_collision)
        {
            ForceMoveBrick(gameInfo, head, direction, 0);
        }
        else
            return col;
    }

    if (body.size() < 2)
        return col;

    for (size_t i = 1; i < body.size(); ++i)
    {
        Brick *current = body[i];
        Brick tmp_brick = *current;

        current->x = old_brick.x;
        current->y = old_brick.y;

        old_brick = tmp_brick;
        deleteFromField(gameInfo->field, &old_brick);
        moveBrickInField(gameInfo->field, current);
    }

    return col;
}

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