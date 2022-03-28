#include "s21_matrix.h"

/**
 * @brief Создание матрицы забитой нулями
 *
 * @param rows Количество рядов
 * @param columns Количество колонок
 * @return matrix_t Возвращает матрицу
 */
matrix_t s21_create_matrix(int rows, int columns) {
    matrix_t matrix;
    matrix.rows = rows;
    matrix.columns = columns;
    if ((rows > 0) && (columns > 0)) {
        matrix.matrix = calloc(rows, sizeof(double *));
        for (int i = 0; i < matrix.rows; i++) {
            matrix.matrix[i] = calloc(columns, sizeof(double));
        }
        matrix.matrix_type = ZERO_MATRIX;
    } else {
        matrix.matrix_type = INCORRECT_MATRIX;
    }
    return matrix;
}

/**
 * @brief Сравнение двух матриц
 *
 * @param A Первая матрица
 * @param B Вторая матрица
 * @return result Возвращает успех или провал сравнения (SUCCESS (1) или FAILURE (0) соответственно)
 */
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int result = SUCCESS;
    if (validMatrix(A) && validMatrix(B) && compareTwoMatrix(A, B)) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS * fabs(B->matrix[i][j])) {
                    result = FAILURE;
                }
            }
        }
    } else {
        result = FAILURE;
    }

    return result;
}

/**
 * @brief Складывает две матрицы
 *
 * @param A Первая матрица
 * @param B Вторая матрица
 * @return matrix_t Итоговая матрица
 */
matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B) {
    matrix_t resultMatrix = s21_create_matrix(A->rows, A->columns);
    if (validMatrix(A) && validMatrix(B) && compareTwoMatrix(A, B)) {
        // resultMatrix = s21_create_matrix(A->rows, A->columns);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                resultMatrix.matrix[i][j] = (A->matrix[i][j] + B->matrix[i][j]);
            }
        }
        resultMatrix.matrix_type = CORRECT_MATRIX;
        checkMatrixType(&resultMatrix);
    } else {
        resultMatrix.matrix_type = INCORRECT_MATRIX;
    }
    return resultMatrix;
}

/**
 * @brief Вычитает две матрицы
 *
 * @param A Первая матрица
 * @param B Вторая матрица
 * @return matrix_t Готовую матрицу
 */
matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B) {
    matrix_t resultMatrix = s21_create_matrix(A->rows, A->columns);
    if (validMatrix(A) && validMatrix(B) && compareTwoMatrix(A, B)) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                resultMatrix.matrix[i][j] = (A->matrix[i][j] - B->matrix[i][j]);
            }
        }
        resultMatrix.matrix_type = CORRECT_MATRIX;
        checkMatrixType(&resultMatrix);
    } else {
        resultMatrix.matrix_type = INCORRECT_MATRIX;
    }
    return resultMatrix;
}

/**
 * @brief Умножает матрицу на определенное число
 *
 * @param A Матрица
 * @param number Число, на которое нужно умножить матрицу
 * @return matrix_t Возвращает готовую матрицу
 */
matrix_t s21_mult_number(matrix_t *A, double number) {
    matrix_t resultMatrix = s21_create_matrix(A->rows, A->columns);
    if (validMatrix(A)) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                resultMatrix.matrix[i][j] = (A->matrix[i][j] * number);
            }
        }
        resultMatrix.matrix_type = CORRECT_MATRIX;
        checkMatrixType(&resultMatrix);
    } else {
        resultMatrix.matrix_type = INCORRECT_MATRIX;
    }
    return resultMatrix;
}

/**
 * @brief Умножает матрицу на другую матрицу
 *
 * @param A Первая матрица
 * @param B Вторая матрица
 * @return matrix_t Возвращает готовую матрицу
 */
matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B) {
    matrix_t resultMatrix = s21_create_matrix(A->rows, B->columns);
    if ((A->columns == B->rows) && validMatrix(A) && validMatrix(B)) {
        for (int i = 0; i < resultMatrix.rows; i++) {
            for (int j = 0; j < resultMatrix.columns; j++) {
                double mul = 0;
                for (int k = 0; k < A->columns; k++) {
                    mul += A->matrix[i][k] * B->matrix[k][j];
                }
                resultMatrix.matrix[i][j] = mul;
            }
        }
        resultMatrix.matrix_type = CORRECT_MATRIX;
        checkMatrixType(&resultMatrix);
    } else {
        resultMatrix.matrix_type = INCORRECT_MATRIX;
    }
    return resultMatrix;
}

/**
 * @brief Очистка матрицы
 *
 * @param A Матрица
 */
void s21_remove_matrix(matrix_t *A) {
    for (int i = 0; i < A->rows; i++)
        if (A->matrix) free(A->matrix[i]);
    if (A->matrix) free(A->matrix);
}

/**
 * @brief Транспонирование матрицы
 *
 * @param A Матрица
 * @return matrix_t Возвращает готовую матрицу
 */
matrix_t s21_transpose(matrix_t *A) {
    matrix_t resultMatrix = s21_create_matrix(A->columns, A->rows);
    if (validMatrix(A)) {
        resultMatrix.columns = A->rows;
        resultMatrix.rows = A->columns;
        for (int i = 0; i < resultMatrix.rows; i++) {
            for (int j = 0; j < resultMatrix.columns; j++) {
                resultMatrix.matrix[i][j] = A->matrix[j][i];
            }
        }
        resultMatrix.matrix_type = CORRECT_MATRIX;
        checkMatrixType(&resultMatrix);
    } else {
        resultMatrix.matrix_type = INCORRECT_MATRIX;
    }
    return resultMatrix;
}

/**
 * @brief Создает матрицу алгебраических дополнений
 *
 * @param A Матрица
 * @return matrix_t Возвращает готовую матрицу
 */
matrix_t s21_calc_complements(matrix_t *A) {
    matrix_t resultMatrix = s21_create_matrix(A->rows, A->columns);
    if (validMatrix(A) && isMatrixSquare(A)) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                matrix_t decrMatrix = get_decMatrix(A, i, j);
                resultMatrix.matrix[i][j] = pow(-1, i + j) * s21_determinant(&decrMatrix);
                s21_remove_matrix(&decrMatrix);
            }
        }
        resultMatrix.matrix_type = CORRECT_MATRIX;
        checkMatrixType(&resultMatrix);
    } else {
        resultMatrix.matrix_type = INCORRECT_MATRIX;
    }
    return resultMatrix;
}

/**
 * @brief Находит детерминант
 *
 * @param A Матрица
 * @return double Детерминант
 */
double s21_determinant(matrix_t *A) {
    double determ = 0.0;
    if (validMatrix(A) && isMatrixSquare(A)) {
        if (A->rows == 1) determ = A->matrix[0][0];
        if (A->rows == 2) {
            determ = (A->matrix[0][0] * A->matrix[1][1]) - (A->matrix[0][1] * A->matrix[1][0]);
        }
        if (A->rows > 2) {
            for (int i = 0; i < A->rows; i++) {
                matrix_t decrMatrix = get_decMatrix(A, i, 0);
                determ += A->matrix[i][0] * pow(-1, i) * s21_determinant(&decrMatrix);
                s21_remove_matrix(&decrMatrix);
            }
        }
    } else {
        determ = NAN;
    }
    return determ;
}

/**
 * @brief Создает инверсированную матрицу
 *
 * @param A Матрица
 * @return matrix_t Возвращает готовую матрицу
 */
matrix_t s21_inverse_matrix(matrix_t *A) {
    matrix_t invMatrix;
    double determ = s21_determinant(A);
    if (fabs(determ) > 1e-7) {
        matrix_t minorM = s21_calc_complements(A);
        matrix_t transpM = s21_transpose(&minorM);
        s21_remove_matrix(&minorM);
        invMatrix = s21_mult_number(&transpM, 1 / determ);
        s21_remove_matrix(&transpM);
        compareNInfToZero(&invMatrix);
    } else {
        invMatrix.matrix_type = INCORRECT_MATRIX;
    }
    return invMatrix;
}

/**
 * @brief Приводит -INF к 0
 *
 * @param matrix Матрица
 */
void compareNInfToZero(matrix_t *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            if (1 / matrix->matrix[i][j] == -INFINITY) {
                matrix->matrix[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Получает обрезанную матрицу
 *
 * @param matrix Матрица
 * @param countCol Сдвиг колонок
 * @param countRow Сдвиг строк
 * @return matrix_t Возвращает готовую матрицу
 */
matrix_t get_decMatrix(matrix_t *matrix, int countCol, int countRow) {
    matrix_t decrMatrix = s21_create_matrix(matrix->rows - 1, matrix->columns - 1);
    for (int i = 0, a = 0; i < matrix->rows; i++) {
        if (countCol != i) {
            for (int j = 0, b = 0; j < matrix->rows; j++) {
                if (countRow != j) {
                    decrMatrix.matrix[a][b] = matrix->matrix[i][j];
                    b++;
                }
            }
            a++;
        }
    }
    return decrMatrix;
}

/**
 * @brief Вспомогательная функция для распечатки матрицы
 *
 * @param matrix Матрица
 */
void printMatrix(matrix_t *matrix) {
    if (matrix->matrix_type != INCORRECT_MATRIX) {
        for (int i = 0; i < matrix->rows; i++) {
            for (int j = 0; j < matrix->columns; j++) {
                printf("%lf ", matrix->matrix[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("Incorrect matrix");
    }
}

/**
 * @brief Вспомогательная функция для проверки матрицы на валидность
 *
 * @param matrix Матрица
 * @return result Результат
 */
int validMatrix(matrix_t *matrix) {
    int result = FAILURE;
    if ((matrix != NULL) && (matrix->matrix != NULL) && (matrix->matrix_type != INCORRECT_MATRIX) &&
        (matrix->rows > 0) && (matrix->columns > 0)) {
        result = SUCCESS;
    }
    return result;
}

/**
 * @brief Вспомогательная функция для сравнения двух матриц
 *
 * @param matrix1 Первая матрица
 * @param matrix2 Вторая матрица
 * @return result Результат
 */
int compareTwoMatrix(matrix_t *matrix1, matrix_t *matrix2) {
    int result = FAILURE;
    if (matrix1->rows == matrix2->rows && matrix1->columns == matrix2->columns) {
        result = SUCCESS;
    }
    return result;
}

/**
 * @brief Вспомогательная функция для проверки является ли матрица квадратной
 *
 * @param matrix Матрица
 * @return result Результат
 */
int isMatrixSquare(matrix_t *matrix) {
    int result = FAILURE;
    if (matrix->rows == matrix->columns) {
        result = SUCCESS;
    }
    return result;
}

/**
 * @brief Проверка и установка типа матрицы
 *
 * @param matrix Матрица
 */
void checkMatrixType(matrix_t *matrix) {
    if (validMatrix(matrix)) {
        matrix->matrix_type = CORRECT_MATRIX;
        if (checkForZeroType(matrix)) {
            matrix->matrix_type = ZERO_MATRIX;
        } else if (checkForIdentityType(matrix)) {
            matrix->matrix_type = IDENTITY_MATRIX;
        }
    } else {
        matrix->matrix_type = INCORRECT_MATRIX;
    }
}

/**
 *
 * @brief Проверка на нулевую матрицу
 *
 * @param matrix Матрица
 * @return int Возвращает результат проверки
 */
int checkForZeroType(matrix_t *matrix) {
    int result = SUCCESS;
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            if (fabs(matrix->matrix[i][j]) > 0) {
                result = FAILURE;
                break;
            }
        }
    }
    return result;
}

/**
 * @brief Проверка на единичную матрицу
 *
 * @param matrix Матрица
 * @return int Возвращает результат проверки
 */
int checkForIdentityType(matrix_t *matrix) {
    int result = SUCCESS;
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->columns; j++) {
            if ((i == j && fabs(matrix->matrix[i][j] - 1) > 1e-7) ||
                (i != j && fabs(matrix->matrix[i][j]) > 1e-7)) {
                result = FAILURE;
                break;
            }
        }
    }
    return result;
}

/**
 * @brief Заполняет матрицу одинаковыми значениями
 *
 * @param matrixStruct Матрица
 * @param value Значение
 */
void s21_fill(matrix_t *matrixStruct, double value) {
    for (int i = 0; i < matrixStruct->rows; i++) {
        for (int j = 0; j < matrixStruct->columns; j++) {
            matrixStruct->matrix[i][j] = value;
        }
    }
    checkMatrixType(matrixStruct);
}
