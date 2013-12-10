/*
 * FileSave.c
 *
 *  Created on: Dec 9, 2013
 *      Author: amsterdam
 */

#include "FileSave.h"

bool saveData(char *path, double timeA, double timeB) {

	FILE *f;

	f = fopen(path, "a");

	if(f == NULL ) {
		fprintf(stderr,"Error:Unable to open %s\n", (char *) f);
		return false;
	}
	fprintf(f, "\nRaport\n");
	fprintf(f, "Podana liczba rdzeni procesora = %i\n", NUM_PROCS);
	fprintf(f, "Wielkość macierzy = %i x %i\n", SIZE, SIZE);
	fprintf(f, "Czas działania algorytmu bez zrownoleglania = %f\n",timeA);
	fprintf(f, "Czas działania algorytmu zrownoleglonego w openMp = %f\n",timeB);
	fclose(f);

	return true;

}
