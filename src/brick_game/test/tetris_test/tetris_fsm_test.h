#ifndef CPP3_BRICKGAME_V2_0_1_SRC_TEST_BACK_TEST_TETRIS_TETRIS_FSM_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_TEST_BACK_TEST_TETRIS_TETRIS_FSM_H_

#include "tetris_test.h"

class TetrisFsmTEST : public ::testing::Test
{
};

TEST_F(TetrisFsmTEST, case_1)
{
    int width = 10;
    int height = 10;
    int **field;
    InitField(&field, width, height);
    GameInfo game_info;
    TetrisSetUp(&game_info, field);
    int x = game_info.current_brick.x;
    int y = game_info.current_brick.y;
    GameState state = kMoving;
    TetrisUpdateCurrentState(&game_info, &state, kMoveDown);
    ASSERT_EQ(game_info.current_brick.x, x);
    ASSERT_EQ(game_info.current_brick.y, y + 1);
    ASSERT_EQ(state, kMoving);
    DeleteField(game_info.field, height);
}

TEST_F(TetrisFsmTEST, case_2)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    TetrisSetUp(&game_info, field);
    game_info.current_brick.y = GAME_WINDOW_HEIGHT - 2;
    int x = game_info.current_brick.x;
    int y = game_info.current_brick.y;
    GameState state = kMoving;
    TetrisUpdateCurrentState(&game_info, &state, kMoveDown);
    ASSERT_EQ(game_info.current_brick.x, x);
    ASSERT_EQ(game_info.current_brick.y, y);
    ASSERT_EQ(state, kSpawn);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_3)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    TetrisSetUp(&game_info, field);
    game_info.current_brick.y = GAME_WINDOW_HEIGHT - 2;
    int x = game_info.current_brick.x;
    int y = game_info.current_brick.y;
    GameState state = kMoving;
    TetrisUpdateCurrentState(&game_info, &state, kMoveDown);
    TetrisUpdateCurrentState(&game_info, &state, kMoveDown);
    ASSERT_EQ(game_info.current_brick.x, x);
    ASSERT_EQ(game_info.current_brick.y, 0);
    ASSERT_EQ(state, kMoving);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_4)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    TetrisSetUp(&game_info, field);
    GameState state = kStart;
    TetrisUpdateCurrentState(&game_info, &state, kStartSig);
    ASSERT_EQ(state, kSpawn);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_5)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    TetrisSetUp(&game_info, field);
    GameState state = kGameOver;
    TetrisUpdateCurrentState(&game_info, &state, kStartSig);
    ASSERT_EQ(state, kStart);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_6)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    TetrisSetUp(&game_info, field);
    GameState state = kGameOver;
    TetrisUpdateCurrentState(&game_info, &state, kExit);
    ASSERT_EQ(state, kExit);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_7)
{
    int **field;
    InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
    GameInfo game_info;
    TetrisSetUp(&game_info, field);
    GameState state = kOnPause;
    int x = game_info.current_brick.x;
    int y = game_info.current_brick.y;
    TetrisUpdateCurrentState(&game_info, &state, kMoveDown);
    ASSERT_EQ(x,game_info.current_brick.x);
    ASSERT_EQ(y,game_info.current_brick.y);
    ASSERT_EQ(state, kOnPause);
    DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

#endif