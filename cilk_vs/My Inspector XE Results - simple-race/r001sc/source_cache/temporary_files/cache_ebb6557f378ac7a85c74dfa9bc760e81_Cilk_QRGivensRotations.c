/*
 * QRGivensRotations.c
 *
 *  Created on: Dec 1, 2013
 *      Author: amsterdam
 */

#include "Cilk_QRGivensRotations.h"

void Cilk_QRGivensRotations(double ***A) {


	double **Q, **R, **G;
	int i, j;
	double c, s;


	Cilk_mallocMatrix(&Q);
			

	Cilk_mallocMatrix(&R);
			

	Cilk_mallocMatrix(&G);




	Cilk_copyArray(&R, A);
			

	Cilk_setEye(&Q);
			



	// Algorytm qr Givens rotations
	for(j=0; j<SIZE; j++) //kolumny
		for(i=SIZE - 1; i > j; i--) { //wiersze

			// #mozna zrownoleglic dwie instrukcje


			Cilk_setEye(&G);
			Cilk_givensRotation(R[i-1][j], R[i][j], &c, &s);
	



			Cilk_setMatrixG(&G, i, j, c, s);


			// #mozna zrownoleglic dwie instrukcje ponizej
			//#pragma omp sections default(shared) private(c,s)



			Cilk_multiplyMatrixToSecondWithTransposition(&G, &R);
			

			Cilk_multiplyMatrixToFirst(&Q, &G);

}


			//printMatrix(&Q, "Q");
			//printMatrix(&R, "R");
			//printf("------END---LOOP-----\n");
		

	Cilk_printMatrix(&Q," Q ROZWIAZANIE  ");
	Cilk_printMatrix(&R," R ROZWIAZANIE  ");

	// #mozna zrownoleglic 3 instrukcje


			Cilk_freeMatrix(&Q);
			Cilk_freeMatrix(&R);
			Cilk_freeMatrix(&G);


	return;
}

void Cilk_setMatrixG(double ***G, int i, int j, double c, double s) {

	// mozna by było zrownoleglic cztery ponizsze instrukcje lecz nie ma to sensu

			(*G)[i-1][i-1] = c;
			(*G)[i][i] = c;
			(*G)[i][i-1] = s;
			(*G)[i-1][i] = -s;

}


void Cilk_givensRotation(double a, double b, double *c, double *s) {

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

void Cilk_givensRotation2(double a, double b, double *c, double *s) {

	//mozna by bylo zrownoleglic lecz nie zalecane numerycznie jest takie liczenie (przekręcenie się licznika)
	double r;
    r = sqrt(a*a + b*b);
    //mozna zrownoleglic dwie ponizsze instrukcje
    *c = a/r;
    *s = b/r;
}
