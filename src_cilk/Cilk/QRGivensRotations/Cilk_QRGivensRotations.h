#ifndef Cilk_QRGIVENSROTATIONS_H_
#define Cilk_QRGIVENSROTATIONS_H_

#include <stdio.h>
#include <math.h>
#include "../MatrixOperation/Cilk_matrixOperation.h"

//#define DEBUG 1;
extern int SIZE;

void Cilk_qrGivensRotations(double ***A);
void Cilk_setMatrixG(double ***G, int i, int j, double c, double s);
void Cilk_givensRotation(double a, double b, double *c, double *s);
void Cilk_givensRotation2(double a, double b, double *c, double *s);

#endif /* Cilk_QRGIVENSROTATIONS_H_ */