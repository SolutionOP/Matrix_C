#include <check.h>

#include "s21_matrix.h"

void s21_matrix_testing(SRunner **sr);

START_TEST(s21_eq_matrix_test_1) {
  matrix_t A = s21_create_matrix(41, 41);
  matrix_t B = s21_create_matrix(41, 41);
  s21_fill(&A, 1);
  s21_fill(&B, 1);
  int expected_result = SUCCESS;
  int actual_result = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_2) {
  matrix_t A = s21_create_matrix(83, 83);
  matrix_t B = s21_create_matrix(83, 83);
  s21_fill(&A, 7);
  s21_fill(&B, 9);
  int expected_result = FAILURE;
  int actual_result = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_3) {
  matrix_t A = s21_create_matrix(32, 32);
  matrix_t B = s21_create_matrix(27, 27);
  s21_fill(&A, 42);
  s21_fill(&B, 42);
  int expected_result = FAILURE;
  int actual_result = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_4) {
  matrix_t A = s21_create_matrix(22, 22);
  matrix_t B = s21_create_matrix(22, 22);
  s21_fill(&A, 13);
  s21_fill(&B, 13);
  A.matrix_type = INCORRECT_MATRIX;
  int expected_result = FAILURE;
  int actual_result = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(expected_result, actual_result);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *s21_eq_matrix_suite(void) {
  Suite *s;
  TCase *tc_s21_eq_matrix;
  s = suite_create("\n s21_eq_matrix");
  tc_s21_eq_matrix = tcase_create("eq_matrix");
  tcase_add_test(tc_s21_eq_matrix, s21_eq_matrix_test_1);
  tcase_add_test(tc_s21_eq_matrix, s21_eq_matrix_test_2);
  tcase_add_test(tc_s21_eq_matrix, s21_eq_matrix_test_3);
  tcase_add_test(tc_s21_eq_matrix, s21_eq_matrix_test_4);
  suite_add_tcase(s, tc_s21_eq_matrix);
  return s;
}

START_TEST(s21_sum_matrix_test_1) {
  matrix_t A = s21_create_matrix(4, 4);
  matrix_t B = s21_create_matrix(4, 4);
  s21_fill(&A, 3);
  s21_fill(&B, 4);
  matrix_t expected_result = s21_create_matrix(4, 4);
  s21_fill(&expected_result, 7);
  matrix_t actual_result = s21_sum_matrix(&A, &B);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(expected_result.matrix[i][j],
                          actual_result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
}
END_TEST

START_TEST(s21_sum_matrix_test_2) {
  matrix_t A = s21_create_matrix(2, 2);
  matrix_t B = s21_create_matrix(4, 4);
  matrix_t expected_result = s21_create_matrix(2, 2);
  expected_result.matrix_type = INCORRECT_MATRIX;
  matrix_t actual_result = s21_sum_matrix(&A, &B);
  ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
}
END_TEST

START_TEST(s21_sum_matrix_test_3) {
  matrix_t A = s21_create_matrix(4, 4);
  matrix_t B = s21_create_matrix(4, 4);
  B.matrix[0][0] = 1;
  B.matrix[1][1] = 1;
  B.matrix[2][2] = 1;
  B.matrix[3][3] = 1;
  matrix_t expected_result = s21_create_matrix(4, 4);
  expected_result.matrix[0][0] = 1;
  expected_result.matrix[1][1] = 1;
  expected_result.matrix[2][2] = 1;
  expected_result.matrix[3][3] = 1;
  expected_result.matrix_type = IDENTITY_MATRIX;
  matrix_t actual_result = s21_sum_matrix(&A, &B);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(expected_result.matrix[i][j],
                          actual_result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
}
END_TEST

Suite *s21_sum_matrix_suite(void) {
  Suite *s;
  TCase *tc_s21_sum_matrix;
  s = suite_create("\n s21_sum_matrix");
  tc_s21_sum_matrix = tcase_create("sum_matrix");
  tcase_add_test(tc_s21_sum_matrix, s21_sum_matrix_test_1);
  tcase_add_test(tc_s21_sum_matrix, s21_sum_matrix_test_2);
  tcase_add_test(tc_s21_sum_matrix, s21_sum_matrix_test_3);
  suite_add_tcase(s, tc_s21_sum_matrix);
  return s;
}

START_TEST(s21_sub_matrix_test_1) {
  matrix_t A = s21_create_matrix(4, 4);
  matrix_t B = s21_create_matrix(4, 4);
  s21_fill(&A, 6);
  s21_fill(&B, 4);
  matrix_t expected_result = s21_create_matrix(4, 4);
  s21_fill(&expected_result, 2);
  matrix_t actual_result = s21_sub_matrix(&A, &B);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(expected_result.matrix[i][j],
                          actual_result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
}
END_TEST

START_TEST(s21_sub_matrix_test_2) {
  matrix_t A = s21_create_matrix(2, 2);
  matrix_t B = s21_create_matrix(4, 4);
  matrix_t expected_result = s21_create_matrix(2, 2);
  expected_result.matrix_type = INCORRECT_MATRIX;
  matrix_t actual_result = s21_sub_matrix(&A, &B);
  ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
}
END_TEST

Suite *s21_sub_matrix_suite(void) {
  Suite *s;
  TCase *tc_s21_sub_matrix;
  s = suite_create("\n s21_sub_matrix");
  tc_s21_sub_matrix = tcase_create("sub_matrix");
  tcase_add_test(tc_s21_sub_matrix, s21_sub_matrix_test_1);
  tcase_add_test(tc_s21_sub_matrix, s21_sub_matrix_test_2);
  suite_add_tcase(s, tc_s21_sub_matrix);
  return s;
}

START_TEST(s21_mult_number_test_1) {
  matrix_t A = s21_create_matrix(4, 4);
  s21_fill(&A, 3);
  matrix_t expected_result = s21_create_matrix(4, 4);
  s21_fill(&expected_result, 30);
  matrix_t actual_result = s21_mult_number(&A, 10);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(expected_result.matrix[i][j],
                          actual_result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
}
END_TEST

START_TEST(s21_mult_number_test_2) {
  matrix_t A = s21_create_matrix(2, 2);
    A.matrix_type = INCORRECT_MATRIX;
  matrix_t expected_result = s21_create_matrix(2, 2);
  expected_result.matrix_type = INCORRECT_MATRIX;
  matrix_t actual_result = s21_mult_number(&A, 3);
  ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
}
END_TEST

Suite *s21_mult_number_suite(void) {
  Suite *s;
  TCase *tc_s21_mult_number;
  s = suite_create("\n s21_mult_number");
  tc_s21_mult_number = tcase_create("mult_number");
  tcase_add_test(tc_s21_mult_number, s21_mult_number_test_1);
  tcase_add_test(tc_s21_mult_number, s21_mult_number_test_2);
  suite_add_tcase(s, tc_s21_mult_number);
  return s;
}

START_TEST(s21_mult_matrix_test_1) {
  matrix_t A = s21_create_matrix(4, 4);
  matrix_t B = s21_create_matrix(4, 4);
  s21_fill(&A, 3);
  s21_fill(&B, 3);
  matrix_t expected_result = s21_create_matrix(4, 4);
  s21_fill(&expected_result, 36);
  matrix_t actual_result = s21_mult_matrix(&A, &B);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(expected_result.matrix[i][j],
                          actual_result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
}
END_TEST

START_TEST(s21_mult_matrix_test_2) {
  matrix_t A = s21_create_matrix(4, 4);
  matrix_t B = s21_create_matrix(3, 3);
  s21_fill(&A, 3);
  s21_fill(&B, 3);
  matrix_t expected_result = s21_create_matrix(4, 4);
  expected_result.matrix_type = INCORRECT_MATRIX;
  matrix_t actual_result = s21_mult_matrix(&A, &B);
  ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
}
END_TEST

Suite *s21_mult_matrix_suite(void) {
  Suite *s;
  TCase *tc_s21_mult_matrix;
  s = suite_create("\n s21_mult_matrix");
  tc_s21_mult_matrix = tcase_create("mult_matrix");
  tcase_add_test(tc_s21_mult_matrix, s21_mult_matrix_test_1);
  tcase_add_test(tc_s21_mult_matrix, s21_mult_matrix_test_2);
  suite_add_tcase(s, tc_s21_mult_matrix);
  return s;
}

START_TEST(s21_transpose_test_1) {
  matrix_t A = s21_create_matrix(4, 4);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;

  A.matrix[1][0] = 1;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 3;
  A.matrix[1][3] = 4;

  A.matrix[2][0] = 1;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 3;
  A.matrix[2][3] = 4;

  A.matrix[3][0] = 1;
  A.matrix[3][1] = 2;
  A.matrix[3][2] = 3;
  A.matrix[3][3] = 4;

  matrix_t expected_result = s21_create_matrix(4, 4);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      expected_result.matrix[j][i] = A.matrix[i][j];
    }
  }
  expected_result.matrix_type = CORRECT_MATRIX;

  matrix_t actual_result = s21_transpose(&A);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq(expected_result.matrix[i][j],
                          actual_result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
}
END_TEST

START_TEST(s21_transpose_test_2) {
  matrix_t A = s21_create_matrix(4, 4);
    A.matrix_type = INCORRECT_MATRIX;
  matrix_t expected_result = s21_create_matrix(4, 4);
  expected_result.matrix_type = INCORRECT_MATRIX;
  matrix_t actual_result = s21_transpose(&A);
  ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
}
END_TEST

Suite *s21_transpose_suite(void) {
  Suite *s;
  TCase *tc_s21_transpose;
  s = suite_create("\n s21_transpose");
  tc_s21_transpose = tcase_create("transpose");
  tcase_add_test(tc_s21_transpose, s21_transpose_test_1);
  tcase_add_test(tc_s21_transpose, s21_transpose_test_2);
  suite_add_tcase(s, tc_s21_transpose);
  return s;
}

START_TEST(s21_calc_complements_test_1) {
  matrix_t A = s21_create_matrix(3, 3);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  A.matrix_type = CORRECT_MATRIX;

  matrix_t expected_result = s21_create_matrix(3, 3);

  expected_result.matrix[0][0] = 0;
  expected_result.matrix[0][1] = 10;
  expected_result.matrix[0][2] = -20;

  expected_result.matrix[1][0] = 4;
  expected_result.matrix[1][1] = -14;
  expected_result.matrix[1][2] = 8;

  expected_result.matrix[2][0] = -8;
  expected_result.matrix[2][1] = -2;
  expected_result.matrix[2][2] = 4;
  expected_result.matrix_type = CORRECT_MATRIX;

  matrix_t actual_result = s21_calc_complements(&A);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(expected_result.matrix[i][j],
                          actual_result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
}

START_TEST(s21_calc_complements_test_2) {
  matrix_t A = s21_create_matrix(3, 4);
    A.matrix_type = INCORRECT_MATRIX;
  matrix_t expected_result = s21_create_matrix(3, 4);
  expected_result.matrix_type = INCORRECT_MATRIX;
  matrix_t actual_result = s21_calc_complements(&A);
  ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
}
END_TEST

Suite *s21_calc_complements_suite(void) {
  Suite *s;
  TCase *tc_s21_calc_complements;
  s = suite_create("\n s21_calc_complements");
  tc_s21_calc_complements = tcase_create("calc_complements");
  tcase_add_test(tc_s21_calc_complements, s21_calc_complements_test_1);
  tcase_add_test(tc_s21_calc_complements, s21_calc_complements_test_2);
  suite_add_tcase(s, tc_s21_calc_complements);
  return s;
}

START_TEST(s21_determinant_test_1) {
  matrix_t A = s21_create_matrix(3, 3);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  A.matrix_type = CORRECT_MATRIX;
  double expected_result = 0;
  double actual_result = s21_determinant(&A);
  ck_assert_ldouble_eq(expected_result, actual_result);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test_2) {
  matrix_t A = s21_create_matrix(3, 4);
  double actual_result = s21_determinant(&A);
  ck_assert_double_nan(actual_result);
  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_determinant_suite(void) {
  Suite *s;
  TCase *tc_s21_determinant;
  s = suite_create("\n s21_determinant");
  tc_s21_determinant = tcase_create("determinant");
  tcase_add_test(tc_s21_determinant, s21_determinant_test_1);
  tcase_add_test(tc_s21_determinant, s21_determinant_test_2);
  suite_add_tcase(s, tc_s21_determinant);
  return s;
}

START_TEST(s21_inverse_matrix_test_1) {
  matrix_t A = s21_create_matrix(3, 3);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;

  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;
  A.matrix_type = CORRECT_MATRIX;

  matrix_t expected_result = s21_create_matrix(3, 3);

  expected_result.matrix[0][0] = 1;
  expected_result.matrix[0][1] = -1;
  expected_result.matrix[0][2] = 1;

  expected_result.matrix[1][0] = -38;
  expected_result.matrix[1][1] = 41;
  expected_result.matrix[1][2] = -34;

  expected_result.matrix[2][0] = 27;
  expected_result.matrix[2][1] = -29;
  expected_result.matrix[2][2] = 24;
  expected_result.matrix_type = CORRECT_MATRIX;

  matrix_t actual_result = s21_inverse_matrix(&A);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq(expected_result.matrix[i][j],
                          actual_result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected_result);
  s21_remove_matrix(&actual_result);
}

START_TEST(s21_inverse_matrix_test_2) {
  matrix_t A = s21_create_matrix(3, 3);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  A.matrix_type = CORRECT_MATRIX;
  matrix_t expected_result = s21_create_matrix(3, 3);
  expected_result.matrix_type = INCORRECT_MATRIX;
  matrix_t actual_result = s21_inverse_matrix(&A);
  ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
  s21_remove_matrix(&A);
  s21_remove_matrix(&expected_result);
}
END_TEST

Suite *s21_inverse_matrix_suite(void) {
  Suite *s;
  TCase *tc_s21_inverse_matrix;
  s = suite_create("\n s21_inverse_matrix");
  tc_s21_inverse_matrix = tcase_create("inverse_matrix");
  tcase_add_test(tc_s21_inverse_matrix, s21_inverse_matrix_test_1);
  tcase_add_test(tc_s21_inverse_matrix, s21_inverse_matrix_test_2);
  suite_add_tcase(s, tc_s21_inverse_matrix);
  return s;
}

START_TEST(s21_create_matrix_test_1) {
  matrix_t actual_result = s21_create_matrix(-88, -88);
  matrix_t expected_result;
  expected_result.matrix_type = INCORRECT_MATRIX;
  ck_assert_uint_eq(expected_result.matrix_type, actual_result.matrix_type);
}
END_TEST

Suite *s21_create_matrix_suite(void) {
  Suite *s;
  TCase *tc_s21_create_matrix;
  s = suite_create("\n s21_create_matrix");
  tc_s21_create_matrix = tcase_create("create_matrix");
  tcase_add_test(tc_s21_create_matrix, s21_create_matrix_test_1);
  suite_add_tcase(s, tc_s21_create_matrix);
  return s;
}

void s21_matrix_testing(SRunner **sr) {
  *sr = srunner_create(s21_eq_matrix_suite());
  srunner_add_suite(*sr, s21_sum_matrix_suite());
  srunner_add_suite(*sr, s21_sub_matrix_suite());
  srunner_add_suite(*sr, s21_mult_number_suite());
  srunner_add_suite(*sr, s21_mult_matrix_suite());
  srunner_add_suite(*sr, s21_transpose_suite());
  srunner_add_suite(*sr, s21_calc_complements_suite());
  srunner_add_suite(*sr, s21_determinant_suite());
  srunner_add_suite(*sr, s21_inverse_matrix_suite());
  srunner_add_suite(*sr, s21_create_matrix_suite());
}

int main(void) {
  int number_failed;
  SRunner *sr = NULL;
  s21_matrix_testing(&sr);
  srunner_run_all(sr, CK_ENV);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
