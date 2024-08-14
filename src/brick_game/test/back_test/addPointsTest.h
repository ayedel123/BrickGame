#ifndef CPP3_BRICKGAME_V2_0_1_SRC_TEST_BACK_TEST_ADD_POINTS_TEST_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_TEST_BACK_TEST_ADD_POINTS_TEST_H_

#include "back_test.h"

class AddPointsTest : public ::testing::Test
{
};

TEST_F(AddPointsTest, case_1)
{
  int width = 10;
  int height = 2;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  InitGameInfo(&game_info, field, 10, 10,RANDOM_BRICK,"test_record");
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  AddPoints(&game_info, 4);
  ASSERT_EQ(game_info.points, 1500);
  ASSERT_EQ(game_info.level, 3);
  DeleteField(game_info.field, width);
}
 
TEST_F(AddPointsTest, case_2)
{
  int width = 10;
  int height = 2;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  InitGameInfo(&game_info, field, 10, 10,RANDOM_BRICK,"test_record");
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  AddPoints(&game_info, 0);
  ASSERT_EQ(game_info.points, 0);
  ASSERT_EQ(game_info.level, 1);
  DeleteField(game_info.field, width);
}
 

TEST_F(AddPointsTest, case_3)
{
  int width = 10;
  int height = 2;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  InitGameInfo(&game_info, field, 10, 10,RANDOM_BRICK,"test_record");
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  AddPoints(&game_info, 1);
  ASSERT_EQ(game_info.points, 100);
  ASSERT_EQ(game_info.level, 1);
  DeleteField(game_info.field, width);
}
 

TEST_F(AddPointsTest, case_4)
{
  int width = 10;
  int height = 2;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  InitGameInfo(&game_info, field, 10, 10,RANDOM_BRICK,"test_record");
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  game_info.points = 300;
  AddPoints(&game_info, 2);
  ASSERT_EQ(game_info.points, 600);
  ASSERT_EQ(game_info.level, 2);
  DeleteField(game_info.field, width);
}
 

TEST_F(AddPointsTest, case_5)
{
  int width = 10;
  int height = 2;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  InitGameInfo(&game_info, field, 10, 10,RANDOM_BRICK,"test_record");
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  AddPoints(&game_info, 1500);
  ASSERT_EQ(game_info.points, 1500);
  ASSERT_EQ(game_info.level, 3);
  DeleteField(game_info.field, width);
}

#endif