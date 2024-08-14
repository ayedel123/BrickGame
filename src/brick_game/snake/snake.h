#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE_H_

#include "../../gui/cli/cli.h"
#include "../back/back.h"
extern "C"
{
#include <ctype.h>
#include <ncurses.h>
#include <stdlib.h>
}
#include "iostream"
#include <vector>
#include <stdexcept>
namespace s21
{

    class Snake
    {
    public:
        GameInfo *game_info;
        std::vector<Brick *> body;
        int last_direction;
        Signal last_signal;
        int game_speed = 300;
        int game_acceleration = 20;

        Snake() = default;
        ~Snake(){
            Clear();
        }
        Snake(GameInfo *game_info, int **field) : Snake()
        {

            this->game_info = game_info;
            InitGameInfo(this->game_info, field, game_speed, game_acceleration, BRICK_TYPES_COUNT, "snake_record");

            this->game_info->next_brick.color = 2;
            last_signal = kMoveDown;
            last_direction = kDirDown;
            Respawn();
        }

        void Respawn()
        {
            game_info->current_brick.x = game_info->win_info.width / 2;
            game_info->current_brick.y = game_info->win_info.height / 2;
            game_info->current_brick.color = 1;
            game_info->next_brick.color = 2;
            Clear();
            for (int i = 0; i < 4; i++)
            {
                body.insert(body.cend(), new Brick{game_info->current_brick});
                body[i]->y -= i;
                MoveBrickInField(game_info->field, body[i]);
            }
        }

        void Clear()
        {
            for (auto it = body.begin(); it != body.end(); ++it)
            {
                delete (*it);
            }
            body.clear();
        }

        void Kill()
        {
            ClearField(game_info->field, game_info->win_info.height,
                       game_info->win_info.width);
            Clear();
            last_direction = kMoveDown;
            game_info->points = 0;
            game_info->level = 0;
        }

        void RandomFreeCell(int *y, int *x)
        {

            int free_cells[game_info->win_info.height * game_info->win_info.width][2];
            int free_count = 0;

            for (int i = 0; i < game_info->win_info.height; i++)
            {
                for (int j = 0; j < game_info->win_info.width; j++)
                {
                    if (game_info->field[i][j] == 0)
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

        int SpawnApple()
        {
            int x = -1, y = -1;
            RandomFreeCell(&y, &x);
            if (x == -1 && y == -1)
            {
                return 1;
            }
            game_info->next_brick.x = x;
            game_info->next_brick.y = y;
            MoveBrickInField(game_info->field, &(game_info->next_brick));

            return 0;
        }

        void RedrawBody()
        {
            for (auto it = body.begin(); it != body.cend(); ++it)
            {
                MoveBrickInField(game_info->field, *it);
            }
        }

        int SpawnNode()
        {
            Brick local_brick = Brick{*(body.back())};

            body.push_back(new Brick{local_brick});

            return 0;
        }

        GameState SnakeHandleCollision(int col, Snake &snake, GameState state)
        {
            if (col == game_info->next_brick.color)
            {
                snake.SpawnNode();
                snake.MoveBody(snake.last_direction, true);

                state = kSpawnApple;
            }
            else if (col == COLLIDE_WITH_BORDER || col == game_info->current_brick.color)
            {
                state = kGameOver;
            }

                

            return state;
        }

        int MoveBody(int direction, bool ignore_collision)
        {
            if (body.empty())
                return COL_STATE_NO;

            Brick *head = body.front();
            Brick old_brick = *head;

            int col = MoveBrick(game_info, head, direction, 0);

            if (col == head->color)
            {
                Brick check_brick = *head;
                MoveBrickCords(&check_brick, direction);
                if (check_brick.x == body.back()->x && check_brick.y == body.back()->y)
                {
                    ForceMoveBrick(game_info, head, direction);
                    col = COL_STATE_NO;
                }
            }

            if (col != COL_STATE_NO && ignore_collision)
            {
                ForceMoveBrick(game_info, head, direction);
            }

            if ((col == COL_STATE_NO || ignore_collision) && body.size() >= 2)
            {

                MoveBodyCords(old_brick);
            }
            MoveBrickInField(game_info->field, body.front());
            return col;
        }

        int AddPoints(int apple)
        {
            int points = apple;

            if (game_info->points < 200)
                game_info->points += points;
            if (game_info->points > game_info->high_score)
            {
                game_info->high_score = game_info->points;
                WriteRecord("snake_record", game_info->high_score);
            }
            if (game_info->points >= 5 * (game_info->level) && game_info->level < 10)
            {
                game_info->level = game_info->points / 5 + 1;
            }
            return (points < 200);
        }

    private:
        void MoveBodyCords(Brick &old_brick)
        {
            for (size_t i = 1; i < body.size(); ++i)
            {
                Brick *current = body[i];
                Brick tmp_brick = *current;

                current->x = old_brick.x;
                current->y = old_brick.y;

                old_brick = tmp_brick;
                DeleteFromField(game_info->field, &old_brick);
                MoveBrickInField(game_info->field, current);
            }
        }
    };

}

#endif