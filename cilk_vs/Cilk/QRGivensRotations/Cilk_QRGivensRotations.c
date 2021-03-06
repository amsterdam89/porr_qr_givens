/*
 * QRGivensRotations.c
 *
 *  Created on: Dec 1, 2013
 *      Author: amsterdam
 */

#include "Cilk_QRGivensRotations.h"


void Cilk_QRGivensRotations(double ***A, double ***Q, double ***R) {


	double **G;
	int i, j;
	double c, s;

	Cilk_mallocMatrix(&G);



	cilk_spawn
	Cilk_copyArray(R, A);

	 cilk_spawn Cilk_setEye(Q);
	cilk_sync;



	// Algorytm qr Givens rotations
	for(j=0; j<SIZE; j++) //kolumny
		for(i=SIZE - 1; i > j; i--) { //wiersze


//#pragma omp parallel num_threads(NUM_PROCS_2)
//{
//#pragma omp sections nowait
//	{
//#pragma omp section
//			{
			cilk_spawn
			Cilk_setEye(&G);
			//}
/*#pragma omp section
			{*/
			cilk_spawn Cilk_givensRotation((*R)[i-1][j], (*R)[i][j], &c, &s);
			cilk_sync;
			//}
	//}
//}


			Cilk_setMatrixG(&G, i, j, c, s);



//#pragma omp parallel num_threads(NUM_PROCS_2)
//{
//#pragma omp sections nowait
//		{
//#pragma omp section
//			{
			cilk_spawn
			Cilk_multiplyMatrixToSecondWithTransposition(&G, R);
			//}
//#pragma omp section
//			{
			cilk_spawn Cilk_multiplyMatrixToFirst(Q, &G);
			cilk_sync;
//			}
//		}
//}

		}//END FOR


	Cilk_freeMatrix(&G);


	return;
}

void Cilk_setMatrixG(double ***G, int i, int j, double c, double s) {

	// nie warto zrownoleglac

			(*G)[i-1][i-1] = c;
			(*G)[i][i] = c;
			(*G)[i][i-1] = s;
			(*G)[i-1][i] = -s;

}


void Cilk_givensRotation(double a, double b, double *c, double *s) {

	double r;

	if(b == 0.0 || a == 0.0)
		if(b == 0.0) {
			*c = 1.0;
			*s = 0.0;
		}
		else {
			*c = 0.0;
			*s = 1.0;
		}
	else
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
