#include "../brick_game_test.h"

class SnakeFunctionsTest : public ::testing::Test
{
};

TEST_F(SnakeFunctionsTest, case_1)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    ASSERT_EQ(snake.body.size(), 4);
    ASSERT_EQ(snake.body.front()->y, GAME_WINDOW_HEIGHT / 2);
    ASSERT_EQ(snake.body.front()->x, GAME_WINDOW_WIDTH / 2);
    ASSERT_EQ(snake.body[1]->y, GAME_WINDOW_HEIGHT / 2 - 1);
    ASSERT_EQ(snake.body[2]->y, GAME_WINDOW_HEIGHT / 2 - 2);
    ASSERT_EQ(snake.body[3]->y, GAME_WINDOW_HEIGHT / 2 - 3);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFunctionsTest, case_2)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    for (int i = 0; i < 4; i++)
    {
        snake.body[i]->y += 5;
        snake.body[i]->x += 5;
    }
    snake.Respawn();
    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(snake.body[i]->x, GAME_WINDOW_WIDTH / 2);
        ASSERT_EQ(snake.body[i]->y, GAME_WINDOW_HEIGHT / 2 - i);
    }
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFunctionsTest, case_3)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    for (int i = 0; i < GAME_WINDOW_HEIGHT; i++)
    {
        for (int j = 0; j < GAME_WINDOW_WIDTH; j++)
        {
            field[i][j] = 1;
        }
    }
    field[GAME_WINDOW_HEIGHT - 1][GAME_WINDOW_WIDTH - 1] = 0;
    int x = 0, y = 0;
    snake.RandomFreeCell(&y, &x);
    ASSERT_EQ(x, GAME_WINDOW_WIDTH - 1);
    ASSERT_EQ(y, GAME_WINDOW_HEIGHT - 1);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFunctionsTest, case_4)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    for (int i = 0; i < GAME_WINDOW_HEIGHT; i++)
    {
        for (int j = 0; j < GAME_WINDOW_WIDTH; j++)
        {
            field[i][j] = 1;
        }
    }
    field[5][5] = 0;
    int x = 0, y = 0;
    snake.RandomFreeCell(&y, &x);
    ASSERT_EQ(x, 5);
    ASSERT_EQ(y, 5);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFunctionsTest, case_5)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    for (int i = 0; i < GAME_WINDOW_HEIGHT; i++)
    {
        for (int j = 0; j < GAME_WINDOW_WIDTH; j++)
        {
            field[i][j] = 1;
        }
    }
    field[GAME_WINDOW_HEIGHT - 1][0] = 0;
    field[GAME_WINDOW_HEIGHT - 1][1] = 0;
    field[GAME_WINDOW_HEIGHT - 1][2] = 0;
    field[GAME_WINDOW_HEIGHT - 1][3] = 0;
    int x = 0, y = 0;
    snake.RandomFreeCell(&y, &x);
    ASSERT_TRUE(x == 0 || x == 1 | 2 || x == 3);
    ASSERT_EQ(y, GAME_WINDOW_HEIGHT - 1);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFunctionsTest, case_6)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    for (int i = 0; i < GAME_WINDOW_HEIGHT; i++)
    {
        for (int j = 0; j < GAME_WINDOW_WIDTH; j++)
        {
            field[i][j] = 1;
        }
    }
    field[GAME_WINDOW_HEIGHT - 1][0] = 0;
    field[GAME_WINDOW_HEIGHT - 1][1] = 0;
    field[GAME_WINDOW_HEIGHT - 1][2] = 0;
    field[GAME_WINDOW_HEIGHT - 1][3] = 0;
    field[5][3] = 0;
    field[5][3] = 0;
    field[5][3] = 0;
    int x = 0, y = 0;
    for (int i = 0; i < 100; i++)
    {
        snake.RandomFreeCell(&y, &x);
        ASSERT_EQ(snake.game_info->field[y][x], 0);
    }

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFunctionsTest, case_7)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);

    for (int i = 0; i < 6; i++)
    {
        snake.SpawnNode();
        ASSERT_EQ(snake.body[3 + i]->x, snake.body[4 + i]->x);
        ASSERT_EQ(snake.body[3 + i]->y, snake.body[4 + i]->y);
    }
    ASSERT_EQ(snake.body.size(), 10);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFunctionsTest, case_8)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    snake.SpawnApple();
    ASSERT_EQ(field[snake.game_info->next_brick.y][snake.game_info->next_brick.x], snake.game_info->next_brick.color);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFunctionsTest, case_9)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    for (int i = 0; i < 196; i++)
    {
        snake.SpawnApple();
        ASSERT_EQ(field[snake.game_info->next_brick.y][snake.game_info->next_brick.x], snake.game_info->next_brick.color);
    }
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFunctionsTest, case_10)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = snake.SnakeHandleCollision(COL_STATE_NO, snake, kMoving);
    ASSERT_EQ(state, kMoving);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFunctionsTest, case_11)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = snake.SnakeHandleCollision(snake.game_info->current_brick.color, snake, kMoving);
    ASSERT_EQ(snake.game_info->current_brick.color, 1);
    ASSERT_EQ(snake.game_info->next_brick.color, 2);
    ASSERT_EQ(state, kGameOver);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFunctionsTest, case_12)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = snake.SnakeHandleCollision(COLLIDE_WITH_BORDER, snake, kMoving);
    ASSERT_EQ(state, kGameOver);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFunctionsTest, case_13)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = snake.SnakeHandleCollision(COLLIDE_WITH_BORDER, snake, kMoving);
    ASSERT_EQ(state, kGameOver);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFunctionsTest, case_14)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = snake.SnakeHandleCollision(COLLIDE_WITH_BORDER, snake, kMoving);
    int x = snake.body[0]->x;
    int y = snake.body[0]->y;
    snake.MoveBody(kDirDown, true);
    for (int i = 0; i < snake.body.size(); i++)
    {
        ASSERT_EQ(snake.body[i]->x, x);
        ASSERT_EQ(snake.body[i]->y, y - i + 1);
    }
    ASSERT_EQ(state, kGameOver);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFunctionsTest, case_15)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = snake.SnakeHandleCollision(COLLIDE_WITH_BORDER, snake, kMoving);
    int x = snake.body[0]->x;
    int y = snake.body[0]->y;
    snake.MoveBody(kDirRight, true);
    ASSERT_EQ(snake.body[0]->x, x + 1);
    ASSERT_EQ(snake.body[0]->y, y);
    ASSERT_EQ(snake.body[1]->x, x);
    ASSERT_EQ(snake.body[1]->y, y);
    ASSERT_EQ(snake.body[2]->x, x);
    ASSERT_EQ(snake.body[2]->y, y - 1);
    ASSERT_EQ(snake.body[3]->x, x);
    ASSERT_EQ(snake.body[3]->y, y - 2);

    ASSERT_EQ(state, kGameOver);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFunctionsTest, case_16)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = snake.SnakeHandleCollision(COLLIDE_WITH_BORDER, snake, kMoving);
    int x = snake.body[0]->x;
    int y = snake.body[0]->y;
    snake.MoveBody(kDirLeft, true);
    ASSERT_EQ(snake.body[0]->x, x - 1);
    ASSERT_EQ(snake.body[0]->y, y);
    ASSERT_EQ(snake.body[1]->x, x);
    ASSERT_EQ(snake.body[1]->y, y);
    ASSERT_EQ(snake.body[2]->x, x);
    ASSERT_EQ(snake.body[2]->y, y - 1);
    ASSERT_EQ(snake.body[3]->x, x);
    ASSERT_EQ(snake.body[3]->y, y - 2);

    ASSERT_EQ(state, kGameOver);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFunctionsTest, case_17)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = snake.SnakeHandleCollision(COLLIDE_WITH_BORDER, snake, kMoving);

    int x = snake.body[0]->x;
    int y = snake.body[0]->y;
    field[y + 1][x] = 2;
    int col = snake.MoveBody(kDirDown, true);
    ASSERT_EQ(snake.body[0]->x, x);
    ASSERT_EQ(snake.body[0]->y, y+1);
    ASSERT_EQ(snake.body[1]->x, x);
    ASSERT_EQ(snake.body[1]->y, y);
    ASSERT_EQ(snake.body[2]->x, x);
    ASSERT_EQ(snake.body[2]->y, y - 1);
    ASSERT_EQ(snake.body[3]->x, x);
    ASSERT_EQ(snake.body[3]->y, y - 2);
    ASSERT_EQ(col,2);

    ASSERT_EQ(state, kGameOver);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}
