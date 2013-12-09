/*
 * QRGivensRotations.h
 *
 *  Created on: Dec 1, 2013
 *      Author: amsterdam
 */

#ifndef openMP_QRGIVENSROTATIONS_H_
#define openMP_QRGIVENSROTATIONS_H_

#include <stdio.h>
#include <math.h>
#include "../MatrixOperation/openMP_matrixOperation.h"

#define DEBUG 1;
extern int SIZE;
extern int NUM_PROCS_2, NUM_PROCS_3;

void openMP_qrGivensRotations(double ***A);
void openMP_setMatrixG(double ***G, int i, int j, double c, double s);
void openMP_givensRotation(double a, double b, double *c, double *s);
void openMP_givensRotation2(double a, double b, double *c, double *s);

#endif /* openMP_QRGIVENSROTATIONS_H_ */
