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
	printMatrix(&R, "R");
	setEye(&Q);
	printMatrix(&Q, "Q");


	// Algorytm qr Givens rotations
	for(j=0; j<N; j++) //kolumny
		for(i=j+1; i<M; i++) { //wiersze
		//for(j=M-1; j>i; j--) { //wiersze
			setEye(&G);
			givensRotation2(R[i-1][j], R[i][j], &c, &s);
			//givensRotation2(R[j-1][i], R[j][i], &c, &s);

			setMatrixG(&G, i, j, c, s);
			printMatrix(&G, "G");
			multiplyMatrixToSecondWithTransposition(&G, &R);
			// R = G'*R;
			multiplyMatrixToFirst(&Q, &G);
			// Q = Q*G;
			printMatrix(&Q, "Q");
			printMatrix(&R, "R");

		}



	printMatrix(&Q," Q ");
	printMatrix(&R," R ");
	freeMatrix(&Q);
	freeMatrix(&R);
	freeMatrix(&G);

	return;
}

void setMatrixG(double ***G, int i, int j, double c, double s) {

	(*G)[i-1][j] = c;
	(*G)[i][j] = -s;
	(*G)[i-1][j+1] = s;
	(*G)[i][j+1] = c;

}


void givensRotation(double a, double b, double *c, double *s) {

	double r;

	  if(b == 0) {
		    *c = 1.0;
		    *s = 0.0;
	  }
	  else {
		    if(abs(b) > abs(a)) {
		      r = a / b;
		      *s = 1 / sqrt(1 + r*r);
		      *c = *s*r;
		    }
		    else {
		    	r = b / a;
		    	*c = 1 / sqrt(1 + r*r);
		    	*s = *c*r;
		    }
	  }
}

void givensRotation2(double a, double b, double *c, double *s) {

	double r;
    r = sqrt(a*a + b*b);
    *c = a/r;
    *s = b/r;
}
