#ifndef CPP3_BRICKGAME_V2_0_1_SRC_TEST_BACK_TEST_CHECK_COLLISION_TEST_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_TEST_BACK_TEST_CHECK_COLLISION_TEST_H_

#include "back_test.h"

class MapTestCase : public ::testing::Test
{
};

TEST_F(MapTestCase, case_1)
{
  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, width, height);

  GameInfo game_info;
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  Brick brick1 = BRICKS_TYPES[0];
  game_info.current_brick = brick1;
  BornBrick(&brick1, 1, 0, 0, 7);

  field[0][4] = 1;
  int status = 0;
  status = CheckCollision(&game_info, &brick1, kDirRight);
  ASSERT_EQ(status, 1);
  DeleteField(field, height);
}

TEST_F(MapTestCase, case_2)
{
  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  Brick brick1 = BRICKS_TYPES[0];
  game_info.current_brick = brick1;
  BornBrick(&brick1, 1, 1, 0, 7);
  field[1][4] = 1;
  int status = 0;
  status = CheckCollision(&game_info, &brick1, kDirDown);
  ASSERT_EQ(status, 1);
  DeleteField(field, height);
}

TEST_F(MapTestCase, case_3)
{
  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  Brick brick1 = BRICKS_TYPES[0];
  game_info.current_brick = brick1;
  BornBrick(&brick1, -1, 0, 0, 7);
  int status = CheckCollision(&game_info, &brick1, kDirTop);
  ASSERT_EQ(status, COLLIDE_WITH_BORDER);
  DeleteField(field, height);
}

// END_TEST

TEST_F(MapTestCase, case_4)
{
  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  Brick brick1 = BRICKS_TYPES[0];
  game_info.current_brick = brick1;
  BornBrick(&brick1, 1, 0, 0, 7);
  field[0][1] = 1;
  int status = CheckCollision(&game_info, &brick1, kDirLeft);
  ASSERT_EQ(status, 1);
  DeleteField(field, height);
}

TEST_F(MapTestCase, case_5)
{
  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  Brick brick = BRICKS_TYPES[0];
  game_info.current_brick = brick;
  BornBrick(&brick, 1, 0, 0, 7);
  int status = CheckCollision(&game_info, &brick, kDirLeft);

  ASSERT_EQ(status, COL_STATE_NO);
  DeleteField(field, height);
}


TEST_F(MapTestCase, case_6)
{
  int width = 4;
  int height = 3;
  int **field;
  InitField(&field,height,width);
  GameInfo game_info;
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  Brick brick = BRICKS_TYPES[0];
  game_info.current_brick = brick;
  BornBrick(&brick, 1, 0, 0, 7);
  int status = CheckCollision(&game_info, &brick, kDirLeft);

  ASSERT_EQ(status, COLLIDE_WITH_BORDER);
  DeleteField(field, height);
}


TEST_F(MapTestCase, case_8)
{
  int width = 4;
  int height = 1;
  Brick brick = BRICKS_TYPES[0];
  BornBrick(&brick, 1, 0, 4, 7);
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  game_info.current_brick = brick;

  int status = CheckCollision(&game_info, &brick, kDirDown);
  ASSERT_EQ(status, COLLIDE_WITH_BORDER);
  DeleteField(field, width);
}

TEST_F(MapTestCase, case_9)
{
  int width = 4;
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
  int status = CheckCollision(&game_info, &brick, kDirRight);
  ASSERT_EQ(status, COLLIDE_WITH_BORDER);
  DeleteField(field, height);
}

TEST_F(MapTestCase, case_10)
{
  int width = 20;
  int height = 20;
  Brick brick = BRICKS_TYPES[0];
  BornBrick(&brick, 1, 0, 0, 7);
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0)
                 ? CheckOutOfBounds(&brick, i, width, height, kDirRight)
                 : status;
  }
  ASSERT_EQ(status, COL_STATE_NO);
}


TEST_F(MapTestCase, case_11)
{

  int width = 4;
  int height = 3;
  Brick brick = BRICKS_TYPES[0];
  BornBrick(&brick, 1, 0, 0, 7);
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0)
                 ? CheckOutOfBounds(&brick, i, width, height, kDirRight)
                 : status;
  }
  ASSERT_EQ(status, COLLIDE_WITH_BORDER);
}


TEST_F(MapTestCase, case_12)
{

  int width = 4;
  int height = 1;
  Brick brick = BRICKS_TYPES[0];
  BornBrick(&brick, 1, 0, 4, 7);
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0)
                 ? CheckOutOfBounds(&brick, i, width, height, kDirDown)
                 : status;
  }
  ASSERT_EQ(status, COLLIDE_WITH_BORDER);
}

TEST_F(MapTestCase, case_13)
{

  int width = 4;
  int height = 3;
  Brick brick = BRICKS_TYPES[0];
  BornBrick(&brick, -1, 0, 0, 7);
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0)
                 ? CheckOutOfBounds(&brick, i, width, height, kDirDown)
                 : status;
  }
  ASSERT_EQ(status, COLLIDE_WITH_BORDER);
}

TEST_F(MapTestCase, case_14)
{
  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, width, height);
  Brick brick1 = BRICKS_TYPES[0];
  BornBrick(&brick1, 1, 0, 0, 7);
  field[0][4] = 1;
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0) ? CheckCollisionBrick(field, &brick1, i)
                           : status;
  }
  ASSERT_EQ(status, 1);
  DeleteField(field, height);
}

TEST_F(MapTestCase, case_15)
{
  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, width, height);
  Brick brick1 = BRICKS_TYPES[0];
  BornBrick(&brick1, 1, 1, 0, 7);
  field[1][4] = 1;
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0) ? CheckCollisionBrick(field, &brick1, i)
                           : status;
  }
  ASSERT_EQ(status, 1);
  DeleteField(field, height);
}

TEST_F(MapTestCase, case_16)
{
  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, width, height);
  Brick brick1 = BRICKS_TYPES[0];
  BornBrick(&brick1, 1, 0, 0, 7);
  field[0][4] = 1;
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0) ? CheckCollisionBrick(field, &brick1, i)
                           : status;
  }
  ASSERT_EQ(status, 1);
  DeleteField(field, height);
}

TEST_F(MapTestCase, case_17)
{
  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, width, height);
  Brick brick1 = BRICKS_TYPES[0];
  BornBrick(&brick1, 1, 0, 0, 7);
  field[0][1] = 1;
  int status = 0;
  status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0) ? CheckCollisionBrick(field, &brick1, i)
                           : status;
  }
  ASSERT_EQ(status, 1);
  DeleteField(field, height);
}


#endif