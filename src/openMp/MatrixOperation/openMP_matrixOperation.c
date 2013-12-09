/*
 * matrixOperation.c
 *
 *  Created on: Dec 1, 2013
 *      Author: amsterdam
 */
#include "openMP_matrixOperation.h"

void openMP_mallocMatrix(double ***A) {
	int i;

	*A =  malloc(SIZE * sizeof *(*A));

	// nie warto zrownoleglac
	for (i = 0; i < SIZE; i++)
		(*A)[i] = malloc(SIZE * sizeof *(*A)[i]);
}

void openMP_freeMatrix(double ***A) {
	int i;

	// nie warto zrownoleglac
    for (i = 0; i < SIZE; i++)
    	free((*A)[i]);

    free(*A);
}

void openMP_printMatrix(double ***A, char *s) {
	int i, j;

	printf("wartosc macierzy %s\n", s);
	for(i=0; i<SIZE; i++) {
		for(j=0; j<SIZE; j++) {;
			printf("\t%f", (*A)[i][j]);
		}
		printf("\n");
	}

}

void openMP_copyArray(double *** R, double ***A) {
	//mozna zrownoleglic fora
	int i, j;

#pragma omp parallel num_threads(NUM_PROCS)  private(i,j) shared(A, R)
	{
#pragma omp for schedule(dynamic, SIZE/NUM_PROCS)
	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++) {
			(*R)[i][j] = (*A)[i][j];

		}
	}
}

void openMP_setEye(double ***A) {
	//mozna zrownoleglic fora
	int i, j;


#pragma omp parallel num_threads(NUM_PROCS)  private(i,j) shared(A)
	{
#pragma omp for schedule(dynamic, SIZE/NUM_PROCS)
	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++)
			if(i == j)
				(*A)[i][j] = 1.0;
			else
				(*A)[i][j] = 0.0;
	}
}

void openMP_setZeros(double ***A) {
	// obowiazkowe
	//mozna zrownoleglic fora
	int i, j;

#pragma omp parallel num_threads(NUM_PROCS)  private(i,j) shared(A)
	{
#pragma omp for schedule(dynamic, SIZE/NUM_PROCS)
	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++)
				(*A)[i][j] = 0.0;
	}
}

void openMP_transposition(double ***A) {
	//mozna zrownoleglic fora
	int i, j;
	double **tmp;

	openMP_mallocMatrix(&tmp);

#pragma omp parallel num_threads(NUM_PROCS)  private(i,j) shared(A,tmp)
	{
#pragma omp for schedule(dynamic, SIZE/NUM_PROCS)
	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++) {
			tmp[j][i] = (*A)[i][j];
		}
	}

	openMP_freeMatrix(A);
	*A = tmp;

}

void openMP_multiplyMatrix(double *** A, double ***B, double ***tmp) {

	int i;

#pragma omp parallel num_threads(NUM_PROCS)  private(i)
	{
#pragma omp for schedule(dynamic, SIZE/NUM_PROCS)
	for (i=0; i < SIZE; i++) {

		 double*  Arow = (*A)[i];
		 int j;

		for (j=0; j < SIZE; j++) {

			double sum = 0.0;
			int k;

			for(k=0;k < SIZE ;k++)
				sum += Arow[k] * (*B)[k][j];

			(*tmp)[i][j] = sum;
	  }
	}
}


}

void openMP_multiplyMatrixToSecondWithTransposition(double *** A, double ***B) {
	// R = G'*R;
	double **tmp, **tmpTranspositionMatrix;

	// zrownoleglanie nie przynosi korzysci
	openMP_mallocMatrix(&tmp);
	openMP_mallocMatrix(&tmpTranspositionMatrix);

	openMP_setZeros(&tmp);
	openMP_copyArray(&tmpTranspositionMatrix, A);

	openMP_transposition(&tmpTranspositionMatrix);
	openMP_multiplyMatrix(&tmpTranspositionMatrix, B, &tmp);

	openMP_freeMatrix(B);
	openMP_freeMatrix(&tmpTranspositionMatrix);


	*B = tmp;

}

void openMP_multiplyMatrixToFirst(double *** A, double ***B) {
	// Q = Q*G;
	double **tmp;
	openMP_mallocMatrix(&tmp);
	openMP_setZeros(&tmp);

	openMP_multiplyMatrix(A, B, &tmp);

	openMP_freeMatrix(A);
	*A = tmp;
}
