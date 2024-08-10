
#include "snake_functions.h"

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

int SpawnApple(GameInfo *game_info)
{
    int x = -1, y = -1;
    RandomFreeCell(game_info->field, game_info->win_info.height, game_info->win_info.width, &y, &x);
    if (x == -1 && y == -1)
    {
        return 1;
    }
    game_info->next_brick.x = x;
    game_info->next_brick.y = y;
    moveBrickInField(game_info->field, &(game_info->next_brick));

    return 0;
}

void redrawBody(GameInfo *game_info, std::vector<Brick *> &body)
{
    for (auto it = body.begin(); it != body.cend(); ++it)
    {
        moveBrickInField(game_info->field, *it);
    }
}

int SpawnNode(GameInfo *game_info, std::vector<Brick *> &body)
{
    Brick local_brick = Brick{*(body.back())};

    body.push_back(new Brick{local_brick});

    return 0;
}

int SnakeHandleCollision(GameInfo *game_info, int col, int dir)
{

    if (col == game_info->next_brick.color)
    {
        col = COL_STATE_CRIT;
    }
    else if (col == COLLIDE_WITH_BORDER || col == game_info->current_brick.color)
    {
        col = COL_STATE_END;
    }

    return col;
}

int MoveBody(GameInfo *game_info, std::vector<Brick *> &body, int direction, bool ignore_collision)
{
    if (body.empty())
        return COL_STATE_NO;

    Brick *head = body.front();
    Brick old_brick = *head;

    int col = moveBrick(game_info, head, direction, 0);

    if (col != COL_STATE_NO)
    {
        if (ignore_collision)
        {
            ForceMoveBrick(game_info, head, direction, 0);
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
        deleteFromField(game_info->field, &old_brick);
        moveBrickInField(game_info->field, current);
    }

    return col;
}

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