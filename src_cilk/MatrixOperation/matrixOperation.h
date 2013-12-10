/*
 * matrixOperation.h
 *
 *  Created on: Dec 1, 2013
 *      Author: amsterdam
 */

#ifndef MATRIXOPERATION_H_
#define MATRIXOPERATION_H_

#include <stdio.h>
#include <stdlib.h>

extern int SIZE;

void mallocMatrix(double ***A);
void freeMatrix(double ***A);
void printMatrix(double ***A, char *s);
void printMatrixDiagonal(double ***A, char *s);

void copyArray(double *** R, double ***A);
void setEye(double ***A);
void transposition(double ***A);
void multiplyMatrixToSecondWithTransposition(double *** A, double ***B);
void multiplyMatrixToFirst(double *** A, double ***B);
void multiplyMatrix(double *** A, double ***B, double ***tmp);

#endif /* MATRIXOPERATION_H_ */





