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
#ifdef __unix__
#include <sys/time.h>
#endif
#include "FileReader/FileReader.h"
#include "QRGivensRotations/QRGivensRotations.h"
#include "openMp/QRGivensRotations/openMP_QRGivensRotations.h"
#include "Cilk/QRGivensRotations/Cilk_QRGivensRotations.h"
//#include "MatrixOperation/matrixOperation.h"



extern void QRGivensRotations(double ***A);
extern void openMP_QRGivensRotations(double ***A);
//#ifdef __unix__
//extern time_t get_time(void);
//#else 
extern clock_t get_time(void); 
//#endif

int SIZE; //liczba wierszy i kolumn


int main(int argc, char *argv[]) {

	double **A;
    char *path = NULL;
    char *name = NULL;
    clock_t clockQRG, clockQRG_openMP;
	/*#ifdef __unix__
    time_t timeQRG, timeQRG_openMP;
#else*/
	clock_t timeQRG, timeQRG_openMP;
//#endif
    double unitsInMilliSecond = 1000;



	argc = 2; //TODO do usuniecia

	if(loadArguments(argc, argv, path, name) ) {

		path = "porr_file.txt"; //TODO do usuniecia

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
			//openMP_QRGivensRotations(&A);
			clockQRG_openMP = clock() - clockQRG_openMP;
			timeQRG_openMP = get_time() - timeQRG_openMP;
			printf("Elapsed clock for QR Givens Rotations in openMp: %.16f seconds\n", (double) clockQRG_openMP / CLOCKS_PER_SEC);
			printf("Elapsed time for QR Givens Rotations in openMp: %.16f \n", (double) timeQRG_openMP / unitsInMilliSecond);

		    clockQRG_openMP = clock();
		    timeQRG_openMP = get_time();
			Cilk_QRGivensRotations(&A);
			clockQRG_openMP = clock() - clockQRG_openMP;
			timeQRG_openMP = get_time() - timeQRG_openMP;
			printf("Elapsed clock for QR Givens Rotations in cilk: %.16f seconds\n", (double) clockQRG_openMP / CLOCKS_PER_SEC);
			printf("Elapsed time for QR Givens Rotations in cilk: %.16f \n", (double) timeQRG_openMP / unitsInMilliSecond);






			freeMatrix(&A);
			getchar();
			return EXIT_SUCCESS;
		}

	}

	return EXIT_FAILURE;
}

//#ifdef __unix__
//time_t get_time(void)
//{ 
//	
//	struct timeval time;
//	gettimeofday(&time, NULL);
//	return time.tv_sec*1000000 + time.tv_usec;
//	
//}
//#else
clock_t get_time(void)
{ 
	
	
	return clock();
	
}
//#endif




