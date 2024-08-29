#include "../brick_game_test.h"

class MoveBrickCase : public ::testing::Test {};

TEST_F(MoveBrickCase, case_1) {
  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, height, width);
  GameInfo game_info;
  BaseInitGameInfo(&game_info);
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  Brick brick = BRICKS_TYPES[0];
  game_info.current_brick = brick;
  BornBrick(&brick, 1, 0, 0, 7);

  int status = MoveBrick(&game_info, &brick, kDirRight, 0);

  ASSERT_EQ(status, COL_STATE_NO);
  ASSERT_EQ(brick.x, 2);
  ASSERT_EQ(brick.y, 0);
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(field[brick.cords[i][1] + brick.y][brick.cords[i][0] + brick.x],
              brick.color);
  }
  DeleteField(field, height);
}

TEST_F(MoveBrickCase, case_2) {
  int width = 5;
  int height = 5;
  int **field;
  InitField(&field, height, width);
  GameInfo game_info;
  BaseInitGameInfo(&game_info);
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  Brick brick = BRICKS_TYPES[0];
  game_info.current_brick = brick;

  BornBrick(&brick, 1, 0, 0, 7);
  Brick brick2 = brick;
  int status = MoveBrick(&game_info, &brick, kDirRight, 0);
  ASSERT_EQ(status, COLLIDE_WITH_BORDER);
  ASSERT_EQ(brick.x, 1);
  ASSERT_EQ(brick.y, 0);
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(field[brick.cords[i][1] + brick.y][brick.cords[i][0] + brick.x],
              brick.color);
    ASSERT_EQ(brick.cords[i][0], brick2.cords[i][0]);
    ASSERT_EQ(brick.cords[i][1], brick2.cords[i][1]);
  }
  DeleteField(field, height);
}

TEST_F(MoveBrickCase, case_3) {
  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, height, width);
  GameInfo game_info;
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  Brick brick = BRICKS_TYPES[0];
  game_info.current_brick = brick;

  BornBrick(&brick, 0, 0, 0, 7);
  Brick brick2;
  BornBrick(&brick2, 0, 0, 0, 7);
  brick2.cords[0][0] = 0;
  brick2.cords[0][1] = 0;
  brick2.cords[1][0] = 0;
  brick2.cords[1][1] = 1;
  brick2.cords[2][0] = 0;
  brick2.cords[2][1] = 2;
  brick2.cords[3][0] = 0;
  brick2.cords[3][1] = 3;
  int status = MoveBrick(&game_info, &brick, kDirState, -1);

  ASSERT_EQ(status, COL_STATE_NO);
  ASSERT_EQ(brick.x, 0);
  ASSERT_EQ(brick.y, 0);
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(field[brick.cords[i][1] + brick.y][brick.cords[i][0] + brick.x],
              brick.color);
    ASSERT_EQ(brick.cords[i][0], brick2.cords[i][0]);
    ASSERT_EQ(brick.cords[i][1], brick2.cords[i][1]);
  }
  DeleteField(field, height);
}

TEST_F(MoveBrickCase, case_4) {
  int width = 10;
  int height = 3;
  int **field;
  InitField(&field, height, width);
  GameInfo game_info;
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  Brick brick = BRICKS_TYPES[0];
  game_info.current_brick = brick;

  BornBrick(&brick, 0, 0, 0, 7);
  Brick brick2 = brick;

  int status = MoveBrick(&game_info, &brick, kDirState, -1);

  ASSERT_EQ(status, COLLIDE_WITH_BORDER);
  ASSERT_EQ(brick.x, 0);
  ASSERT_EQ(brick.y, 0);
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(field[brick.cords[i][1] + brick.y][brick.cords[i][0] + brick.x],
              brick.color);
    ASSERT_EQ(brick.cords[i][0], brick2.cords[i][0]);
    ASSERT_EQ(brick.cords[i][1], brick2.cords[i][1]);
  }
  DeleteField(field, height);
}

TEST_F(MoveBrickCase, case_5) {
  Brick brick = BRICKS_TYPES[0];
  BornBrick(&brick, 1, 0, 0, 7);
  MoveBrickCords(&brick, kDirRight);
  ASSERT_EQ(brick.x, 2);
  ASSERT_EQ(brick.y, 0);
}

TEST_F(MoveBrickCase, case_6) {
  Brick brick = BRICKS_TYPES[0];
  BornBrick(&brick, 1, 0, 0, 7);
  MoveBrickCords(&brick, kDirDown);
  ASSERT_EQ(brick.x, 1);
  ASSERT_EQ(brick.y, 1);
}

TEST_F(MoveBrickCase, case_7) {
  Brick brick1 = BRICKS_TYPES[0];
  Brick brick2 = BRICKS_TYPES[0];
  BornBrick(&brick1, 0, 0, 0, 7);
  BornBrick(&brick2, 0, 0, 0, 7);
  brick2.cords[0][0] = 0;
  brick2.cords[0][1] = 0;
  brick2.cords[1][0] = 0;
  brick2.cords[1][1] = 1;
  brick2.cords[2][0] = 0;
  brick2.cords[2][1] = 2;
  brick2.cords[3][0] = 0;
  brick2.cords[3][1] = 3;
  RotateBrickCords(&brick1, -1);
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(brick1.cords[i][0], brick2.cords[i][0]);
    ASSERT_EQ(brick1.cords[i][1], brick2.cords[i][1]);
  }
}

TEST_F(MoveBrickCase, case_8) {
  Brick brick1 = BRICKS_TYPES[0];
  Brick brick2 = BRICKS_TYPES[0];
  BornBrick(&brick1, 0, 0, 0, 7);
  BornBrick(&brick2, 0, 0, 0, 7);
  brick2.cords[0][0] = 0;
  brick2.cords[0][1] = 0;
  brick2.cords[1][0] = 0;
  brick2.cords[1][1] = -1;
  brick2.cords[2][0] = 0;
  brick2.cords[2][1] = -2;
  brick2.cords[3][0] = 0;
  brick2.cords[3][1] = -3;
  RotateBrickCords(&brick1, 1);
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(brick1.cords[i][0], brick2.cords[i][0]);
    ASSERT_EQ(brick1.cords[i][1], brick2.cords[i][1]);
  }
}

TEST_F(MoveBrickCase, case_9) {
  Brick brick1 = BRICKS_TYPES[0];
  Brick brick2 = BRICKS_TYPES[0];
  BornBrick(&brick1, 0, 0, 6, 7);
  BornBrick(&brick2, 0, 0, 6, 7);
  brick2.cords[0][0] = 0;
  brick2.cords[0][1] = 0;
  brick2.cords[1][0] = 0;
  brick2.cords[1][1] = 1;
  brick2.cords[2][0] = -1;
  brick2.cords[2][1] = 1;
  brick2.cords[3][0] = -1;
  brick2.cords[3][1] = 2;
  RotateBrickCords(&brick1, -1);
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(brick1.cords[i][0], brick2.cords[i][0]);
    ASSERT_EQ(brick1.cords[i][1], brick2.cords[i][1]);
  }
}

TEST_F(MoveBrickCase, case_10) {
  Brick brick1 = BRICKS_TYPES[0];
  BornBrick(&brick1, 0, 0, 3, 7);
  int **field;
  int rows = 10;
  int cols = 10;
  InitField(&field, rows, cols);
  MoveBrickInField(field, &brick1);
  ASSERT_EQ(field[brick1.y][brick1.x], brick1.color);
  ASSERT_EQ(field[brick1.y][brick1.x + 1], brick1.color);
  ASSERT_EQ(field[brick1.y + 1][brick1.x], brick1.color);
  ASSERT_EQ(field[brick1.y + 1][brick1.x + 1], brick1.color);
  DeleteField(field, rows);
}

TEST_F(MoveBrickCase, case_11) {
  Brick brick1 = BRICKS_TYPES[0];
  BornBrick(&brick1, 0, 0, 5, 7);
  int **field;
  int rows = 10;
  int cols = 10;
  InitField(&field, rows, cols);
  MoveBrickInField(field, &brick1);
  ASSERT_EQ(field[brick1.y][brick1.x + 1], brick1.color);
  ASSERT_EQ(field[brick1.y + 1][brick1.x], brick1.color);
  ASSERT_EQ(field[brick1.y + 1][brick1.x + 1], brick1.color);
  ASSERT_EQ(field[brick1.y + 1][brick1.x + 2], brick1.color);
  DeleteFromField(field, &brick1);
  ASSERT_EQ(field[brick1.y][brick1.x + 1], 0);
  ASSERT_EQ(field[brick1.y + 1][brick1.x], 0);
  ASSERT_EQ(field[brick1.y + 1][brick1.x + 1], 0);
  ASSERT_EQ(field[brick1.y + 1][brick1.x + 2], 0);
  DeleteField(field, rows);
}