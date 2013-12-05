/*
 * matrixOperation.c
 *
 *  Created on: Dec 1, 2013
 *      Author: amsterdam
 */
#include "matrixOperation.h"

void mallocMatrix(double ***A) {
	int i;

	*A =  malloc(SIZE * sizeof *(*A));
	for (i = 0; i < SIZE; i++)
		(*A)[i] = malloc(SIZE * sizeof *(*A)[i]);
}

void freeMatrix(double ***A) {
	int i;

    for (i = 0; i < SIZE; i++)
    	free((*A)[i]);
    free(*A);
}

void printMatrix(double ***A, char *s) {
	int i, j;

	printf("wartosc macierzy %s\n", s);
	for(i=0; i<SIZE; i++) {
		for(j=0; j<SIZE; j++) {;
			printf("\t%f", (*A)[i][j]);
		}
		printf("\n");
	}

}

void copyArray(double *** R, double ***A) {
	//mozna zrownoleglic fora
	int i, j;

	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++) {
			(*R)[i][j] = (*A)[i][j];

		}
}

void setEye(double ***A) {
	//mozna zrownoleglic fora
	int i, j;

	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++)
			if(i == j)
				(*A)[i][j] = 1.0;
			else
				(*A)[i][j] = 0.0;
}

void setZeros(double ***A) {
	// obowiazkowe
	//mozna zrownoleglic fora
	int i, j;

	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++)
				(*A)[i][j] = 0.0;
}

void transposition(double ***A) {
	//mozna zrownoleglic fora
	int i, j;
	double **tmp;

	mallocMatrix(&tmp);

	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++) {
			tmp[j][i] = (*A)[i][j];
		}

	freeMatrix(A);
	*A = tmp;

}

void multiplyMatrix(double *** A, double ***B, double ***tmp) {
	//mozna zrownoleglic fora
	int i, j, k;


	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++)
			for(k=0; k<SIZE; k++) {
				(*tmp)[i][j] += ( (*A)[i][k] * (*B)[k][j] );
			}
}

void multiplyMatrixToSecondWithTransposition(double *** A, double ***B) {

	double **tmp, **tmpTranspositionMatrix;

	mallocMatrix(&tmp);
	mallocMatrix(&tmpTranspositionMatrix);
	setZeros(&tmp);

	copyArray(&tmpTranspositionMatrix, A);
	printMatrix(&tmpTranspositionMatrix, "macierz przede transpozycja");
	transposition(&tmpTranspositionMatrix);
	printMatrix(&tmpTranspositionMatrix, "macierz po transpozycja");

	multiplyMatrix(&tmpTranspositionMatrix, B, &tmp);

	freeMatrix(B);
	freeMatrix(&tmpTranspositionMatrix);
	*B = tmp;

}

void multiplyMatrixToFirst(double *** A, double ***B) {

	double **tmp;
	mallocMatrix(&tmp);
	setZeros(&tmp);

	multiplyMatrix(A, B, &tmp);

	freeMatrix(A);
	*A = tmp;
}
