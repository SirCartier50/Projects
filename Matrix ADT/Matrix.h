/***
 * Author: Mignot Mesele
 * mmesele
 * 2023 Fall CSE101 PA{4}
 * Title: Matrix.h
 * Purpose: Matrix ADT header
 * ***/
#ifndef MATRIX_H_INCLUDE
#define MATRIX_H_INCLUDE

#include"List.h"

typedef struct MatrixObj* Matrix;

/*constructor*/

Matrix newMatrix(int n);

/*deconstructor*/
void freeMatrix(Matrix* pM);

/*Acess functions*/
int size(Matrix M);
int NNZ(Matrix M);
int equals(Matrix A, Matrix B);

/*Manipulation procedures*/
void makeZero(Matrix M);
void changeEntry(Matrix M, int i, int j, double x);

/*Arithmetic operations*/
Matrix copy(Matrix A);
Matrix transpose(Matrix A);
Matrix scalarMult(double x, Matrix A);
Matrix sum(Matrix A, Matrix B);
Matrix diff(Matrix A, Matrix B);
Matrix product(Matrix A, Matrix B);
/*diagnostics*/
void printMatrix(FILE* out, Matrix M);

#endif
