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
	for (i = 0; i < SIZE; i++)
		(*A)[i] = malloc(SIZE * sizeof *(*A)[i]);
}

void openMP_freeMatrix(double ***A) {
	int i;

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

//#pragma omp parallel for shared(A, R, SIZE) private(i,j)  schedule(dynamic)
	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++) {
			(*R)[i][j] = (*A)[i][j];

		}
}

void openMP_setEye(double ***A) {
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

void openMP_setZeros(double ***A) {
	// obowiazkowe
	//mozna zrownoleglic fora
	int i, j;

//#pragma omp parallel for shared(A, SIZE) private(i,j) schedule(dynamic)
	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++)
				(*A)[i][j] = 0.0;
}

void openMP_transposition(double ***A) {
	//mozna zrownoleglic fora
	int i, j;
	double **tmp;

	openMP_mallocMatrix(&tmp);

//#pragma omp parallel for shared(tmp, A, SIZE) private(i,j) schedule(dynamic)
	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++) {
			tmp[j][i] = (*A)[i][j];
		}

	openMP_freeMatrix(A);
	*A = tmp;

}

void openMP_multiplyMatrix(double *** A, double ***B, double ***tmp) {
	//mozna zrownoleglic fora
	//  reduction(+:tmp)

	int i;//, j, k;




#pragma omp parallel num_threads(8)  private(i) //shared(A, B,tmp)
	{
#pragma omp for schedule(dynamic, SIZE/8)
	for (i=0; i < SIZE; i++) {

		 double*  Arow = (*A)[i];
		//double*  Crow = (*tmp)[i];
		 int j;

//1		 #pragma omp parallel num_threads(8) shared(tmp)
//1		 {
//1 #pragma omp for private(j) schedule(auto) nowait //reduction(+:sum)
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


/*
#pragma omp parallel for shared(tmp) private(i,j,k) num_threads(2) schedule(auto) //reduction(+: tab )
	for(i=0; i<SIZE; i++)
		for(j=0; j<SIZE; j++)
			for(k=0; k<SIZE; k++)
				//tab[i][j] = tab[i][j] + ( (*A)[i][k] * (*B)[k][j] );
				(*tmp)[i][j] += ( (*A)[i][k] * (*B)[k][j] );
*/



}

void openMP_multiplyMatrixToSecondWithTransposition(double *** A, double ***B) {
	// R = G'*R;
	double **tmp, **tmpTranspositionMatrix;

	openMP_mallocMatrix(&tmp);
	openMP_mallocMatrix(&tmpTranspositionMatrix);
	openMP_setZeros(&tmp);

	openMP_copyArray(&tmpTranspositionMatrix, A);
	//openMP_printMatrix(&tmpTranspositionMatrix, "macierz przede transpozycja");
	openMP_transposition(&tmpTranspositionMatrix);
	//openMP_printMatrix(&tmpTranspositionMatrix, "macierz po transpozycja");

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
