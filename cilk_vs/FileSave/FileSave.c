/*
 * FileSave.c
 *
 *  Created on: Dec 9, 2013
 *      Author: amsterdam
 */

#include "FileSave.h"

bool saveData(char *path, double timeA, double timeB) {

	FILE *f;

	f = fopen(path, "w");

	if(f == NULL ) {
		fprintf(stderr,"Error:Unable to open %s\n", (char *) f);
		return false;
	}
	fprintf(f, "Raport\n");
	fprintf(f, "Czas działania algorytmu bez zrownoleglania = %f\n",timeA);
	fprintf(f, "Czas działania algorytmu zrownoleglonego w cilk = %f\n",timeB);
	fclose(f);

	return true;

}
