/*
 * matrixOperation.c
 *
 *  Created on: Dec 1, 2013
 *      Author: amsterdam
 */
#include "matrixOperation.h"

void mallocMatrix(double ***A) {
	int i;

	*A =  malloc(M * sizeof *(*A));
	for (i = 0; i < M; i++)
		(*A)[i] = malloc(N * sizeof *(*A)[i]);
}

void mallocMatrixReverse(double ***A) {
	int i;

	*A =  malloc(N * sizeof *(*A));
	for (i = 0; i < N; i++)
		(*A)[i] = malloc(M * sizeof *(*A)[i]);
}

void freeMatrix(double ***A) {
	int i;

    for (i = 0; i < M; i++)
    	free((*A)[i]);
    free(*A);
}

void freeMatrixReverse(double ***A) {
	int i;

    for (i = 0; i < N; i++)
    	free((*A)[i]);
    free(*A);
}

void printMatrix(double ***A, char *s) {
	int i, j;

	printf("wartosc macierzy %s\n", s);
	for(i=0; i<M; i++) {
		for(j=0; j<N; j++) {;
			printf("\t%f", (*A)[i][j]);
		}
		printf("\n");
	}

}

void printMatrixReverse(double ***A, char *s) {
	int i, j;

	printf("wartosc macierzy %s\n", s);
	for(i=0; i<N; i++) {
		for(j=0; j<M; j++) {;
			printf("\t%f", (*A)[i][j]);
		}
		printf("\n");
	}

}

void copyArray(double *** R, double ***A) {
	int i, j;

	for(i=0; i<M; i++)
		for(j=0; j<N; j++) {
			(*R)[i][j] = (*A)[i][j];

		}
}

void setEye(double ***A) {
	int i, j;

	for(i=0; i<M; i++)
		for(j=0; j<N; j++)
			if(i == j)
				(*A)[i][j] = 1.0;
			else
				(*A)[i][j] = 0.0;
}

void transposition(double ***A) {
	int i, j;
	double **tmp;

	mallocMatrixReverse(&tmp);

	for(i=0; i<M; i++)
		for(j=0; j<N; j++) {
			tmp[j][i] = (*A)[i][j];
		}

	freeMatrix(A);
	*A = tmp;

}

void multiplyMatrixToSecondWithTransposition(double *** A, double ***B) {
	int i, j, k;
	double **tmp, **tmpTranspositionMatrix;

	mallocMatrix(&tmp);
	mallocMatrix(&tmpTranspositionMatrix);

	copyArray(&tmpTranspositionMatrix, A);
	//printMatrix(&tmpTranspositionMatrix, "macierz przede transpozycja");
	transposition(&tmpTranspositionMatrix);
	//printMatrixReverse(&tmpTranspositionMatrix, "macierz po transpozycji");

	for(i=0; i<M; i++)
		for(j=0; j<N; j++)
			for(k=0; k<N; k++) {
				tmp[i][j] += tmpTranspositionMatrix[i][k] * (*B)[k][j];
			}

	freeMatrix(B);
	freeMatrixReverse(&tmpTranspositionMatrix);
	*B = tmp;

}

void multiplyMatrixToFirst(double *** A, double ***B) {
	int i, j, k;
	double **tmp;

	mallocMatrix(&tmp);

	for(i=0; i<M; i++)
		for(j=0; j<N; j++)
			for(k=0; k<N; k++) {
				tmp[i][j] += (*A)[i][k] * (*B)[k][j];
			}

	freeMatrix(A);
	*A = tmp;

}
