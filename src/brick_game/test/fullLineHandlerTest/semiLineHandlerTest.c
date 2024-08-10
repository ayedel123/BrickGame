#include "../backTests.h"

START_TEST(drop_lines_case_1) {
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

  dropLines(&game_info, 3, 1);

  ck_assert_int_eq(game_info.field[0][0], 0);
  ck_assert_int_eq(game_info.field[1][0], 1);
  ck_assert_int_eq(game_info.field[2][0], 2);
  ck_assert_int_eq(game_info.field[3][0], 3);

  DeleteField(game_info.field, height);
}
END_TEST

START_TEST(is_line_full_case_1) {
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
  int isFull = isLineFull(&game_info, line_id);

  ck_assert_int_eq(isFull, 1);

  DeleteField(game_info.field, height);
}
END_TEST

START_TEST(reset_brick_case_1) {
  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, width, height);
  GameInfo game_info;
  InitGameInfo(&game_info, field, 10, 10);
  game_info.win_info.height = height;
  game_info.win_info.width = width;
  Brick secondBrick = game_info.next_brick;

  int status = resetBrick(&game_info);
  ck_assert_int_eq(game_info.current_brick.x, secondBrick.x);
  ck_assert_int_eq(game_info.current_brick.y, secondBrick.y);
  ck_assert_int_eq(game_info.current_brick.color, secondBrick.color);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(game_info.current_brick.cords[i][0],
                     secondBrick.cords[i][0]);
    ck_assert_int_eq(game_info.current_brick.cords[i][1],
                     secondBrick.cords[i][1]);
  }
  ck_assert_int_eq(status, 0);

  DeleteField(game_info.field, height);
}
END_TEST

Suite *semi_linehandler_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("LineHandlerSemiFuncs");
  tc = tcase_create("test");

  tcase_add_test(tc, drop_lines_case_1);
  tcase_add_test(tc, is_line_full_case_1);
  tcase_add_test(tc, reset_brick_case_1);

  suite_add_tcase(s, tc);
  return s;
}