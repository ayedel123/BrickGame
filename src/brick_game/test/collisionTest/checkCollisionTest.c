#include "../backTests.h"

START_TEST(case_1) {
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
  ck_assert_int_eq(status, COL_STATE_COL);
  DeleteField(field, height);
}
END_TEST

START_TEST(case_2) {
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
  ck_assert_int_eq(status, COL_STATE_CRIT);
  DeleteField(field, height);
}
END_TEST

START_TEST(case_3) {
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
  int status = CheckCollision(&game_info, &brick1, kDirTop);
  ck_assert_int_eq(status, COL_STATE_COL);
  DeleteField(field, height);
}

END_TEST

START_TEST(case_4) {

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
  ck_assert_int_eq(status, COL_STATE_COL);
  DeleteField(field, height);
}
END_TEST

START_TEST(case_5) {
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

  ck_assert_int_eq(status, COL_STATE_NO);
  DeleteField(field, height);
}
END_TEST

START_TEST(case_6) {
  int width = 4;
  int height = 3;
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

  ck_assert_int_eq(status, COL_STATE_COL);
  DeleteField(field, height);
}
END_TEST

START_TEST(case_7) {
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
  ck_assert_int_eq(status, COL_STATE_CRIT);
  DeleteField(field, height);
}
END_TEST

START_TEST(case_8) {
  int width = 4;
  int height = 3;
  Brick brick = BRICKS_TYPES[0];
  BornBrick(&brick, -1, 0, 0, 7);
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  game_info.field = field;
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  game_info.current_brick = brick;

  int status = CheckCollision(&game_info, &brick, kDirDown);
  ck_assert_int_eq(status, COL_STATE_COL);
  DeleteField(field, height);
}
END_TEST

START_TEST(case_9) {
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
  ck_assert_int_eq(status, COL_STATE_COL);
  ck_assert_int_eq(brick.x, 1);
  ck_assert_int_eq(brick.y, 0);
  DeleteField(field, height);
}
END_TEST

Suite *collision_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("Collision");
  tc = tcase_create("test");

  tcase_add_test(tc, case_1);
  tcase_add_test(tc, case_2);
  tcase_add_test(tc, case_3);
  tcase_add_test(tc, case_4);
  tcase_add_test(tc, case_5);
  tcase_add_test(tc, case_6);
  tcase_add_test(tc, case_7);
  tcase_add_test(tc, case_8);
  tcase_add_test(tc, case_9);

  suite_add_tcase(s, tc);
  return s;
}