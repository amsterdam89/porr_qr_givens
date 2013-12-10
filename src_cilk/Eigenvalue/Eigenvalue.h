/*
 * Eigenvalue.h
 *
 *  Created on: Dec 9, 2013
 *      Author: amsterdam
 */

#ifndef EIGENVALUE_H_
#define EIGENVALUE_H_

#include <stdio.h>

#include "../bool.h"
#include "../MatrixOperation/matrixOperation.h"
#include "../QRGivensRotations/QRGivensRotations.h"

extern int SIZE;
extern int MAX_ITER;
extern double EPSILON;

void getEignvalues(double ***A);
bool isDiagonal(double ***A, double epsilon);

#endif /* EIGENVALUE_H_ */
