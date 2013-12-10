/*
 * Eigenvalue.c
 *
 *  Created on: Dec 9, 2013
 *      Author: amsterdam
 */

#include "Eigenvalue.h"

void getEignvalues(double ***A) {

	double **Q, **R, **copyA;
	int i;


	mallocMatrix(&Q);
	mallocMatrix(&R);
	mallocMatrix(&copyA);

	copyArray(&copyA, A);


	for(i = 0; i < MAX_ITER; i++) {

		QRGivensRotations(&copyA, &Q, &R);

		if(isDiagonal(&copyA, EPSILON))
			break;

		setZeros(&copyA);
		multiplyMatrix(&R, &Q, &copyA);

	}

	printMatrixDiagonal(&copyA, " A po QR rotacjami givensa");


	freeMatrix(&Q);
	freeMatrix(&R);
	freeMatrix(&copyA);

}



bool isDiagonal(double ***A, double epsilon) {

	int i, j;
	for(i = 0; i < SIZE; i++)
		for(j = i; j < SIZE; j++)
			if( abs( (*A)[i][j] ) > epsilon )
				return false;

	return true;

}
