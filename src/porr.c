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
#include "FileSave/FileSave.h"
#include "QRGivensRotations/QRGivensRotations.h"
#include "openMp/QRGivensRotations/openMP_QRGivensRotations.h"
#include <time.h>



#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <time.h>
typedef clock_t TIME;

TIME get_time(void) {
	return clock();
}

#else
#include <sys/time.h>
typedef time_t TIME;


TIME get_time(void)
{
	struct timeval myTime;
	gettimeofday(&myTime, NULL);
	return myTime.tv_sec*1000000 + myTime.tv_usec;
}

#endif


extern void QRGivensRotations(double ***A);
extern void openMP_QRGivensRotations(double ***A);

int SIZE; //liczba wierszy i kolumn
int NUM_PROCS;
int NUM_PROCS_2;
int NUM_PROCS_3;


int main(int argc, char *argv[]) {

	double **A;
    char *path = NULL;
    char *name = NULL;
    TIME timeQRG, timeQRG_openMP;
    clock_t clockQRG, clockQRG_openMP;
    double unitsInMilliSecond = 1000;


	argc = 3; //TODO do usuniecia

	if(loadArguments(argc, argv, &path, &name) ) {

		NUM_PROCS = 8; //TODO rm
		path = "/home/amsterdam/workspace/porr_file.txt"; //TODO do usuniecia

		if(loadData(path, &A)) {

			if(NUM_PROCS >= 3) {
				NUM_PROCS_2 = 2;
				NUM_PROCS_3 = 3;
			}
			else if (NUM_PROCS >= 2) {
				NUM_PROCS_2 = 2;
				NUM_PROCS_3 = 2;
			}
			else {
				NUM_PROCS_2 = 1;
				NUM_PROCS_3 = 1;
				NUM_PROCS = 1;
			}

			clockQRG = clock();
		    timeQRG = get_time();
		    QRGivensRotations(&A);
		    clockQRG = clock() - clockQRG;
		    timeQRG = get_time() - timeQRG;
		    printf("Elapsed clock for QR Givens Rotations: %.16f seconds\n", (double) clockQRG / CLOCKS_PER_SEC); //TODO rm
		    printf("Elapsed time for QR Givens Rotations: %.16f \n", (double) timeQRG / unitsInMilliSecond);

		    clockQRG_openMP = clock(); //TODO rm
		    timeQRG_openMP = get_time();
			openMP_QRGivensRotations(&A);
			clockQRG_openMP = clock() - clockQRG_openMP; //TODO rm
			timeQRG_openMP = get_time() - timeQRG_openMP;
			printf("Elapsed clock for QR Givens Rotations in openMp: %.16f seconds\n", (double) clockQRG_openMP / CLOCKS_PER_SEC); //TODO rm
			printf("Elapsed time for QR Givens Rotations in openMp: %.16f \n", (double) timeQRG_openMP / unitsInMilliSecond);


			freeMatrix(&A);

			if(saveData(name, (double) timeQRG / unitsInMilliSecond, (double) timeQRG_openMP / unitsInMilliSecond))
				return EXIT_SUCCESS;
			else
				return EXIT_FAILURE;

		}

	}

	return EXIT_FAILURE;
}
