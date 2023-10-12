#include "s21_matrix.h"

// Создание матриц

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int flag = SUCCESS;
  result->matrix = NULL;  // Зануляем матрицу
  if (rows > 0 && columns > 0) {
    result->matrix = (double **)malloc(rows * sizeof(double));
    if (result->matrix != NULL) {
      flag = FAILURE;
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)malloc(columns * sizeof(double));
      }
    }
    result->rows = rows;
    result->columns = columns;
  }
  return flag;
}

// Очистка матриц

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
}

// Сравнение матриц
//Совпадают их размеры и соответствующие элементы равны

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS;
  if (A == NULL || A->matrix == NULL || B == NULL || B->matrix == NULL ||
      A->rows != B->rows || A->columns != B->columns || A->rows <= 0 ||
      A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    flag = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPSILON) {
          flag = FAILURE;
          break;
        }
      }
    }
  }
  return flag;
}

// Сложение
//Суммой двух матриц определятся равенством C(i,j) = A(i,j) + B(i,j)

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int STATUS = OK;

  if (STATUS == OK) {
    if ((A->columns == B->columns) && (A->rows == B->rows)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      STATUS = EXCEPTION_CALL;
    }
  }
  return STATUS;
}

// вычитание матриц
//Разницой двух матриц определятся равенством C(i,j) = A(i,j) - B(i,j)
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int STATUS = OK;
  if (STATUS == OK) {
    if ((A->columns == B->columns) && (A->rows == B->rows)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      STATUS = EXCEPTION_CALL;
    }
  }
  return STATUS;
}

// Умножение матрицы на число
//Произведением матрицы это равенствщ B = λ × A(i,j)

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int STATUS = OK;
  if (STATUS == OK) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else {
    STATUS = EXCEPTION;
  }
  return OK;
}

//  Умножение двух матриц
// пример как должно быть C(1,1) = A(1,1) × B(1,1) + A(1,2) × B(2,1)

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int STATUS = OK;
  if (STATUS == OK) {
    if (B->rows == A->columns) {
      s21_create_matrix(A->rows, B->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      STATUS = EXCEPTION_CALL;
    }
  }
  return STATUS;
}

//Транспонирование матрицы
//Транспонирование матрицы А заключается в замене строк этой матрицы ее
//столбцами с сохранением их номеров.

int s21_transpose(matrix_t *A, matrix_t *result) {
  int STATUS = OK;
  if (STATUS == OK) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return STATUS;
}

//Определитель матрицы
//Определитель матрицы равен сумме произведений
//элементов строки (столбца) на соответствующие алгебраические дополнения.

int s21_determinant(matrix_t *A, double *result) {
  int STATUS = OK;
  if (STATUS == OK) {
    if (A->rows == A->columns) {
      *result = s21_get_determinant(A);
    } else {
      STATUS = EXCEPTION_CALL;
    }
  }
  return STATUS;
}

//вычисляет определитель и записывает его в переменную `result`
double s21_get_determinant(matrix_t *A) {
  double result = 0;
  if (A->rows == 1) {
    result = A->matrix[0][0];
  } else {
    matrix_t tmp = {0};
    s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
    for (int i = 0; i < A->columns; i++) {
      s21_get_calc(0, i, A, &tmp);  //вычисляем минор
      if (i % 2) {
        result -= A->matrix[0][i] * s21_get_determinant(&tmp);
      } else {
        result += A->matrix[0][i] * s21_get_determinant(&tmp);
      }
    }
    s21_remove_matrix(&tmp);
  }
  return result;
}

//Вычисляются размерности матрицы
//Копируются элементы исходной матрицы во временную, за исключением строки и
//столбца, соответствующих переданным координатам.

void s21_get_calc(int rows, int columns, matrix_t *A, matrix_t *result) {
  int crows = 0;
  int ccolumns = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == rows) {
      continue;
    }
    ccolumns = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == columns) {
        continue;
      }
      result->matrix[crows][ccolumns] = A->matrix[i][j];
      ccolumns++;
    }
    crows++;
  }
}

//Минор матрицы и матрица алгебраических дополнений
//Минором M(i,j) называется определитель (n-1)-го порядка, полученный
//вычёркиванием из матрицы A i-й строки и j-го столбца.
//знак каждого элемента зависит от расположения столбца и строки
//поэтому используется функция pow для вычисления выражения (-1)^(i+j).

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int STATUS = OK;
  if (STATUS == OK) {
    if (A->rows == A->columns) {
      s21_create_matrix(A->columns, A->rows, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t calc = {0};
          double determinant = 0;
          s21_create_matrix(A->columns - 1, A->rows - 1, &calc);
          s21_get_calc(i, j, A, &calc);
          s21_determinant(&calc, &determinant);
          result->matrix[i][j] = pow(-1, (i + j)) * determinant;
          s21_remove_matrix(&calc);
        }
      }
    } else {
      STATUS = EXCEPTION_CALL;
    }
  }
  return STATUS;
}

//инверсия

int s21_inverse_matrix(matrix_t *A,
                       matrix_t *result) {  // поиск обратной матрицы
  int STATUS = OK;
  if ((A == NULL && A->matrix == NULL) || (A->rows < 0 && A->columns < 0)) {
    STATUS = EXCEPTION;
  } else if (A->rows != A->columns) {
    STATUS = EXCEPTION_CALL;
  } else {
    double det = 0;
    s21_determinant(A, &det);
    if (fabs(det) > 1e-7) {
      matrix_t tempM1, tempM2;
      s21_calc_complements(A, &tempM1);
      s21_transpose(&tempM1, &tempM2);
      s21_remove_matrix(&tempM1);
      s21_mult_number(&tempM2, 1.0 / det, result);
      s21_remove_matrix(&tempM2);
    } else {
      STATUS = EXCEPTION_CALL;
    }
  }
  return STATUS;
}