#include "../backTests.h"

START_TEST(case_1) {
  int width = 10;
  int height = 2;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  InitGameInfo(&game_info, field, 10, 10);
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  AddPoints(&game_info, 4);
  ck_assert_int_eq(game_info.points, 1500);
  ck_assert_int_eq(game_info.level, 3);
  DeleteField(game_info.field, height);
}
END_TEST

START_TEST(case_2) {
  int width = 10;
  int height = 2;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  InitGameInfo(&game_info, field, 10, 10);
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  AddPoints(&game_info, 0);
  ck_assert_int_eq(game_info.points, 0);
  ck_assert_int_eq(game_info.level, 1);
  DeleteField(game_info.field, height);
}
END_TEST

START_TEST(case_3) {
  int width = 10;
  int height = 2;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  InitGameInfo(&game_info, field, 10, 10);
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  AddPoints(&game_info, 1);
  ck_assert_int_eq(game_info.points, 100);
  ck_assert_int_eq(game_info.level, 1);
  DeleteField(game_info.field, height);
}
END_TEST

START_TEST(case_4) {
  int width = 10;
  int height = 2;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  InitGameInfo(&game_info, field, 10, 10);
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  game_info.points = 300;
  AddPoints(&game_info, 2);
  ck_assert_int_eq(game_info.points, 600);
  ck_assert_int_eq(game_info.level, 2);
  DeleteField(game_info.field, height);
}
END_TEST

START_TEST(case_5) {
  int width = 10;
  int height = 2;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  InitGameInfo(&game_info, field, 10, 10);
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  AddPoints(&game_info, 1500);
  ck_assert_int_eq(game_info.points, 1500);
  ck_assert_int_eq(game_info.level, 3);
  DeleteField(game_info.field, height);
}
END_TEST

Suite *add_points_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("AdPointsTest");
  tc = tcase_create("test");

  tcase_add_test(tc, case_1);
  tcase_add_test(tc, case_2);
  tcase_add_test(tc, case_3);
  tcase_add_test(tc, case_4);
  tcase_add_test(tc, case_5);

  suite_add_tcase(s, tc);
  return s;
}