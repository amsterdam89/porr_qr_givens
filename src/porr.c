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
#include <time.h>
#include "FileReader/FileReader.h"
#include "QRGivensRotations/QRGivensRotations.h"
#include "openMp/QRGivensRotations/openMP_QRGivensRotations.h"
//#include "MatrixOperation/matrixOperation.h"


extern void QRGivensRotations(double ***A);
extern void openMP_QRGivensRotations(double ***A);

int SIZE; //liczba wierszy i kolumn


int main(int argc, char *argv[]) {

	double **A;
    char *path = NULL;
    char *name = NULL;
    clock_t timeQRG, timeQRG_openMP;



	argc = 2; //TODO do usuniecia

	if(loadArguments(argc, argv, path, name) ) {

		path = "/home/amsterdam/workspace/porr_file.txt"; //TODO do usuniecia

		if(loadData(path, &A)) {


			//TODO jeszcze wymnożyć i zwrócić Q i R oraz dodać jakieś czasy

		    timeQRG = clock();
		    QRGivensRotations(&A);
		    timeQRG = clock() - timeQRG;
		    printf("Elapsed time for QR Givens Rotations: %.16f seconds\n", (double) timeQRG / CLOCKS_PER_SEC);

		    timeQRG_openMP = clock();
			openMP_QRGivensRotations(&A);
			timeQRG_openMP = clock() - timeQRG_openMP;
			printf("Elapsed time for QR Givens Rotations in openMp: %.16f seconds\n", (double) timeQRG_openMP / CLOCKS_PER_SEC);






			freeMatrix(&A);
			return EXIT_SUCCESS;
		}

	}

	return EXIT_FAILURE;
}


