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
#include "Eigenvalue/Eigenvalue.h"
#include "openMp/Eigenvalue/openMP_Eigenvalue.h"
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


extern void getEignvalues(double ***A);
extern void openMP_getEignvalues(double ***A);
extern void setNumProcs();


int SIZE; //liczba wierszy i kolumn
int MAX_ITER = 120;
double EPSILON = 0.0001;
int NUM_PROCS = 1;
int NUM_PROCS_2 = 1;


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
		//path = "/home/amsterdam/workspace/porr/porr_file.txt"; //TODO do usuniecia
		path = "/home/amsterdam/workspace/porr/porr_25.txt"; //TODO do usuniecia
		name = "wynik_10_12.dat"; //TODO rm

		if(loadData(path, &A)) {


			setNumProcs();


		    clockQRG_openMP = clock(); //TODO rm
		    timeQRG_openMP = get_time();
		    openMP_getEignvalues(&A);
			clockQRG_openMP = clock() - clockQRG_openMP; //TODO rm
			timeQRG_openMP = get_time() - timeQRG_openMP;
			printf("Elapsed clock for QR Givens Rotations in openMp: %.16f seconds\n", (double) clockQRG_openMP / CLOCKS_PER_SEC); //TODO rm
			printf("ISTOTNE Elapsed time for QR Givens Rotations in openMp: %.16f ms\n", (double) timeQRG_openMP / unitsInMilliSecond);

			clockQRG = clock();
		    timeQRG = get_time();
		    getEignvalues(&A);
		    clockQRG = clock() - clockQRG;
		    timeQRG = get_time() - timeQRG;
		    printf("Elapsed clock for QR Givens Rotations: %.16f seconds\n", (double) clockQRG / CLOCKS_PER_SEC); //TODO rm
		    printf("ISTOTNE Elapsed time for QR Givens Rotations: %.16f ms\n", (double) timeQRG / unitsInMilliSecond);




			freeMatrix(&A);

			if(saveData(name, (double) timeQRG / unitsInMilliSecond, (double) timeQRG_openMP / unitsInMilliSecond))
				return EXIT_SUCCESS;
			else
				return EXIT_FAILURE;

		}

	}

	return EXIT_FAILURE;
}

void setNumProcs() {

	if(NUM_PROCS >= 2)
		NUM_PROCS_2 = 2;
	else {
		NUM_PROCS_2 = 1;
		NUM_PROCS = 1;
	}

}
