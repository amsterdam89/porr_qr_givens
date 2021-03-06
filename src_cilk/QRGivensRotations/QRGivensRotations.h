/*
 * QRGivensRotations.h
 *
 *  Created on: Dec 1, 2013
 *      Author: amsterdam
 */

#ifndef QRGIVENSROTATIONS_H_
#define QRGIVENSROTATIONS_H_

#include <math.h>
#include "../MatrixOperation/matrixOperation.h"

extern int SIZE;

void QRGivensRotations(double ***A, double ***Q, double ***R);
void setMatrixG(double ***G, int i, int j, double c, double s);
void givensRotation(double a, double b, double *c, double *s);
void givensRotation2(double a, double b, double *c, double *s);

#endif /* QRGIVENSROTATIONS_H_ */
