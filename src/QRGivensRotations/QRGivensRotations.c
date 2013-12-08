/*
 * QRGivensRotations.c
 *
 *  Created on: Dec 1, 2013
 *      Author: amsterdam
 */

#include "QRGivensRotations.h"

void QRGivensRotations(double ***A) {

	double **Q, **R, **G;
	int i, j;
	double c, s;

	mallocMatrix(&Q);
	mallocMatrix(&R);
	mallocMatrix(&G);

	copyArray(&R, A);
	setEye(&Q);


	// Algorytm qr Givens rotations
	for(j=0; j<SIZE; j++) //kolumny
		for(i=SIZE - 1; i > j; i--) { //wiersze

			// #mozna zrownoleglic dwie instrukcje
			setEye(&G);
			givensRotation(R[i-1][j], R[i][j], &c, &s);

			setMatrixG(&G, i, j, c, s);

			// #mozna zrownoleglic dwie instrukcje ponizej
			multiplyMatrixToSecondWithTransposition(&G, &R);
			multiplyMatrixToFirst(&Q, &G);

		}

	//printMatrix(&Q," Q ROZWIAZANIE");
	//printMatrix(&R," R ROZWIAZANIE");

	// #mozna zrownoleglic 3 instrukcje
	freeMatrix(&Q);
	freeMatrix(&R);
	freeMatrix(&G);

	return;
}

void setMatrixG(double ***G, int i, int j, double c, double s) {

	// mozna zrownoleglic cztery ponizsze instrukcje
	(*G)[i-1][i-1] = c;
	(*G)[i][i-1] = s;
	(*G)[i-1][i] = -s;
	(*G)[i][i] = c;

}


void givensRotation(double a, double b, double *c, double *s) {

	double r;

	if(abs(b) > abs(a)) {
	  r = a / b;
	  *s = 1.0 / sqrt(1.0 + r*r);
	  *c = (*s)*r;
	}
	else {
		r = b / a;
		*c = 1.0 / sqrt(1.0 + r*r);
		*s = (*c)*r;
	}
}

void givensRotation2(double a, double b, double *c, double *s) {

	//mozna by bylo zrownoleglic lecz nie zalecane numerycznie jest takie liczenie (przekręcenie się licznika)
	double r;
    r = sqrt(a*a + b*b);
    //mozna zrownoleglic dwie ponizsze instrukcje
    *c = a/r;
    *s = b/r;
}
