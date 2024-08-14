#ifndef CPP3_BRICKGAME_V2_0_1_SRC_TEST_BACK_TEST_TETRIS_TEST_FULL_LINE_HANDLER_TEST_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_TEST_BACK_TEST_TETRIS_TEST_FULL_LINE_HANDLER_TEST_H_

#include "tetris_test.h"

class FullLineHandlerTest : public ::testing::Test
{
};


TEST_F(FullLineHandlerTest, case_1)
{
  int width = 4;
  int height = 4;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  ClearField(field, height, width);
  game_info.field[1][0] = 1;
  game_info.field[1][1] = 2;
  game_info.field[1][2] = 3;
  game_info.field[1][0] = 4;

  int points = FullLineHandler(&game_info);
  ASSERT_EQ(points, 0);
  DeleteField(game_info.field, height);
}

TEST_F(FullLineHandlerTest, case_2)
{
  int width = 4;
  int height = 4;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  ClearField(field, height, width);
  game_info.field[0][0] = 1;
  game_info.field[0][1] = 2;
  game_info.field[0][2] = 3;
  game_info.field[0][3] = 0;
  game_info.field[1][0] = 1;
  game_info.field[1][1] = 2;
  game_info.field[1][2] = 3;
  game_info.field[1][3] = 4;

  int full_lines = FullLineHandler(&game_info);
  ASSERT_EQ(field[1][0], 1);
  ASSERT_EQ(field[1][1], 2);
  ASSERT_EQ(field[1][2], 3);
  ASSERT_EQ(field[1][3], 0);
  ASSERT_EQ(full_lines, 1);

  DeleteField(game_info.field, height);
}


TEST_F(FullLineHandlerTest, case_3)
{
  int width = 4;
  int height = 4;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  ClearField(field, height, width);
  game_info.field[0][0] = 1;
  game_info.field[0][1] = 2;
  game_info.field[0][2] = 3;
  game_info.field[0][3] = 0;
  game_info.field[1][0] = 1;
  game_info.field[1][1] = 2;
  game_info.field[1][2] = 3;
  game_info.field[1][3] = 4;
  game_info.field[2][0] = 1;
  game_info.field[2][1] = 2;
  game_info.field[2][2] = 3;
  game_info.field[2][3] = 4;
  int full_lines = FullLineHandler(&game_info);
  ASSERT_EQ(field[2][0], 1);
  ASSERT_EQ(field[2][1], 2);
  ASSERT_EQ(field[2][2], 3);
  ASSERT_EQ(field[2][3], 0);
  ASSERT_EQ(full_lines, 2);

  DeleteField(game_info.field, height);
}


TEST_F(FullLineHandlerTest, case_5)
{
  int width = 4;
  int height = 4;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;

  game_info.field[0][0] = 1;
  game_info.field[1][0] = 2;
  game_info.field[2][0] = 3;
  game_info.field[3][0] = 4;

  DropLines(&game_info, 3, 1);

  ASSERT_EQ(game_info.field[0][0], 0);
  ASSERT_EQ(game_info.field[1][0], 1);
  ASSERT_EQ(game_info.field[2][0], 2);
  ASSERT_EQ(game_info.field[3][0], 3);

  DeleteField(game_info.field, height);
}

TEST_F(FullLineHandlerTest, case_6)
{
  int width = 4;
  int height = 4;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;

  game_info.field[1][0] = 2;
  game_info.field[1][1] = 3;
  game_info.field[1][2] = 4;
  game_info.field[1][3] = 5;

  int line_id = 1;
  int isFull = IsLineFull(&game_info, line_id);

  ASSERT_EQ(isFull, 1);

  DeleteField(game_info.field, height);
}

TEST_F(FullLineHandlerTest, case_7)
{

  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  InitGameInfo(&game_info, field, 10, 10,RANDOM_BRICK,"test_record");
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  Brick secondBrick = game_info.next_brick;

  int status = resetBrick(&game_info);
  ASSERT_EQ(game_info.current_brick.x, secondBrick.x);
  ASSERT_EQ(game_info.current_brick.y, secondBrick.y);
  ASSERT_EQ(game_info.current_brick.color, secondBrick.color);
  for (int i = 0; i < 4; i++) {
    ASSERT_EQ(game_info.current_brick.cords[i][0],
                     secondBrick.cords[i][0]);
    ASSERT_EQ(game_info.current_brick.cords[i][1],
                     secondBrick.cords[i][1]);
  }
  ASSERT_EQ(status, 0);

  DeleteField(game_info.field, height);
}

#endif