#include <check.h>
#include <errno.h>

#include "s21_matrix.h"

// s21_create_matrix

START_TEST(test_s21_create_matrix_1) {
  matrix_t matrix = {0};
  ck_assert_int_eq(s21_create_matrix(1, 1, &matrix), OK);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_s21_create_matrix_2) {
  matrix_t matrix = {0};
  ck_assert_int_eq(s21_create_matrix(4, 3, &matrix), OK);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_s21_create_matrix_3) {
  matrix_t A = {0};
  int res = s21_create_matrix(2, 3, &A);
  ck_assert_int_eq(A.rows, 2);
  ck_assert_int_eq(A.columns, 3);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_create_matrix_4) {
  matrix_t A = {0};
  int res = s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 3);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_s21_create_matrix_5) {
  matrix_t A = {0};
  int res = s21_create_matrix(0, 3, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_create_matrix_6) {
  matrix_t A = {0};
  int res = s21_create_matrix(3, -3, &A);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_create_matrix_7) {
  int code = 0;
  matrix_t matrix = {0};
  code = s21_create_matrix(1, 1, &matrix);
  s21_remove_matrix(&matrix);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_s21_create_matrix_8) {
  matrix_t matrix = {0};
  int res = s21_create_matrix(3, -3, &matrix);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_create_matrix_9) {
  matrix_t matrix = {0};
  int res = s21_create_matrix(15, 0, &matrix);
  ck_assert_int_eq(res, 1);
}
END_TEST

// s21_eq_matrix

START_TEST(test_s21_eq_matrix_1) {
  double count = 1.0;
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count;
      count = count + 1.0;
    }
  }
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_2) {
  double count = 1.0;
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 1, &A);
  s21_create_matrix(3, 1, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count;
      count = count + 1.0;
    }
  }
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_3) {
  double count = 1.0;
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count;
      count = count + 1.0;
    }
  }
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 1);
  B.matrix[2][2] += 0.0000009;
  res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_4) {
  double count = 1.0;
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count + 1.0;
      count = count + 1.0;
    }
  }
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_5) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 1, &A);
  s21_create_matrix(3, 3, &B);
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_eq_matrix_7) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &matrix2);
  int count = 1;
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      matrix1.matrix[y][x] = count;
      matrix2.matrix[y][x] = count;
      count++;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), SUCCESS);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(test_s21_eq_matrix_8) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  s21_create_matrix(3, 2, &matrix1);
  s21_create_matrix(2, 2, &matrix2);
  int count = 1;
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      matrix1.matrix[y][x] = count;
      matrix2.matrix[y][x] = count;
      count++;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(test_s21_eq_matrix_9) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  s21_create_matrix(2, 3, &matrix1);
  s21_create_matrix(2, 2, &matrix2);
  int count = 1;
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      matrix1.matrix[y][x] = count;
      matrix2.matrix[y][x] = count;
      count++;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(test_s21_eq_matrix_10) {
  matrix_t matrix1 = {0};
  matrix_t matrix2 = {0};
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &matrix2);
  int count = 1;
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 2; x++) {
      matrix1.matrix[y][x] = count;
      matrix2.matrix[y][x] = count;
      count++;
    }
  }
  matrix1.matrix[0][0] = 100;
  ck_assert_int_eq(s21_eq_matrix(&matrix1, &matrix2), FAILURE);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&matrix2);
}
END_TEST

// // sum_matrix
START_TEST(test_s21_sum_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 1, &A);
  s21_create_matrix(3, 3, &B);

  int res = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_sum_matrix_2) {
  double count = 1.0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &C);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count;
      C.matrix[i][j] = A.matrix[i][j] + B.matrix[i][j];
      count = count + 1.0;
    }
  }

  int res = s21_sum_matrix(&A, &B, &D);
  int res_eq = s21_eq_matrix(&C, &D);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res_eq, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

// // // sub_matrix

START_TEST(test_s21_sub_matrix_1) {
  double count = 1.0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &C);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = count;
      C.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
      count = count + 1.0;
    }
  }

  int res = s21_sub_matrix(&A, &B, &D);
  int res_eq = s21_eq_matrix(&C, &D);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res_eq, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(test_s21_sub_matrix_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 1, &A);
  s21_create_matrix(3, 3, &B);

  int res = s21_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// // s21_mult_number

START_TEST(test_s21_mult_number_1) {
  double number = 2.0;
  double count = 1.0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[i][j] = A.matrix[i][j] * number;
      count = count + 1.0;
    }
  }

  int res = s21_mult_number(&A, number, &C);
  int res_eq = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res_eq, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_s21_mult_number_2) {
  const int rows = 2;
  const int cols = 2;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 1;
  m.matrix[1][0] = 1;
  m.matrix[1][1] = 1;
  check.matrix[0][0] = 2;
  check.matrix[0][1] = 2;
  check.matrix[1][0] = 2;
  check.matrix[1][1] = 2;
  int num = 2;
  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_number(&m, num, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), 1);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

// // s21_mult_matri

START_TEST(test_s21_mult_matrix_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(1, 3, &A);
  s21_create_matrix(4, 1, &B);
  s21_create_matrix(1, 1, &C);

  int res = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_s21_mult_matrix_3) {
  double count = 1.0;
  double count2 = 3.0;
  matrix_t A;
  matrix_t B;
  matrix_t C;
  matrix_t D;
  s21_create_matrix(1, 3, &A);
  s21_create_matrix(3, 1, &B);
  s21_create_matrix(1, 1, &C);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[j][i] = count2;
      count = count + 1.0;
      count2 = count2 - 1.0;
    }
  }
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      for (int k = 0; k < B.rows; k++) {
        C.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
      }
    }
  }

  int res = s21_mult_matrix(&A, &B, &D);
  // int res_eq = s21_eq_matrix(&C, &D);
  ck_assert_int_eq(res, 0);
  // ck_assert_int_eq(res_eq, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

// s21_transpose
START_TEST(test_s21_transpose_1) {
  double count = 1.0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = count;
      B.matrix[j][i] = count;
      count = count + 1.0;
    }
  }

  int res = s21_transpose(&A, &C);
  int res_eq = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(res_eq, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_s21_transpose_2) {
  const int rows = 2;
  const int cols = 2;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t check = {0};
  s21_create_matrix(cols, rows, &check);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[1][0] = 3;
  m.matrix[1][1] = 4;
  check.matrix[0][0] = 1;
  check.matrix[0][1] = 3;
  check.matrix[1][0] = 2;
  check.matrix[1][1] = 4;
  matrix_t res = {0};
  ck_assert_int_eq(s21_transpose(&m, &res), 0);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), 1);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

// // calc_complements
START_TEST(test_s21_calc_complements_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(B.matrix[0][0], 0);
  ck_assert_int_eq(B.matrix[0][1], 10);
  ck_assert_int_eq(B.matrix[0][2], -20);
  ck_assert_int_eq(B.matrix[1][0], 4);
  ck_assert_int_eq(B.matrix[1][1], -14);
  ck_assert_int_eq(B.matrix[1][2], 8);
  ck_assert_int_eq(B.matrix[2][0], -8);
  ck_assert_int_eq(B.matrix[2][1], -2);
  ck_assert_int_eq(B.matrix[2][2], 4);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_calc_complements_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 3;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 8;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 2;

  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(B.matrix[0][0], -12);
  ck_assert_int_eq(B.matrix[0][1], 20);
  ck_assert_int_eq(B.matrix[0][2], -2);
  ck_assert_int_eq(B.matrix[1][0], 0);
  ck_assert_int_eq(B.matrix[1][1], 0);
  ck_assert_int_eq(B.matrix[1][2], 0);
  ck_assert_int_eq(B.matrix[2][0], 12);
  ck_assert_int_eq(B.matrix[2][1], -20);
  ck_assert_int_eq(B.matrix[2][2], 2);
  ck_assert_int_eq(res, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_s21_calc_complements_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 1, &A);

  int res = s21_calc_complements(&A, &B);
  ck_assert_int_eq(res, 2);
  s21_remove_matrix(&A);
}
END_TEST

// determinant
START_TEST(test_s21_determinant_1) {
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &matrix1);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 4;
  matrix1.matrix[1][1] = 5;
  matrix1.matrix[1][2] = 6;
  matrix1.matrix[2][0] = 7;
  matrix1.matrix[2][1] = 8;
  matrix1.matrix[2][2] = 9;

  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), EXCEPTION_CALL);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_determinant_3) {
  double determinant = 0;
  matrix_t matrix = {NULL, 0, 0};
  matrix_t matrix2 = {NULL, 0, 0};

  s21_create_matrix(4, 4, &matrix);
  s21_create_matrix(1, 1, &matrix2);

  matrix.matrix[0][0] = 9;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 2;
  matrix.matrix[0][3] = 4;

  matrix.matrix[1][0] = 3;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 4;
  matrix.matrix[1][3] = 4;

  matrix.matrix[2][0] = 4;
  matrix.matrix[2][1] = 4;
  matrix.matrix[2][2] = 9;
  matrix.matrix[2][3] = 9;

  matrix.matrix[3][0] = 1;
  matrix.matrix[3][1] = 1;
  matrix.matrix[3][2] = 5;
  matrix.matrix[3][3] = 1;

  int result = s21_determinant(&matrix, &determinant);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(determinant, -578);

  matrix2.matrix[0][0] = 10;
  result = s21_determinant(&matrix2, &determinant);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(determinant, 10);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&matrix2);
}
END_TEST

START_TEST(test_s21_determinant_4) {
  matrix_t matrix1 = {0};
  s21_create_matrix(3, 3, &matrix1);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 4;
  matrix1.matrix[1][1] = 5;
  matrix1.matrix[1][2] = 6;
  matrix1.matrix[2][0] = 7;
  matrix1.matrix[2][1] = 8;
  matrix1.matrix[2][2] = 9;

  double determinant = 0;
  int status = s21_determinant(&matrix1, &determinant);
  ck_assert_ldouble_eq_tol(determinant, 0, EPSILON);
  ck_assert_int_eq(status, OK);
  s21_remove_matrix(&matrix1);
}

END_TEST

START_TEST(test_s21_determinant_5) {
  matrix_t matrix1 = {0};
  s21_create_matrix(1, 1, &matrix1);

  matrix1.matrix[0][0] = 10;

  double determinant = 0;

  int status = s21_determinant(&matrix1, &determinant);
  ck_assert_ldouble_eq_tol(determinant, 10, EPSILON);
  ck_assert_int_eq(status, OK);
  s21_remove_matrix(&matrix1);
}

END_TEST

START_TEST(test_s21_determinant_6) {
  matrix_t matrix1 = {0};
  s21_create_matrix(2, 2, &matrix1);

  matrix1.matrix[0][0] = 3;
  matrix1.matrix[0][1] = 4;
  matrix1.matrix[1][0] = 2;
  matrix1.matrix[1][1] = 5;

  double determinant = 0;
  int status = s21_determinant(&matrix1, &determinant);
  ck_assert_ldouble_eq_tol(determinant, 7, EPSILON);
  ck_assert_int_eq(status, OK);
  s21_remove_matrix(&matrix1);
}

END_TEST

START_TEST(test_s21_determinant_7) {
  matrix_t matrix1 = {0};
  s21_create_matrix(4, 4, &matrix1);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 5;
  matrix1.matrix[0][2] = 6;
  matrix1.matrix[0][3] = 7;
  matrix1.matrix[1][0] = -3;
  matrix1.matrix[1][1] = 4;
  matrix1.matrix[1][2] = 6;
  matrix1.matrix[1][3] = 7;
  matrix1.matrix[2][0] = 9;
  matrix1.matrix[2][1] = 10;
  matrix1.matrix[2][2] = 24;
  matrix1.matrix[2][3] = 8;
  matrix1.matrix[3][0] = -5;
  matrix1.matrix[3][1] = 8;
  matrix1.matrix[3][2] = 4;
  matrix1.matrix[3][3] = 5;

  double determinant = 0;
  int status = s21_determinant(&matrix1, &determinant);
  ck_assert_ldouble_eq_tol(determinant, -2830, EPSILON);
  ck_assert_int_eq(status, OK);
  s21_remove_matrix(&matrix1);
}

END_TEST

START_TEST(test_s21_determinant_8) {
  matrix_t matrix1 = {0};
  s21_create_matrix(2, 3, &matrix1);
  double det = 0;

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 0;
  matrix1.matrix[1][1] = 4;
  matrix1.matrix[1][2] = 2;
  ck_assert_int_eq(s21_determinant(&matrix1, &det), EXCEPTION_CALL);
  s21_remove_matrix(&matrix1);
}

END_TEST

// inverse_matrix

START_TEST(test_s21_inverse_matrix_1) {
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(3, 3, &matrix1);
  s21_create_matrix(3, 3, &test_result);

  matrix1.matrix[0][0] = 2;
  matrix1.matrix[0][1] = 5;
  matrix1.matrix[0][2] = 7;
  matrix1.matrix[1][0] = 6;
  matrix1.matrix[1][1] = 3;
  matrix1.matrix[1][2] = 4;
  matrix1.matrix[2][0] = 5;
  matrix1.matrix[2][1] = -2;
  matrix1.matrix[2][2] = -3;

  test_result.matrix[0][0] = 1;
  test_result.matrix[0][1] = -1;
  test_result.matrix[0][2] = 1;
  test_result.matrix[1][0] = -38;
  test_result.matrix[1][1] = 41;
  test_result.matrix[1][2] = -34;
  test_result.matrix[2][0] = 27;
  test_result.matrix[2][1] = -29;
  test_result.matrix[2][2] = 24;

  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), OK);

  for (int y = 0; y < result.rows; y++) {
    for (int x = 0; x < result.columns; x++) {
      ck_assert_ldouble_lt(fabs(result.matrix[y][x] - test_result.matrix[y][x]),
                           EPSILON);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

END_TEST

START_TEST(test_s21_inverse_matrix_3) {
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(2, 2, &matrix1);
  s21_create_matrix(2, 2, &test_result);

  matrix1.matrix[0][0] = 2;
  matrix1.matrix[0][1] = 7;
  matrix1.matrix[1][0] = 4;
  matrix1.matrix[1][1] = -6;

  test_result.matrix[0][0] = 0.15;
  test_result.matrix[0][1] = 0.175;
  test_result.matrix[1][0] = 0.1;
  test_result.matrix[1][1] = -0.05;

  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), OK);

  for (int y = 0; y < result.rows; y++) {
    for (int x = 0; x < result.columns; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPSILON);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}

START_TEST(test_s21_inverse_matrix_4) {
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  matrix_t test_result = {0};
  s21_create_matrix(4, 4, &matrix1);
  s21_create_matrix(4, 4, &test_result);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[0][3] = 3;
  matrix1.matrix[1][0] = 0;
  matrix1.matrix[1][1] = 4;
  matrix1.matrix[1][2] = 2;
  matrix1.matrix[1][3] = 2;
  matrix1.matrix[2][0] = 5;
  matrix1.matrix[2][1] = 2;
  matrix1.matrix[2][2] = 1;
  matrix1.matrix[2][3] = 1;
  matrix1.matrix[3][0] = 1;
  matrix1.matrix[3][1] = 2;
  matrix1.matrix[3][2] = 3;
  matrix1.matrix[3][3] = 4;

  test_result.matrix[0][0] = 0;
  test_result.matrix[0][1] = -0.1;
  test_result.matrix[0][2] = 0.2;
  test_result.matrix[0][3] = 0;
  test_result.matrix[1][0] = -0.25;
  test_result.matrix[1][1] = 0.35;
  test_result.matrix[1][2] = 0.05;
  test_result.matrix[1][3] = 0;
  test_result.matrix[2][0] = 1.5;
  test_result.matrix[2][1] = -0.2;
  test_result.matrix[2][2] = -0.1;
  test_result.matrix[2][3] = -1;
  test_result.matrix[3][0] = -1;
  test_result.matrix[3][1] = 0;
  test_result.matrix[3][2] = 0;
  test_result.matrix[3][3] = 1;
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), OK);
  for (int y = 0; y < result.rows; y++) {
    for (int x = 0; x < result.columns; x++) {
      ck_assert_ldouble_eq_tol(result.matrix[y][x], test_result.matrix[y][x],
                               EPSILON);
    }
  }
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&test_result);
}
END_TEST

START_TEST(test_s21_inverse_matrix_5) {
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &matrix1);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 4;
  matrix1.matrix[1][1] = 5;
  matrix1.matrix[1][2] = 6;
  matrix1.matrix[2][0] = 7;
  matrix1.matrix[2][1] = 8;
  matrix1.matrix[2][2] = 9;

  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), EXCEPTION_CALL);

  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_inverse_matrix_6) {
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  s21_create_matrix(2, 3, &matrix1);

  matrix1.matrix[0][0] = 1;
  matrix1.matrix[0][1] = 2;
  matrix1.matrix[0][2] = 3;
  matrix1.matrix[1][0] = 0;
  matrix1.matrix[1][1] = 4;
  matrix1.matrix[1][2] = 2;
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), EXCEPTION_CALL);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_s21_inverse_matrix_7) {
  matrix_t matrix1 = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 1, &matrix1);

  matrix1.matrix[0][0] = 0;
  ck_assert_int_eq(s21_inverse_matrix(&matrix1, &result), EXCEPTION_CALL);
  s21_remove_matrix(&matrix1);
  s21_remove_matrix(&result);
}
END_TEST

int main() {
  Suite *s1 = suite_create("s21_matrix: ");
  TCase *tc1_1 = tcase_create("s21_matrix: ");
  SRunner *sr = srunner_create(s1);
  int result = 0;
  suite_add_tcase(s1, tc1_1);

  // create_matrix and remove_matrix
  tcase_add_test(tc1_1, test_s21_create_matrix_1);
  tcase_add_test(tc1_1, test_s21_create_matrix_2);
  tcase_add_test(tc1_1, test_s21_create_matrix_3);
  tcase_add_test(tc1_1, test_s21_create_matrix_4);
  tcase_add_test(tc1_1, test_s21_create_matrix_5);
  tcase_add_test(tc1_1, test_s21_create_matrix_6);
  tcase_add_test(tc1_1, test_s21_create_matrix_7);
  tcase_add_test(tc1_1, test_s21_create_matrix_8);
  tcase_add_test(tc1_1, test_s21_create_matrix_9);

  // s21_s21_eq_matrix(сравнение)
  tcase_add_test(tc1_1, test_s21_eq_matrix_1);
  tcase_add_test(tc1_1, test_s21_eq_matrix_2);
  tcase_add_test(tc1_1, test_s21_eq_matrix_3);
  tcase_add_test(tc1_1, test_s21_eq_matrix_4);
  tcase_add_test(tc1_1, test_s21_eq_matrix_5);
  tcase_add_test(tc1_1, test_s21_eq_matrix_7);
  tcase_add_test(tc1_1, test_s21_eq_matrix_8);
  tcase_add_test(tc1_1, test_s21_eq_matrix_9);
  tcase_add_test(tc1_1, test_s21_eq_matrix_10);

  // s21_sum_matrix
  tcase_add_test(tc1_1, test_s21_sum_matrix_1);
  tcase_add_test(tc1_1, test_s21_sum_matrix_2);

  // s21_sub_matrix
  tcase_add_test(tc1_1, test_s21_sub_matrix_1);
  tcase_add_test(tc1_1, test_s21_sub_matrix_2);

  // s21_mult_number
  tcase_add_test(tc1_1, test_s21_mult_number_1);
  tcase_add_test(tc1_1, test_s21_mult_number_2);

  // s21_mult_matrix
  tcase_add_test(tc1_1, test_s21_mult_matrix_1);
  tcase_add_test(tc1_1, test_s21_mult_matrix_3);

  // s21_transpose
  tcase_add_test(tc1_1, test_s21_transpose_1);
  tcase_add_test(tc1_1, test_s21_transpose_2);

  // calc_complements
  tcase_add_test(tc1_1, test_s21_calc_complements_1);
  tcase_add_test(tc1_1, test_s21_calc_complements_2);
  tcase_add_test(tc1_1, test_s21_calc_complements_3);

  // determinant
  tcase_add_test(tc1_1, test_s21_determinant_1);
  tcase_add_test(tc1_1, test_s21_determinant_3);
  tcase_add_test(tc1_1, test_s21_determinant_4);
  tcase_add_test(tc1_1, test_s21_determinant_5);
  tcase_add_test(tc1_1, test_s21_determinant_6);
  tcase_add_test(tc1_1, test_s21_determinant_7);
  tcase_add_test(tc1_1, test_s21_determinant_8);

  // inverse

  tcase_add_test(tc1_1, test_s21_inverse_matrix_1);
  tcase_add_test(tc1_1, test_s21_inverse_matrix_3);
  tcase_add_test(tc1_1, test_s21_inverse_matrix_4);
  tcase_add_test(tc1_1, test_s21_inverse_matrix_5);
  tcase_add_test(tc1_1, test_s21_inverse_matrix_6);
  tcase_add_test(tc1_1, test_s21_inverse_matrix_7);

  srunner_run_all(sr, CK_ENV);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);

  return result == 0 ? 0 : 1;
}
