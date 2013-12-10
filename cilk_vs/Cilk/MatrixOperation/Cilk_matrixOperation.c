/*
 * matrixOperation.c
 *
 *  Created on: Dec 1, 2013
 *      Author: amsterdam
 */
#include "Cilk_matrixOperation.h"

void Cilk_mallocMatrix(double ***A) {
	int i;

	*A =  malloc(SIZE * sizeof *(*A));

	// nie warto zrownoleglac
	for (i = 0; i < SIZE; i++)
		(*A)[i] = malloc(SIZE * sizeof *(*A)[i]);
}

void Cilk_freeMatrix(double ***A) {
	int i;

	// nie warto zrownoleglac
    for (i = 0; i < SIZE; i++)
    	free((*A)[i]);

    free(*A);
}

void Cilk_printMatrix(double ***A, char *s) {
	int i, j;

	printf("wartosc macierzy %s\n", s);
	for(i=0; i<SIZE; i++) {
		for(j=0; j<SIZE; j++) {;
			printf("\t%f", (*A)[i][j]);
		}
		printf("\n");
	}

}

void Cilk_printMatrixDiagonal(double ***A, char *s) {
	int i;

	printf("wartosc diagonali macierzy %s\n", s);
	for(i=0; i<SIZE; i++)
			printf("\t%f\n", (*A)[i][i]);
		printf("\n");

}

void Cilk_copyArray(double *** R, double ***A) {
	//mozna zrownoleglic fora
	int i, j;

//#pragma omp parallel num_threads(NUM_PROCS)  private(i,j) shared(A, R)
//	{
//#pragma omp for schedule(dynamic, SIZE/NUM_PROCS)
	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++) {
			(*R)[i][j] = (*A)[i][j];

		}
//	}
}

void Cilk_setEye(double ***A) {
	//mozna zrownoleglic fora
	int i, j;

//
//#pragma omp parallel num_threads(NUM_PROCS)  private(i,j) shared(A)
//	{
//#pragma omp for schedule(dynamic, SIZE/NUM_PROCS)
	//cilk_spawn
	cilk_for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++)
			if(i == j)
				(*A)[i][j] = 1.0;
			else
				(*A)[i][j] = 0.0;
	//cilk_sync;
	}
//}

void Cilk_setZeros(double ***A) {
	// obowiazkowe
	//mozna zrownoleglic fora
	int i, j;

//#pragma omp parallel num_threads(NUM_PROCS)  private(i,j) shared(A)
//	{
//#pragma omp for schedule(dynamic, SIZE/NUM_PROCS)
	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++)
				(*A)[i][j] = 0.0;
//	}
}

void Cilk_transposition(double ***A) {
	//mozna zrownoleglic fora
	int i, j;
	double **tmp;

	Cilk_mallocMatrix(&tmp);

//#pragma omp parallel num_threads(NUM_PROCS)  private(i,j) shared(A,tmp)
//	{
//#pragma omp for schedule(dynamic, SIZE/NUM_PROCS)
	//cilk_spawn
	cilk_for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++) {
			tmp[j][i] = (*A)[i][j];
		}
		//cilk_sync;
	//}

	Cilk_freeMatrix(A);
	*A = tmp;

}

void Cilk_multiplyMatrix(double *** A, double ***B, double ***tmp) {

	int i;

//#pragma omp parallel num_threads(NUM_PROCS) shared(A,B,tmp) private(i)
//	{
//#pragma omp for schedule(dynamic, SIZE/NUM_PROCS)
	for (i=0; i < SIZE; i++) {

		 double*  Arow = (*A)[i];
		 int j;

		cilk_for (j=0; j < SIZE; j++) {

			double sum = 0.0;
			int k;

			for(k=0;k < SIZE ;k++)
				sum += Arow[k] * (*B)[k][j];

			(*tmp)[i][j] = sum;
	  }
//	}
}


}

void Cilk_multiplyMatrixToSecondWithTransposition(double *** A, double ***B) {
	// R = G'*R;
	double **tmp, **tmpTranspositionMatrix;

	// zrownoleglanie nie przynosi korzysci
	Cilk_mallocMatrix(&tmp);
	Cilk_mallocMatrix(&tmpTranspositionMatrix);

	Cilk_setZeros(&tmp);
	Cilk_copyArray(&tmpTranspositionMatrix, A);

	Cilk_transposition(&tmpTranspositionMatrix);
	Cilk_multiplyMatrix(&tmpTranspositionMatrix, B, &tmp);

	Cilk_freeMatrix(B);
	Cilk_freeMatrix(&tmpTranspositionMatrix);


	*B = tmp;

}

void Cilk_multiplyMatrixToFirst(double *** A, double ***B) {
	// Q = Q*G;
	double **tmp;
	Cilk_mallocMatrix(&tmp);
	Cilk_setZeros(&tmp);

	Cilk_multiplyMatrix(A, B, &tmp);

	Cilk_freeMatrix(A);
	*A = tmp;
}
