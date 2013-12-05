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

int SIZE; //liczba wierszy i kolumn


int main(int argc, char *argv[]) {

	double **A;
    char *path = NULL;
    char *name = NULL;

	argc = 2; //TODO do usuniecia

	if(loadArguments(argc, argv, path, name) ) {

		path = "/home/amsterdam/workspace/porr_file.txt"; //TODO do usuniecia

		if(loadData(path, &A)) {

			//printf("wartosc macierzy = %f\n", A[2][2]);

			QRGivensRotations(&A);
			//TODO jeszcze wymnożyć i zwrócić Q i R oraz dodać jakieś czasy


			freeMatrix(&A);
			return EXIT_SUCCESS;
		}

	}

	return EXIT_FAILURE;
}
