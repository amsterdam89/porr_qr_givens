/*
 * QRGivensRotations.c
 *
 *  Created on: Dec 1, 2013
 *      Author: amsterdam
 */

#include "openMP_QRGivensRotations.h"

void openMP_QRGivensRotations(double ***A) {


	double **Q, **R, **G;
	int i, j;
	double c, s;

#pragma omp parallel num_threads(3)
{
	#pragma omp sections nowait
	{
#pragma omp section
			{
	openMP_mallocMatrix(&Q);
			}
#pragma omp section
			{
	openMP_mallocMatrix(&R);
			}
#pragma omp section
			{
	openMP_mallocMatrix(&G);
			}
	}
}

#pragma omp parallel num_threads(2)
{
	#pragma omp sections nowait
	{
#pragma omp section
			{
	openMP_copyArray(&R, A);
			}
#pragma omp section
			{
	openMP_setEye(&Q);
			}
	}
}


	// Algorytm qr Givens rotations
	for(j=0; j<SIZE; j++) //kolumny
		for(i=SIZE - 1; i > j; i--) { //wiersze

			// #mozna zrownoleglic dwie instrukcje
#pragma omp parallel num_threads(2)
{
	#pragma omp sections nowait
	{
			openMP_setEye(&G);
			openMP_givensRotation(R[i-1][j], R[i][j], &c, &s);
	}
}


			openMP_setMatrixG(&G, i, j, c, s);


			// #mozna zrownoleglic dwie instrukcje ponizej
			//#pragma omp sections default(shared) private(c,s)

#pragma omp parallel num_threads(2)
{
	#pragma omp sections
		{
#pragma omp section
			{
			openMP_multiplyMatrixToSecondWithTransposition(&G, &R);
			}
#pragma omp section
			{
			openMP_multiplyMatrixToFirst(&Q, &G);
			}
		}
}


			//printMatrix(&Q, "Q");
			//printMatrix(&R, "R");
			//printf("------END---LOOP-----\n");
		}

	openMP_printMatrix(&Q," Q ROZWIAZANIE  ");
	openMP_printMatrix(&R," R ROZWIAZANIE  ");

	// #mozna zrownoleglic 3 instrukcje

	#pragma omp parallel num_threads(3)
	{
		#pragma omp sections
		{
			openMP_freeMatrix(&Q);
			openMP_freeMatrix(&R);
			openMP_freeMatrix(&G);
		}
	}

	return;
}

void openMP_setMatrixG(double ***G, int i, int j, double c, double s) {

	// mozna by było zrownoleglic cztery ponizsze instrukcje lecz nie ma to sensu

			(*G)[i-1][i-1] = c;
			(*G)[i][i] = c;
			(*G)[i][i-1] = s;
			(*G)[i-1][i] = -s;

}


void openMP_givensRotation(double a, double b, double *c, double *s) {

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

void openMP_givensRotation2(double a, double b, double *c, double *s) {

	//mozna by bylo zrownoleglic lecz nie zalecane numerycznie jest takie liczenie (przekręcenie się licznika)
	double r;
    r = sqrt(a*a + b*b);
    //mozna zrownoleglic dwie ponizsze instrukcje
    *c = a/r;
    *s = b/r;
}
