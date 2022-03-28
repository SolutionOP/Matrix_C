#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define EPS 0.0000001

typedef enum {
    CORRECT_MATRIX = 0,
    INCORRECT_MATRIX = 1,
    IDENTITY_MATRIX = 2,
    ZERO_MATRIX = 3
} matrix_type_t;


typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
    matrix_type_t matrix_type;
} matrix_t;

matrix_t s21_create_matrix(int rows, int c1olumns);
matrix_t s21_sum_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_sub_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_mult_number(matrix_t *A, double number);
matrix_t s21_mult_matrix(matrix_t *A, matrix_t *B);
matrix_t s21_transpose(matrix_t *A);
matrix_t s21_calc_complements(matrix_t *A);
matrix_t s21_inverse_matrix(matrix_t *A);
double s21_determinant(matrix_t *A);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);

void printMatrix(matrix_t *matrix);
int validMatrix(matrix_t *matrix);
int compareTwoMatrix(matrix_t *matrix1, matrix_t *matrix2);
int isMatrixSquare(matrix_t *matrix);
void compareNInfToZero(matrix_t *matrix);
void checkMatrixType(matrix_t *matrix);
int checkForZeroType(matrix_t *matrix);
int checkForIdentityType(matrix_t *matrix);
matrix_t get_decMatrix(matrix_t *matrix, int countCol, int countRow);
void s21_fill(matrix_t *matrixStruct, double value);

#endif  // SRC_S21_MATRIX_H_
