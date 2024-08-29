#include "../brick_game_test.h"

class TetrisFsmTEST : public ::testing::Test {};

TEST_F(TetrisFsmTEST, case_1) {
  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  TetrisSetUp(&game_info, field);
  game_info.current_brick = BRICKS_TYPES[0];
  int x = game_info.current_brick.x;
  int y = game_info.current_brick.y;
  GameState state = kMoving;
  TetrisUpdateCurrentState(&game_info, &state, kAction);
  ASSERT_EQ(game_info.current_brick.x, x);
  ASSERT_EQ(game_info.current_brick.y, y + 1);
  ASSERT_EQ(state, kMoving);
  DeleteField(game_info.field, height);
}

TEST_F(TetrisFsmTEST, case_2) {
  int **field;
  InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  GameInfo game_info;
  TetrisSetUp(&game_info, field);
  game_info.current_brick = BRICKS_TYPES[0];

  game_info.current_brick.y = GAME_WINDOW_HEIGHT - 1;
  int x = game_info.current_brick.x;
  int y = game_info.current_brick.y;
  GameState state = kMoving;
  TetrisUpdateCurrentState(&game_info, &state, kAction);
  ASSERT_EQ(game_info.current_brick.x, x);
  ASSERT_EQ(game_info.current_brick.y, y);
  ASSERT_EQ(state, kSpawn);
  DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_3) {
  int **field;
  InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  GameInfo game_info;
  TetrisSetUp(&game_info, field);
  game_info.current_brick = BRICKS_TYPES[0];
  game_info.current_brick.y = GAME_WINDOW_HEIGHT - 1;
  GameState state = kMoving;
  TetrisUpdateCurrentState(&game_info, &state, kAction);
  ASSERT_EQ(state, kSpawn);
  TetrisUpdateCurrentState(&game_info, &state, kAction);
  ASSERT_EQ(game_info.current_brick.x, GAME_WINDOW_WIDTH / 2);
  ASSERT_EQ(game_info.current_brick.y, 0);

  DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_4) {
  int **field;
  InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  GameInfo game_info;
  TetrisSetUp(&game_info, field);
  game_info.current_brick = BRICKS_TYPES[0];
  GameState state = kStart;
  TetrisUpdateCurrentState(&game_info, &state, kStartSig);
  ASSERT_EQ(state, kSpawn);
  DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_5) {
  int **field;
  InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  GameInfo game_info;
  TetrisSetUp(&game_info, field);
  game_info.current_brick = BRICKS_TYPES[0];
  GameState state = kGameOver;
  TetrisUpdateCurrentState(&game_info, &state, kStartSig);
  ASSERT_EQ(state, kStart);
  DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_6) {
  int **field;
  InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  GameInfo game_info;
  TetrisSetUp(&game_info, field);
  game_info.current_brick = BRICKS_TYPES[0];
  GameState state = kGameOver;
  TetrisUpdateCurrentState(&game_info, &state, kExit);
  ASSERT_EQ(state, kExitState);
  DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_7) {
  int **field;
  InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  GameInfo game_info;
  TetrisSetUp(&game_info, field);
  game_info.current_brick = BRICKS_TYPES[0];
  GameState state = kOnPause;
  int x = game_info.current_brick.x;
  int y = game_info.current_brick.y;
  TetrisUpdateCurrentState(&game_info, &state, kAction);
  ASSERT_EQ(x, game_info.current_brick.x);
  ASSERT_EQ(y, game_info.current_brick.y);
  ASSERT_EQ(state, kOnPause);
  DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_8) {
  int **field;
  InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  GameInfo game_info;
  TetrisSetUp(&game_info, field);
  game_info.current_brick = BRICKS_TYPES[0];
  GameState state = kMoving;
  game_info.current_brick.x = 2;
  game_info.current_brick.y = 5;
  int x = game_info.current_brick.x;
  int y = game_info.current_brick.y;
  Brick tmp_brick = game_info.current_brick;
  RotateBrickCords(&tmp_brick, 1);
  TetrisUpdateCurrentState(&game_info, &state, kRotateRight);
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(tmp_brick.cords[i][0], game_info.current_brick.cords[i][0]);
    ASSERT_EQ(tmp_brick.cords[i][1], game_info.current_brick.cords[i][1]);
  }
  ASSERT_EQ(x, game_info.current_brick.x);
  ASSERT_EQ(y, game_info.current_brick.y);
  ASSERT_EQ(state, kMoving);
  DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_9) {
  int **field;
  InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  GameInfo game_info;
  TetrisSetUp(&game_info, field);
  game_info.current_brick = BRICKS_TYPES[0];
  GameState state = kExitState;
  int x = game_info.current_brick.x;
  int y = game_info.current_brick.y;
  TetrisUpdateCurrentState(&game_info, &state, kAction);
  ASSERT_EQ(x, game_info.current_brick.x);
  ASSERT_EQ(y, game_info.current_brick.y);
  ASSERT_EQ(state, kExitState);
  DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_10) {
  int **field;
  InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  GameInfo game_info;
  TetrisSetUp(&game_info, field);
  game_info.current_brick = BRICKS_TYPES[0];
  GameState state = kOnPause;
  int x = game_info.current_brick.x;
  int y = game_info.current_brick.y;
  TetrisUpdateCurrentState(&game_info, &state, kExit);
  ASSERT_EQ(x, game_info.current_brick.x);
  ASSERT_EQ(y, game_info.current_brick.y);
  ASSERT_EQ(state, kExitState);
  DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_11) {
  int **field;
  InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  GameInfo game_info;
  TetrisSetUp(&game_info, field);
  game_info.current_brick = BRICKS_TYPES[0];
  GameState state = kMoving;
  int x = game_info.current_brick.x;
  int y = game_info.current_brick.y;
  TetrisUpdateCurrentState(&game_info, &state, kRotateLeft);
  ASSERT_EQ(x, game_info.current_brick.x);
  ASSERT_EQ(y, game_info.current_brick.y);
  ASSERT_EQ(state, kMoving);
  DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_12) {
  int **field;
  InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  GameInfo game_info;
  TetrisSetUp(&game_info, field);
  game_info.current_brick = BRICKS_TYPES[0];
  GameState state = kOnPause;
  TetrisUpdateCurrentState(&game_info, &state, kPause);
  ASSERT_EQ(state, kMoving);
  DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_13) {
  int **field;
  InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  GameInfo game_info;
  TetrisSetUp(&game_info, field);
  game_info.current_brick = BRICKS_TYPES[0];
  GameState state = kMoving;
  TetrisUpdateCurrentState(&game_info, &state, kPause);
  ASSERT_EQ(state, kOnPause);
  DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}

TEST_F(TetrisFsmTEST, case_14) {
  int **field;
  InitField(&field, GAME_WINDOW_HEIGHT, GAME_WINDOW_WIDTH);
  GameInfo game_info;
  TetrisSetUp(&game_info, field);
  game_info.current_brick = BRICKS_TYPES[0];
  GameState state = kMoving;
  TetrisUpdateCurrentState(&game_info, &state, kExit);
  ASSERT_EQ(state, kExitState);
  DeleteField(game_info.field, GAME_WINDOW_HEIGHT);
}