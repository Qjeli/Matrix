#ifndef SRC_MATRIX_S21_MATRIX_H_
#define SRC_MATRIX_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0

#define EXCEPTION_CALL 2
#define EXCEPTION 1
#define OK 0

/* - 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
 * нельзя провести вычисления и т.д.)*/
// - 1 - Ошибка, некорректная матрица
// - 0 - OK

#define EPSILON 0.0000001  // точность сравнения

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B,
                   matrix_t *result);  //вычитание матриц (sub_matrix)
int s21_mult_number(matrix_t *A, double number,
                    matrix_t *result);  //умножение матрицы на число
int s21_mult_matrix(matrix_t *A, matrix_t *B,
                    matrix_t *result);  // умножение матрица на матрицу
int s21_transpose(matrix_t *A,
                  matrix_t *result);  // Транспонирование матрицы (transpose)
int s21_determinant(
    matrix_t *A, double *result);  //Определитель матрицы равен сумме
                                   //произведений элементов строки (столбца) на
                                   //соответствующие алгебраические дополнения.

int s21_calc_complements(
    matrix_t *A,
    matrix_t *result);  // Минор матрицы и матрица алгебраических дополнений
double s21_get_determinant(
    matrix_t *A);  // Дополнительные функции к детерминанту.
void s21_get_calc(int rows, int columns, matrix_t *A, matrix_t *result);

int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif
