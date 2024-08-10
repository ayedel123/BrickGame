#include "../backTests.h"

START_TEST(move_brick_case_1) {
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

  int status = moveBrick(&game_info, &brick, kDirRight, 0);

  ck_assert_int_eq(status, COL_STATE_NO);
  ck_assert_int_eq(brick.x, 2);
  ck_assert_int_eq(brick.y, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(
        field[brick.cords[i][1] + brick.y][brick.cords[i][0] + brick.x],
        brick.color);
  }
  DeleteField(field, height);
}
END_TEST

START_TEST(move_brick_case_2) {
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
  int status = moveBrick(&game_info, &brick, kDirRight, 0);
  ck_assert_int_eq(status, COL_STATE_COL);
  ck_assert_int_eq(brick.x, 1);
  ck_assert_int_eq(brick.y, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(
        field[brick.cords[i][1] + brick.y][brick.cords[i][0] + brick.x],
        brick.color);
    ck_assert_int_eq(brick.cords[i][0], brick2.cords[i][0]);
    ck_assert_int_eq(brick.cords[i][1], brick2.cords[i][1]);
  }
  DeleteField(field, height);
}
END_TEST

START_TEST(move_brick_case_3) {
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
  int status = moveBrick(&game_info, &brick, kDirState, -1);

  ck_assert_int_eq(status, COL_STATE_NO);
  ck_assert_int_eq(brick.x, 0);
  ck_assert_int_eq(brick.y, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(
        field[brick.cords[i][1] + brick.y][brick.cords[i][0] + brick.x],
        brick.color);
    ck_assert_int_eq(brick.cords[i][0], brick2.cords[i][0]);
    ck_assert_int_eq(brick.cords[i][1], brick2.cords[i][1]);
  }
  DeleteField(field, height);
}

START_TEST(move_brick_case_4) {
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

  int status = moveBrick(&game_info, &brick, kDirState, -1);

  ck_assert_int_eq(status, COL_STATE_COL);
  ck_assert_int_eq(brick.x, 0);
  ck_assert_int_eq(brick.y, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(
        field[brick.cords[i][1] + brick.y][brick.cords[i][0] + brick.x],
        brick.color);
    ck_assert_int_eq(brick.cords[i][0], brick2.cords[i][0]);
    ck_assert_int_eq(brick.cords[i][1], brick2.cords[i][1]);
  }
  DeleteField(field, height);
}

Suite *move_brick_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("moveBrick");
  tc = tcase_create("test");

  tcase_add_test(tc, move_brick_case_1);
  tcase_add_test(tc, move_brick_case_2);
  tcase_add_test(tc, move_brick_case_3);
  tcase_add_test(tc, move_brick_case_4);

  suite_add_tcase(s, tc);
  return s;
}
