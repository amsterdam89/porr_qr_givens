/*
 * FileReader.c
 *
 *  Created on: Nov 22, 2013
 *      Author: amsterdam
 */
#include "FileReader.h"


bool loadArguments(int argc, char *argv[], char *path, char *name){

	if(argc == 1) {
		printf("wywolanie algorytmu z niepoprawnymi flagami.\n");
		printf("przyklady wywolania:\n porr.exe data.dat\n porr.exe data.dat wyniki.dat\n");
		return false;
	}
	else if(argc >=2) {
		if(argc == 2) {
			path = argv[1];
			name = "wynik.dat";
			return true;
		}
		else {
			path = argv[1];
			name = argv[2];
			return true;
		}
	}
	else {
			printf("blad, zle argumenty.\n");
			return false;
	}

}

bool loadData(char *path, double ***A) {
	/*
	 * plik przykladowy
	 *
	 * 4
	 * 11 12 13 14
	 * 21 22 23 24
	 * 31 32 33 34
	 * 41 42 43 44
	 */

	FILE *f;

	f = fopen(path, "r");

	if(f == NULL ) {
		fprintf(stderr,"Error:Unable to open %s\n", (char *) f);
		return false;
	}

	fscanf(f, "%d", &SIZE);

	mallocMatrix(A);
	setMatrix(f,A);
    fclose(f);

    return true;
}

void setMatrix(FILE *f, double ***A) {
	int i , j;

	for(i=0; i<SIZE; i++) //wiersze
		for(j=0; j<SIZE; j++) //kolumny
			fscanf(f, " %lf", &(*A)[i][j]);


}


