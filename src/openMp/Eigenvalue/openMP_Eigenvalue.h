/*
 * Eigenvalue.h
 *
 *  Created on: Dec 9, 2013
 *      Author: amsterdam
 */

#ifndef openMP_EIGENVALUE_H_
#define openMP_EIGENVALUE_H_

#include <stdio.h>
#include <stdlib.h>

#include "../../bool.h"
#include "../MatrixOperation/openMP_matrixOperation.h"
#include "../QRGivensRotations/openMP_QRGivensRotations.h"

extern int SIZE;
extern int MAX_ITER;
extern double EPSILON;

void openMP_getEignvalues(double ***A);
bool openMP_isDiagonal(double ***A, double epsilon);

#endif /* openMP_EIGENVALUE_H_ */
