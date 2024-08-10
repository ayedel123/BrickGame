#include "../backTests.h"

START_TEST(case_1) {
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
  ck_assert_int_eq(points, 0);
  DeleteField(game_info.field, height);
}
END_TEST

START_TEST(case_2) {
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
  ck_assert_int_eq(field[1][0], 1);
  ck_assert_int_eq(field[1][1], 2);
  ck_assert_int_eq(field[1][2], 3);
  ck_assert_int_eq(field[1][3], 0);
  ck_assert_int_eq(full_lines, 1);

  DeleteField(game_info.field, height);
}
END_TEST

START_TEST(case_3) {
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
  ck_assert_int_eq(field[2][0], 1);
  ck_assert_int_eq(field[2][1], 2);
  ck_assert_int_eq(field[2][2], 3);
  ck_assert_int_eq(field[2][3], 0);
  ck_assert_int_eq(full_lines, 2);

  DeleteField(game_info.field, height);
}
END_TEST

Suite *linehandler_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("LineHandler");
  tc = tcase_create("test");

  tcase_add_test(tc, case_1);
  tcase_add_test(tc, case_2);
  tcase_add_test(tc, case_3);

  suite_add_tcase(s, tc);
  return s;
}