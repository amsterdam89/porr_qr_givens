/*
 * Eigenvalue.c
 *
 *  Created on: Dec 9, 2013
 *      Author: amsterdam
 */

#include "openMP_Eigenvalue.h"

void openMP_getEignvalues(double ***A) {

	double **Q, **R, **copyA;
	int i;

	openMP_printMatrix(A, " A ");

	openMP_mallocMatrix(&Q);
	openMP_mallocMatrix(&R);
	openMP_mallocMatrix(&copyA);


	openMP_copyArray(&copyA, A);


	for(i = 0; i < MAX_ITER; i++) {

		openMP_QRGivensRotations(&copyA, &Q, &R);

		if(openMP_isDiagonal(&copyA, EPSILON))
			break;

		openMP_setZeros(&copyA);
		openMP_multiplyMatrix(&R, &Q, &copyA);

	}

	openMP_printMatrixDiagonal(&copyA, " A po QR rotacjami givensa");


	openMP_freeMatrix(&Q);
	openMP_freeMatrix(&R);
	openMP_freeMatrix(&copyA);

}

bool openMP_isDiagonal(double ***A, double epsilon) {

	int i, j;
	for(i = 0; i < SIZE; i++)
		for(j = i; j < SIZE; j++)
			if( abs( (*A)[i][j] ) > epsilon )
				return false;

	return true;

}
