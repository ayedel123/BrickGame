#include "../brick_game_test.h"
class SnakeFSMTest : public ::testing::Test
{
};

TEST_F(SnakeFSMTest, case_1)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kStart;
    SnakeUpdateCurrentState(snake, &state, kNosig);
    ASSERT_EQ(state, kSpawn);
    ASSERT_EQ(snake.last_signal, kMoveDown);
    ASSERT_EQ(snake.body.size(), 4);
    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(snake.body[i]->x, GAME_WINDOW_WIDTH / 2);
        ASSERT_EQ(snake.body[i]->y, GAME_WINDOW_HEIGHT / 2 - i);
        ASSERT_EQ(snake.game_info->field[GAME_WINDOW_HEIGHT / 2 - i][GAME_WINDOW_WIDTH / 2], snake.body.front()->color);
    }

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_2)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kGameOver;
    SnakeUpdateCurrentState(snake, &state, kNosig);
    ASSERT_EQ(state, kGameOver);
    ASSERT_EQ(snake.body.empty(), true);
    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(snake.game_info->field[GAME_WINDOW_HEIGHT / 2 - i][GAME_WINDOW_WIDTH / 2], 0);
    }

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_3)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kGameOver;
    SnakeUpdateCurrentState(snake, &state, kExit);
    ASSERT_EQ(state, kExitState);
    ASSERT_EQ(snake.body.empty(), true);
    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(snake.game_info->field[GAME_WINDOW_HEIGHT / 2 - i][GAME_WINDOW_WIDTH / 2], 0);
    }

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_4)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kGameOver;
    SnakeUpdateCurrentState(snake, &state, kStartSig);
    ASSERT_EQ(snake.last_signal, kStartSig);
    ASSERT_EQ(state, kStart);
    ASSERT_EQ(snake.body.empty(), true);
    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(snake.game_info->field[GAME_WINDOW_HEIGHT / 2 - i][GAME_WINDOW_WIDTH / 2], 0);
    }

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_5)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kSpawn;
    int x = snake.game_info->next_brick.x;
    int y = snake.game_info->next_brick.y;
    int points = snake.game_info->points;
    SnakeUpdateCurrentState(snake, &state, kNosig);
    ASSERT_EQ(state, kMoving);
    ASSERT_NE(x, snake.game_info->next_brick.x);
    ASSERT_NE(y, snake.game_info->next_brick.y);
    ASSERT_EQ(snake.game_info->field[snake.game_info->next_brick.y][snake.game_info->next_brick.x], snake.game_info->next_brick.color);
    ASSERT_EQ(points + 1, snake.game_info->points);

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_6)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kMoving;
    SnakeUpdateCurrentState(snake, &state, kExit);
    ASSERT_EQ(state, kExitState);

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_7)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kMoving;
    SnakeUpdateCurrentState(snake, &state, kPause);
    ASSERT_EQ(state, kOnPause);

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_8)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kMoving;
    SnakeUpdateCurrentState(snake, &state, kMoveDown);
    ASSERT_EQ(state, kMoving);
    ASSERT_EQ(snake.body.size(), 4);
    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(snake.body[i]->x, GAME_WINDOW_WIDTH / 2);
        ASSERT_EQ(snake.body[i]->y, GAME_WINDOW_HEIGHT / 2 + 1 - i);
    }

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_9)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kMoving;
    SnakeUpdateCurrentState(snake, &state, kMoveUp);
    ASSERT_EQ(state, kMoving);
    ASSERT_EQ(snake.body.size(), 4);
    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(snake.body[i]->x, GAME_WINDOW_WIDTH / 2);
        ASSERT_EQ(snake.body[i]->y, GAME_WINDOW_HEIGHT / 2 - i);
    }

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_10)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kMoving;
    SnakeUpdateCurrentState(snake, &state, kMoveRight);
    ASSERT_EQ(state, kMoving);
    ASSERT_EQ(snake.body.size(), 4);
    ASSERT_EQ(snake.body[0]->x, GAME_WINDOW_WIDTH / 2 + 1);
    ASSERT_EQ(snake.body[0]->y, GAME_WINDOW_HEIGHT / 2);
    for (int i = 1; i < 4; i++)
    {
        ASSERT_EQ(snake.body[i]->x, GAME_WINDOW_WIDTH / 2);
        ASSERT_EQ(snake.body[i]->y, GAME_WINDOW_HEIGHT / 2 - i + 1);
    }

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_11)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kMoving;
    SnakeUpdateCurrentState(snake, &state, kMoveLeft);
    ASSERT_EQ(state, kMoving);
    ASSERT_EQ(snake.body.size(), 4);
    ASSERT_EQ(snake.body[0]->x, GAME_WINDOW_WIDTH / 2 - 1);
    ASSERT_EQ(snake.body[0]->y, GAME_WINDOW_HEIGHT / 2);
    for (int i = 1; i < 4; i++)
    {
        ASSERT_EQ(snake.body[i]->x, GAME_WINDOW_WIDTH / 2);
        ASSERT_EQ(snake.body[i]->y, GAME_WINDOW_HEIGHT / 2 - i + 1);
    }

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_12)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kMoving;
    for (int i = 0; i < 4; i++)
    {
        snake.body[i]->y = GAME_WINDOW_HEIGHT - 1 - i;
    }
    SnakeUpdateCurrentState(snake, &state, kMoveDown);
    ASSERT_EQ(state, kGameOver);
    ASSERT_EQ(snake.body.size(), 4);

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_13)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kMoving;
    field[GAME_WINDOW_HEIGHT / 2 + 1][GAME_WINDOW_WIDTH / 2] = snake.game_info->next_brick.color;
    SnakeUpdateCurrentState(snake, &state, kMoveDown);
    ASSERT_EQ(state, kSpawn);
    for (int i = 0; i < 5; i++)
    {
        ASSERT_EQ(snake.body[i]->x, GAME_WINDOW_WIDTH / 2);
        ASSERT_EQ(snake.body[i]->y, GAME_WINDOW_HEIGHT / 2 - i + 1);
        ASSERT_EQ(snake.game_info->field[GAME_WINDOW_HEIGHT / 2 - i + 1][GAME_WINDOW_WIDTH / 2], snake.body.front()->color);
    }
    ASSERT_EQ(snake.body.size(), 5);

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_14)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kMoving;
    snake.body[2]->x = GAME_WINDOW_WIDTH / 2 - 1;
    snake.body[2]->y = GAME_WINDOW_HEIGHT / 2 - 1;
    snake.body[3]->x = GAME_WINDOW_WIDTH / 2 - 1;
    snake.body[3]->y = GAME_WINDOW_HEIGHT / 2;
    SnakeUpdateCurrentState(snake, &state, kMoveLeft);
    ASSERT_EQ(state, kMoving);

    ASSERT_EQ(snake.body[0]->x, GAME_WINDOW_WIDTH / 2 - 1);
    ASSERT_EQ(snake.body[0]->y, GAME_WINDOW_HEIGHT / 2);
    ASSERT_EQ(snake.game_info->field[snake.body[0]->y][snake.body[0]->x], snake.body.front()->color);

    ASSERT_EQ(snake.body[1]->x, GAME_WINDOW_WIDTH / 2);
    ASSERT_EQ(snake.body[1]->y, GAME_WINDOW_HEIGHT / 2);
    ASSERT_EQ(snake.game_info->field[snake.body[1]->y][snake.body[1]->x], snake.body.front()->color);

    ASSERT_EQ(snake.body[2]->x, GAME_WINDOW_WIDTH / 2);
    ASSERT_EQ(snake.body[2]->y, GAME_WINDOW_HEIGHT / 2 - 1);
    ASSERT_EQ(snake.game_info->field[snake.body[2]->y][snake.body[2]->x], snake.body.front()->color);

    ASSERT_EQ(snake.body[3]->x, GAME_WINDOW_WIDTH / 2 - 1);
    ASSERT_EQ(snake.body[3]->y, GAME_WINDOW_HEIGHT / 2 - 1);
    ASSERT_EQ(snake.game_info->field[snake.body[3]->y][snake.body[3]->x], snake.body.front()->color);

    ASSERT_EQ(snake.body.size(), 4);

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_15)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kMoving;
    SnakeUpdateCurrentState(snake, &state, kPause);
    ASSERT_EQ(state, kOnPause);
    for (int i = 0; i < 4; i++)
    {
        ASSERT_EQ(snake.body[i]->x, GAME_WINDOW_WIDTH / 2);
        ASSERT_EQ(snake.body[i]->y, GAME_WINDOW_HEIGHT / 2 - i);
        ASSERT_EQ(snake.game_info->field[GAME_WINDOW_HEIGHT / 2 - i][GAME_WINDOW_WIDTH / 2], snake.body.front()->color);
    }

    ASSERT_EQ(snake.body.size(), 4);

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_16)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kMoving;
    SnakeUpdateCurrentState(snake, &state, kPause);
    ASSERT_EQ(state, kOnPause);
    SnakeUpdateCurrentState(snake, &state, kPause);
    ASSERT_EQ(state, kMoving);
    SnakeUpdateCurrentState(snake, &state, kPause);
    ASSERT_EQ(state, kOnPause);
    SnakeUpdateCurrentState(snake, &state, kExit);
    ASSERT_EQ(state, kExitState);
    ASSERT_EQ(snake.body.size(), 4);

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_17)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kExitState;
    SnakeUpdateCurrentState(snake, &state, kExit);
    ASSERT_EQ(snake.body.size(), 0);
    ASSERT_EQ(state, kExitState);

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(SnakeFSMTest, case_18)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    s21::Snake snake = s21::Snake(&game_info, field);
    GameState state = kMoving;
    field[GAME_WINDOW_HEIGHT / 2 + 1][GAME_WINDOW_WIDTH / 2] = 1;
    SnakeUpdateCurrentState(snake, &state, kMoveDown);
    ASSERT_EQ(state, kGameOver);

    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}