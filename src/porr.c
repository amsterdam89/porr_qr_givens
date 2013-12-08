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
#include <sys/time.h>
#include "FileReader/FileReader.h"
#include "QRGivensRotations/QRGivensRotations.h"
#include "openMp/QRGivensRotations/openMP_QRGivensRotations.h"
//#include "MatrixOperation/matrixOperation.h"



extern void QRGivensRotations(double ***A);
extern void openMP_QRGivensRotations(double ***A);
extern time_t get_time(void);

int SIZE; //liczba wierszy i kolumn


int main(int argc, char *argv[]) {

	double **A;
    char *path = NULL;
    char *name = NULL;
    clock_t clockQRG, clockQRG_openMP;
    time_t timeQRG, timeQRG_openMP;
    double unitsInMilliSecond = 1000;



	argc = 2; //TODO do usuniecia

	if(loadArguments(argc, argv, path, name) ) {

		path = "/home/amsterdam/workspace/porr_file.txt"; //TODO do usuniecia

		if(loadData(path, &A)) {


			//TODO jeszcze wymnożyć i zwrócić Q i R oraz dodać jakieś czasy


		    clockQRG = clock();
		    timeQRG = get_time();
		    QRGivensRotations(&A);
		    clockQRG = clock() - clockQRG;
		    timeQRG = get_time() - timeQRG;
		    printf("Elapsed clock for QR Givens Rotations: %.16f seconds\n", (double) clockQRG / CLOCKS_PER_SEC);
		    printf("Elapsed time for QR Givens Rotations: %.16f \n", (double) timeQRG / unitsInMilliSecond);

		    clockQRG_openMP = clock();
		    timeQRG_openMP = get_time();
			openMP_QRGivensRotations(&A);
			clockQRG_openMP = clock() - clockQRG_openMP;
			timeQRG_openMP = get_time() - timeQRG_openMP;
			printf("Elapsed clock for QR Givens Rotations in openMp: %.16f seconds\n", (double) clockQRG_openMP / CLOCKS_PER_SEC);
			printf("Elapsed time for QR Givens Rotations: %.16f \n", (double) timeQRG_openMP / unitsInMilliSecond);






			freeMatrix(&A);
			return EXIT_SUCCESS;
		}

	}

	return EXIT_FAILURE;
}

time_t get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return time.tv_sec*1000000 + time.tv_usec;
}



