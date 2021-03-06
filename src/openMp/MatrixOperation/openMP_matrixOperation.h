/*
 * matrixOperation.h
 *
 *  Created on: Dec 1, 2013
 *      Author: amsterdam
 */

#ifndef openMP_MATRIXOPERATION_H_
#define openMP_MATRIXOPERATION_H_

#include <stdio.h>
#include <stdlib.h>

extern int SIZE;
extern int NUM_PROCS;

void openMP_mallocMatrix(double ***A);
void openMP_freeMatrix(double ***A);
void openMP_printMatrix(double ***A, char *s);
void openMP_printMatrixDiagonal(double ***A, char *s);

void openMP_copyArray(double *** R, double ***A);
void openMP_setEye(double ***A);
void openMP_setZeros(double ***A);
void openMP_transposition(double ***A);
void openMP_multiplyMatrixToSecondWithTransposition(double *** A, double ***B);
void openMP_multiplyMatrixToFirst(double *** A, double ***B);
void openMP_multiplyMatrix(double *** A, double ***B, double ***tmp);

#endif /* openMP_MATRIXOPERATION_H_ */





