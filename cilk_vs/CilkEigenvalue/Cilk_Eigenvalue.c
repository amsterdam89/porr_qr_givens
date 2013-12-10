#include "Cilk_Eigenvalue.h"

void Cilk_getEignvalues(double ***A) {

	double **Q, **R, **copyA;
	int i;


	Cilk_mallocMatrix(&Q);
	Cilk_mallocMatrix(&R);
	Cilk_mallocMatrix(&copyA);

	Cilk_copyArray(&copyA, A);


	for(i = 0; i < MAX_ITER; i++) {

		Cilk_QRGivensRotations(&copyA, &Q, &R);

		if(Cilk_isDiagonal(&copyA, EPSILON))
			break;

		Cilk_setZeros(&copyA);
		Cilk_multiplyMatrix(&R, &Q, &copyA);

	}

	Cilk_printMatrixDiagonal(&copyA, " A po QR rotacjami givensa w cilk");


	Cilk_freeMatrix(&Q);
	Cilk_freeMatrix(&R);
	Cilk_freeMatrix(&copyA);

}

bool Cilk_isDiagonal(double ***A, double epsilon) {

	int i, j;
	for(i = 0; i < SIZE; i++)
		for(j = i; j < SIZE; j++)
			if( abs( (*A)[i][j] ) > epsilon )
				return false;

	return true;

}