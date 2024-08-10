#include "../backTests.h"

START_TEST(case_1) {
  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, width, height);
  Brick brick1 = BRICKS_TYPES[0];
  BornBrick(&brick1, 1, 0, 0, 7);
  field[0][4] = 1;
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0) ? CheckCollisionBrick(field, &brick1, i, kDirRight)
                           : status;
  }
  ck_assert_int_eq(status, COL_STATE_COL);
  DeleteField(field, height);
}
END_TEST

START_TEST(case_2) {
  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, width, height);
  Brick brick1 = BRICKS_TYPES[0];
  BornBrick(&brick1, 1, 1, 0, 7);
  field[1][4] = 1;
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0) ? CheckCollisionBrick(field, &brick1, i, kDirDown)
                           : status;
  }
  ck_assert_int_eq(status, COL_STATE_CRIT);
  DeleteField(field, height);
}
END_TEST

START_TEST(case_3) {
  int width = 10;
  int height = 10;
  int **field;
  InitField(&field, width, height);
  Brick brick1 = BRICKS_TYPES[0];
  BornBrick(&brick1, 1, 0, 0, 7);
  field[0][4] = 1;
  int status = 0;
  for (int i = 0; i < 4; i++) {
    status = (status == 0) ? CheckCollisionBrick(field, &brick1, i, kDirTop)
                           : status;
  }
  ck_assert_int_eq(status, COL_STATE_COL);
  DeleteField(field, height);
}
END_TEST

START_TEST(case_4) {
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
    status = (status == 0) ? CheckCollisionBrick(field, &brick1, i, kDirLeft)
                           : status;
  }
  ck_assert_int_eq(status, COL_STATE_COL);
  DeleteField(field, height);
}
END_TEST

Suite *collision_brick_suite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("collision_bot");
  tc = tcase_create("test");

  tcase_add_test(tc, case_1);
  tcase_add_test(tc, case_2);
  tcase_add_test(tc, case_3);
  tcase_add_test(tc, case_4);

  suite_add_tcase(s, tc);
  return s;
}
