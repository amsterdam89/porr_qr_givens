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
	for (i = 0; i < SIZE; i++)
		(*A)[i] = malloc(SIZE * sizeof *(*A)[i]);
}

void Cilk_freeMatrix(double ***A) {
	int i;

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

//#pragma omp parallel for shared(A, R, SIZE) private(i,j)  schedule(dynamic)
	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++) {
			(*R)[i][j] = (*A)[i][j];

		}
}

void Cilk_setEye(double ***A) {
	//mozna zrownoleglic fora
	int i, j;

//#pragma omp parallel for shared(A, SIZE) private(i,j) schedule(dynamic)
	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++)
			if(i == j)
				(*A)[i][j] = 1.0;
			else
				(*A)[i][j] = 0.0;
}

void Cilk_setZeros(double ***A) {
	// obowiazkowe
	//mozna zrownoleglic fora
	int i, j;

//#pragma omp parallel for shared(A, SIZE) private(i,j) schedule(dynamic)
	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++)
				(*A)[i][j] = 0.0;
}

void Cilk_transposition(double ***A) {
	//mozna zrownoleglic fora
	int i, j;
	double **tmp;

	Cilk_mallocMatrix(&tmp);

//#pragma omp parallel for shared(tmp, A, SIZE) private(i,j) schedule(dynamic)
	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++) {
			tmp[j][i] = (*A)[i][j];
		}

	Cilk_freeMatrix(A);
	*A = tmp;

}

void Cilk_multiplyMatrix(double *** A, double ***B, double ***tmp) {

	
	

	int i;//, j, k;




/*2#pragma omp parallel num_threads(8)  private(i) //shared(A, B,tmp)
	{
#pragma omp for schedule(dynamic, SIZE/8)*/
	//cilk_
		for (i=0; i < SIZE; i++) {

		 double*  Arow = (*A)[i];
		//double*  Crow = (*tmp)[i];
		 int j;


		for (j=0; j < SIZE; j++) {



			//double* Bcol = B;
			double sum = 0.0;
			int k;
			for(k=0;k < SIZE ;k++) {
				sum += Arow[k] * (*B)[k][j]; //C(i,j)=sum(over k) A(i,k)*B(k,j)
			}
			(*tmp)[i][j] = sum;
	    //Crow[j] = sum;
	  }
	}
//1	}
}






//2}

void Cilk_multiplyMatrixToSecondWithTransposition(double *** A, double ***B) {
	// R = G'*R;
	double **tmp, **tmpTranspositionMatrix;

	Cilk_mallocMatrix(&tmp);
	Cilk_mallocMatrix(&tmpTranspositionMatrix);
	Cilk_setZeros(&tmp);

	Cilk_copyArray(&tmpTranspositionMatrix, A);
	//Cilk_printMatrix(&tmpTranspositionMatrix, "macierz przede transpozycja");
	Cilk_transposition(&tmpTranspositionMatrix);
	//Cilk_printMatrix(&tmpTranspositionMatrix, "macierz po transpozycja");

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
