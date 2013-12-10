/*
 * Eigenvalue.h
 *
 *  Created on: Dec 9, 2013
 *      Author: amsterdam
 */

#ifndef CILK_EIGENVALUE_H_
#define CILK_EIGENVALUE_H_

#include <stdio.h>

#include "../bool.h"
#include "../Cilk/MatrixOperation/Cilk_matrixOperation.h"
#include "../Cilk/QRGivensRotations/Cilk_QRGivensRotations.h"

extern int SIZE;
extern int MAX_ITER;
extern double EPSILON;


void Cilk_getEignvalues(double ***A);
bool isDiagonal(double ***A, double epsilon);

#endif /* CILK_EIGENVALUE_H_ */
