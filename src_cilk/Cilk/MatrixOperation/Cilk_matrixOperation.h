#ifndef Cilk_MATRIXOPERATION_H_
#define Cilk_MATRIXOPERATION_H_

#include <stdio.h>
#include <stdlib.h>
#include <cilk/cilk.h>

extern int SIZE;

void Cilk_mallocMatrix(double ***A);
void Cilk_freeMatrix(double ***A);
void Cilk_printMatrix(double ***A, char *s);
void printMatrixDiagonal(double ***A, char *s);

void Cilk_copyArray(double *** R, double ***A);
void Cilk_setEye(double ***A);
void Cilk_transposition(double ***A);
void Cilk_multiplyMatrixToSecondWithTransposition(double *** A, double ***B);
void Cilk_multiplyMatrixToFirst(double *** A, double ***B);

#endif /* Cilk_MATRIXOPERATION_H_ */