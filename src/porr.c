/*
 ============================================================================
 Name        : porr.c
 Author      : lmetrak
 Version     :
 Copyright   : Your copyright notice
 Description : Projekt porr in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include "FileReader/FileReader.h"
#include "QRGivensRotations/QRGivensRotations.h"
#include "MatrixOperation/matrixOperation.h"

extern void QRGivensRotations(double ***A);

int M, N; //ilość wierszy i kolumn macierzy


int main(int argc, char *argv[]) {

	double **A;
    char *path = NULL;
    char *name = NULL;

	argc = 2; //TODO

	if(loadArguments(argc, argv, path, name) ) {

		path = "/home/amsterdam/workspace/porr_file.txt"; //TODO

		if(loadData(path, &A)) {

			//printf("wartosc macierzy = %f\n", A[2][2]);

			QRGivensRotations(&A); //TODO error in algorithm
			//TODO jeszcze wymnożyć i zwrócić Q i R


			freeMatrix(&A);
			return EXIT_SUCCESS;
		}

	}

	return EXIT_FAILURE;
}
